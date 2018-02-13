/*
 * This file is part of the coreboot project.
 *
 * Copyright 2016 Google Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <assert.h>
#include <spi-generic.h>
#include <string.h>

int spi_claim_bus(const struct spi_slave *slave)
{
	const struct spi_ctrlr *ctrlr = slave->ctrlr;
	if (ctrlr && ctrlr->claim_bus)
		return ctrlr->claim_bus(slave);
	return 0;
}

void spi_release_bus(const struct spi_slave *slave)
{
	const struct spi_ctrlr *ctrlr = slave->ctrlr;
	if (ctrlr && ctrlr->release_bus)
		ctrlr->release_bus(slave);
}

static int spi_xfer_single_op(const struct spi_slave *slave,
			struct spi_op *op)
{
	const struct spi_ctrlr *ctrlr = slave->ctrlr;
	int ret;

	if (!ctrlr || !ctrlr->xfer)
		return -1;

	ret = ctrlr->xfer(slave, op->dout, op->bytesout, op->din, op->bytesin);
	if (ret)
		op->status = SPI_OP_FAILURE;
	else
		op->status = SPI_OP_SUCCESS;

	return ret;
}

static int spi_xfer_vector_default(const struct spi_slave *slave,
				struct spi_op vectors[], size_t count)
{
	size_t i;
	int ret;

	for (i = 0; i < count; i++) {
		ret = spi_xfer_single_op(slave, &vectors[i]);
		if (ret)
			return ret;
	}

	return 0;
}

int spi_xfer_vector(const struct spi_slave *slave,
		struct spi_op vectors[], size_t count)
{
	const struct spi_ctrlr *ctrlr = slave->ctrlr;

	if (ctrlr && ctrlr->xfer_vector)
		return ctrlr->xfer_vector(slave, vectors, count);

	return spi_xfer_vector_default(slave, vectors, count);
}

int spi_xfer(const struct spi_slave *slave, const void *dout, size_t bytesout,
	     void *din, size_t bytesin)
{
	const struct spi_ctrlr *ctrlr = slave->ctrlr;

	if (ctrlr && ctrlr->xfer)
		return ctrlr->xfer(slave, dout, bytesout, din, bytesin);

	return -1;
}

void __attribute__((weak)) spi_init(void)
{
	/* Default weak implementation - do nothing. */
}

const struct spi_ctrlr_buses spi_ctrlr_bus_map[0] __attribute__((weak));
const size_t spi_ctrlr_bus_map_count __attribute__((weak));

int __attribute__((weak)) spi_setup_slave(unsigned int bus, unsigned int cs,
					  struct spi_slave *slave)
{
	size_t i;

	memset(slave, 0, sizeof(*slave));

	for (i = 0; i < spi_ctrlr_bus_map_count; i++) {
		if ((spi_ctrlr_bus_map[i].bus_start <= bus) &&
		    (spi_ctrlr_bus_map[i].bus_end >= bus)) {
			slave->ctrlr = spi_ctrlr_bus_map[i].ctrlr;
			break;
		}
	}

	if (slave->ctrlr == NULL)
		return -1;

	slave->bus = bus;
	slave->cs = cs;

	if (slave->ctrlr->setup)
		return slave->ctrlr->setup(slave);

	return 0;
}

static int spi_xfer_combine_two_vectors(const struct spi_slave *slave,
					struct spi_op *v1, struct spi_op *v2)
{
	struct spi_op op = {
		.dout = v1->dout, .bytesout = v1->bytesout,
		.din = v2->din, .bytesin = v2->bytesin,
	};
	int ret;

	/*
	 * Combine two vectors only if:
	 * v1 has non-NULL dout and NULL din and
	 * v2 has non-NULL din and NULL dout and
	 *
	 * In all other cases, do not combine the two vectors.
	 */
	if ((!v1->dout || v1->din) || (v2->dout || !v2->din))
		return -1;

	ret = spi_xfer_single_op(slave, &op);
	v1->status = v2->status = op.status;

	return ret;
}

/*
 * Helper function to allow chipsets to combine two vectors if possible. This
 * function can only handle upto 2 vectors.
 *
 * Two vectors are combined if first vector has a non-NULL dout and NULL din and
 * second vector has a non-NULL din and NULL dout. Otherwise, each vector is
 * operated upon one at a time.
 *
 * Returns 0 on success and non-zero on failure.
 */
int spi_xfer_two_vectors(const struct spi_slave *slave,
			struct spi_op vectors[], size_t count)
{
	int ret;

	assert (count <= 2);

	if (count == 2) {
		ret = spi_xfer_combine_two_vectors(slave, &vectors[0],
						&vectors[1]);

		if (!ret || (vectors[0].status != SPI_OP_NOT_EXECUTED))
			return ret;
	}

	return spi_xfer_vector_default(slave, vectors, count);
}
