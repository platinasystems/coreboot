/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 The Chromium OS Authors. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdint.h>
#include <string.h>
#include <cbmem.h>
#include <console/console.h>
#include <arch/io.h>
#include <bootmode.h>
#include <bootstate.h>
#include <delay.h>
#include <elog.h>
#include <halt.h>
#include <reset.h>
#include <rtc.h>
#include <stdlib.h>
#include <vboot/vboot_common.h>

#include "chip.h"
#include "ec.h"
#include "ec_commands.h"

void log_recovery_mode_switch(void)
{
	uint32_t *events;

	if (cbmem_find(CBMEM_ID_EC_HOSTEVENT))
		return;

	events = cbmem_add(CBMEM_ID_EC_HOSTEVENT, sizeof(*events));
	if (!events)
		return;

	*events = google_chromeec_get_events_b();
}

static void google_chromeec_elog_add_recovery_event(void *unused)
{
	uint32_t *events = cbmem_find(CBMEM_ID_EC_HOSTEVENT);
	uint8_t event_byte = EC_EVENT_KEYBOARD_RECOVERY;

	if (!events)
		return;

	if (!(*events & EC_HOST_EVENT_MASK(EC_HOST_EVENT_KEYBOARD_RECOVERY)))
		return;

	if (*events &
	    EC_HOST_EVENT_MASK(EC_HOST_EVENT_KEYBOARD_RECOVERY_HW_REINIT))
		event_byte = EC_EVENT_KEYBOARD_RECOVERY_HWREINIT;

	elog_add_event_byte(ELOG_TYPE_EC_EVENT, event_byte);
}

BOOT_STATE_INIT_ENTRY(BS_WRITE_TABLES, BS_ON_ENTRY,
		      google_chromeec_elog_add_recovery_event, NULL);

uint8_t google_chromeec_calc_checksum(const uint8_t *data, int size)
{
	int csum;

	for (csum = 0; size > 0; data++, size--)
		csum += *data;
	return (uint8_t)(csum & 0xff);
}

int google_chromeec_kbbacklight(int percent)
{
	struct chromeec_command cec_cmd;
	struct ec_params_pwm_set_keyboard_backlight cmd_backlight;
	struct ec_response_pwm_get_keyboard_backlight rsp_backlight;
	/* if they were dumb, help them out */
	percent = percent % 101;
	cec_cmd.cmd_code = EC_CMD_PWM_SET_KEYBOARD_BACKLIGHT;
	cec_cmd.cmd_version = 0;
	cmd_backlight.percent = percent;
	cec_cmd.cmd_data_in = &cmd_backlight;
	cec_cmd.cmd_data_out = &rsp_backlight;
	cec_cmd.cmd_size_in = sizeof(cmd_backlight);
	cec_cmd.cmd_size_out = sizeof(rsp_backlight);
	cec_cmd.cmd_dev_index = 0;
	google_chromeec_command(&cec_cmd);
	printk(BIOS_DEBUG, "Google Chrome set keyboard backlight: %x status (%x)\n",
	       rsp_backlight.percent, cec_cmd.cmd_code);
	return cec_cmd.cmd_code;

}

void google_chromeec_post(u8 postcode)
{
	/* backlight is a percent. postcode is a u8.
	 * Convert the u8 to %.
	 */
	postcode = (postcode/4) + (postcode/8);
	google_chromeec_kbbacklight(postcode);
}

/*
 * Query the EC for specified mask indicating enabled events.
 * The EC maintains separate event masks for SMI, SCI and WAKE.
 */
static u32 google_chromeec_get_mask(u8 type)
{
	struct ec_params_host_event_mask req;
	struct ec_response_host_event_mask rsp;
	struct chromeec_command cmd;

	cmd.cmd_code = type;
	cmd.cmd_version = 0;
	cmd.cmd_data_in = &req;
	cmd.cmd_size_in = sizeof(req);
	cmd.cmd_data_out = &rsp;
	cmd.cmd_size_out = sizeof(rsp);
	cmd.cmd_dev_index = 0;

	if (google_chromeec_command(&cmd) == 0)
		return rsp.mask;
	return 0;
}

static int google_chromeec_set_mask(u8 type, u32 mask)
{
	struct ec_params_host_event_mask req;
	struct ec_response_host_event_mask rsp;
	struct chromeec_command cmd;

	req.mask = mask;
	cmd.cmd_code = type;
	cmd.cmd_version = 0;
	cmd.cmd_data_in = &req;
	cmd.cmd_size_in = sizeof(req);
	cmd.cmd_data_out = &rsp;
	cmd.cmd_size_out = sizeof(rsp);
	cmd.cmd_dev_index = 0;

	return google_chromeec_command(&cmd);
}

u32 google_chromeec_get_events_b(void)
{
	return google_chromeec_get_mask(EC_CMD_HOST_EVENT_GET_B);
}

int google_chromeec_clear_events_b(u32 mask)
{
	printk(BIOS_DEBUG, "Chrome EC: clear events_b mask to 0x%08x\n", mask);
	return google_chromeec_set_mask(
		EC_CMD_HOST_EVENT_CLEAR_B, mask);
}

int google_chromeec_get_mkbp_event(struct ec_response_get_next_event *event)
{
	struct chromeec_command cmd;

	cmd.cmd_code = EC_CMD_GET_NEXT_EVENT;
	cmd.cmd_version = 0;
	cmd.cmd_data_in = NULL;
	cmd.cmd_size_in = 0;
	cmd.cmd_data_out = event;
	cmd.cmd_size_out = sizeof(*event);
	cmd.cmd_dev_index = 0;

	return google_chromeec_command(&cmd);
}

/* Get the current device event mask */
uint32_t google_chromeec_get_device_enabled_events(void)
{
	struct ec_params_device_event req;
	struct ec_response_device_event rsp;
	struct chromeec_command cmd;

	req.param = EC_DEVICE_EVENT_PARAM_GET_ENABLED_EVENTS;
	cmd.cmd_code = EC_CMD_DEVICE_EVENT;
	cmd.cmd_version = 0;
	cmd.cmd_data_in = &req;
	cmd.cmd_size_in = sizeof(req);
	cmd.cmd_data_out = &rsp;
	cmd.cmd_size_out = sizeof(rsp);
	cmd.cmd_dev_index = 0;

	if (google_chromeec_command(&cmd) == 0)
		return rsp.event_mask;
	return 0;
}

/* Set the current device event mask */
int google_chromeec_set_device_enabled_events(uint32_t mask)
{
	struct ec_params_device_event req;
	struct ec_response_device_event rsp;
	struct chromeec_command cmd;

	req.event_mask = mask;
	req.param = EC_DEVICE_EVENT_PARAM_SET_ENABLED_EVENTS;
	cmd.cmd_code = EC_CMD_DEVICE_EVENT;
	cmd.cmd_version = 0;
	cmd.cmd_data_in = &req;
	cmd.cmd_size_in = sizeof(req);
	cmd.cmd_data_out = &rsp;
	cmd.cmd_size_out = sizeof(rsp);
	cmd.cmd_dev_index = 0;

	return google_chromeec_command(&cmd);
}

/* Read and clear pending device events */
uint32_t google_chromeec_get_device_current_events(void)
{
	struct ec_params_device_event req;
	struct ec_response_device_event rsp;
	struct chromeec_command cmd;

	req.param = EC_DEVICE_EVENT_PARAM_GET_CURRENT_EVENTS;
	cmd.cmd_code = EC_CMD_DEVICE_EVENT;
	cmd.cmd_version = 0;
	cmd.cmd_data_in = &req;
	cmd.cmd_size_in = sizeof(req);
	cmd.cmd_data_out = &rsp;
	cmd.cmd_size_out = sizeof(rsp);
	cmd.cmd_dev_index = 0;

	if (google_chromeec_command(&cmd) == 0)
		return rsp.event_mask;
	return 0;
}

static void google_chromeec_log_device_events(uint32_t mask)
{
	uint32_t events;
	int i;

	if (!IS_ENABLED(CONFIG_ELOG) || !mask)
		return;

	if (google_chromeec_check_feature(EC_FEATURE_DEVICE_EVENT) != 1)
		return;

	events = google_chromeec_get_device_current_events() & mask;
	printk(BIOS_INFO, "EC Device Events: 0x%08x\n", events);

	for (i = 0; i < sizeof(events) * 8; i++) {
		if (EC_DEVICE_EVENT_MASK(i) & events)
			elog_add_event_byte(ELOG_TYPE_EC_DEVICE_EVENT, i);
	}
}

static void google_chromeec_log_events(u32 mask)
{
	u8 event;
	u32 wake_mask;

	if (!IS_ENABLED(CONFIG_ELOG))
		return;

	/* Set wake mask so events will be read from ACPI interface */
	wake_mask = google_chromeec_get_wake_mask();
	google_chromeec_set_wake_mask(mask);

	while ((event = google_chromeec_get_event()) != 0) {
		if (EC_HOST_EVENT_MASK(event) & mask)
			elog_add_event_byte(ELOG_TYPE_EC_EVENT, event);
	}

	google_chromeec_set_wake_mask(wake_mask);
}

void google_chromeec_events_init(const struct google_chromeec_event_info *info,
					bool is_s3_wakeup)
{
	if (is_s3_wakeup) {
		google_chromeec_log_events(info->log_events |
						info->s3_wake_events);

		/* Log and clear device events that may wake the system. */
		google_chromeec_log_device_events(info->s3_device_events);

		/* Disable SMI and wake events. */
		google_chromeec_set_smi_mask(0);

		/* Clear pending events. */
		while (google_chromeec_get_event() != 0)
			;

		/* Restore SCI event mask. */
		google_chromeec_set_sci_mask(info->sci_events);
	} else
		google_chromeec_log_events(info->log_events |
						info->s5_wake_events);

	/* Clear wake event mask. */
	google_chromeec_set_wake_mask(0);
}

int google_chromeec_check_feature(int feature)
{
	struct chromeec_command cmd;
	struct ec_response_get_features r;

	cmd.cmd_code = EC_CMD_GET_FEATURES;
	cmd.cmd_version = 0;
	cmd.cmd_size_in = 0;
	cmd.cmd_data_out = &r;
	cmd.cmd_size_out = sizeof(r);
	cmd.cmd_dev_index = 0;

	if (google_chromeec_command(&cmd) != 0)
		return -1;

	if (feature >= 8 * sizeof(r.flags))
		return -1;

	return r.flags[feature / 32] & EC_FEATURE_MASK_0(feature);
}

int google_chromeec_set_sku_id(u32 skuid)
{
	struct chromeec_command cmd;
	struct ec_sku_id_info set_skuid = {
		.sku_id = skuid
	};

	cmd.cmd_code = EC_CMD_SET_SKU_ID;
	cmd.cmd_version = 0;
	cmd.cmd_size_in = sizeof(set_skuid);
	cmd.cmd_data_in = &set_skuid;
	cmd.cmd_data_out = NULL;
	cmd.cmd_size_out = 0;
	cmd.cmd_dev_index = 0;

	if (google_chromeec_command(&cmd) != 0)
		return -1;

	return 0;
}

#if IS_ENABLED(CONFIG_EC_GOOGLE_CHROMEEC_RTC)
int rtc_get(struct rtc_time *time)
{
	struct chromeec_command cmd;
	struct ec_response_rtc r;

	cmd.cmd_code = EC_CMD_RTC_GET_VALUE;
	cmd.cmd_version = 0;
	cmd.cmd_size_in = 0;
	cmd.cmd_data_out = &r;
	cmd.cmd_size_out = sizeof(r);
	cmd.cmd_dev_index = 0;

	if (google_chromeec_command(&cmd) != 0)
		return -1;

	return rtc_to_tm(r.time, time);
}
#endif

int google_chromeec_reboot(int dev_idx, enum ec_reboot_cmd type, uint8_t flags)
{
	struct ec_params_reboot_ec reboot_ec = {
		.cmd = type,
		.flags = flags,
	};
	struct ec_response_get_version cec_resp = { };
	struct chromeec_command cec_cmd = {
		.cmd_code = EC_CMD_REBOOT_EC,
		.cmd_version = 0,
		.cmd_data_in = &reboot_ec,
		.cmd_data_out = &cec_resp,
		.cmd_size_in = sizeof(reboot_ec),
		.cmd_size_out = 0, /* ignore response, if any */
		.cmd_dev_index = dev_idx,
	};

	return google_chromeec_command(&cec_cmd);
}

#ifndef __SMM__
u16 google_chromeec_get_board_version(void)
{
	struct chromeec_command cmd;
	struct ec_response_board_version board_v;

	cmd.cmd_code = EC_CMD_GET_BOARD_VERSION;
	cmd.cmd_version = 0;
	cmd.cmd_size_in = 0;
	cmd.cmd_size_out = sizeof(board_v);
	cmd.cmd_data_out = &board_v;
	cmd.cmd_dev_index = 0;

	if (google_chromeec_command(&cmd) != 0)
		return 0;

	return board_v.board_version;
}

u32 google_chromeec_get_sku_id(void)
{
	struct chromeec_command cmd;
	struct ec_sku_id_info sku_v;

	cmd.cmd_code = EC_CMD_GET_SKU_ID;
	cmd.cmd_version = 0;
	cmd.cmd_size_in = 0;
	cmd.cmd_size_out = sizeof(sku_v);
	cmd.cmd_data_out = &sku_v;
	cmd.cmd_dev_index = 0;

	if (google_chromeec_command(&cmd) != 0)
		return 0;

	return sku_v.sku_id;
}

int google_chromeec_vbnv_context(int is_read, uint8_t *data, int len)
{
	struct chromeec_command cec_cmd;
	struct ec_params_vbnvcontext cmd_vbnvcontext;
	struct ec_response_vbnvcontext rsp_vbnvcontext;
	int retries = 3;

	if (len != EC_VBNV_BLOCK_SIZE)
		return -1;

retry:
	cec_cmd.cmd_code = EC_CMD_VBNV_CONTEXT;
	cec_cmd.cmd_version = EC_VER_VBNV_CONTEXT;
	cec_cmd.cmd_data_in = &cmd_vbnvcontext;
	cec_cmd.cmd_data_out = &rsp_vbnvcontext;
	cec_cmd.cmd_size_in = sizeof(cmd_vbnvcontext);
	cec_cmd.cmd_size_out = is_read ? sizeof(rsp_vbnvcontext) : 0;
	cec_cmd.cmd_dev_index = 0;

	cmd_vbnvcontext.op = is_read ? EC_VBNV_CONTEXT_OP_READ :
					EC_VBNV_CONTEXT_OP_WRITE;

	if (!is_read)
		memcpy(&cmd_vbnvcontext.block, data, EC_VBNV_BLOCK_SIZE);

	if (google_chromeec_command(&cec_cmd)) {
		printk(BIOS_ERR, "ERROR: failed to %s vbnv_ec context: %d\n",
			is_read ? "read" : "write", (int)cec_cmd.cmd_code);
		mdelay(10);	/* just in case */
		if (--retries)
			goto retry;
	}

	if (is_read)
		memcpy(data, &rsp_vbnvcontext.block, EC_VBNV_BLOCK_SIZE);

	return cec_cmd.cmd_code;
}

#endif /* ! __SMM__ */

#ifndef __PRE_RAM__

int google_chromeec_i2c_xfer(uint8_t chip, uint8_t addr, int alen,
			     uint8_t *buffer, int len, int is_read)
{
	union {
		struct ec_params_i2c_passthru p;
		uint8_t outbuf[EC_HOST_PARAM_SIZE];
	} params;
	union {
		struct ec_response_i2c_passthru r;
		uint8_t inbuf[EC_HOST_PARAM_SIZE];
	} response;
	struct ec_params_i2c_passthru *p = &params.p;
	struct ec_response_i2c_passthru *r = &response.r;
	struct ec_params_i2c_passthru_msg *msg = p->msg;
	struct chromeec_command cmd;
	uint8_t *pdata;
	int read_len, write_len;
	int size;
	int rv;

	p->port = 0;

	if (alen != 1) {
		printk(BIOS_ERR, "Unsupported address length %d\n", alen);
		return -1;
	}
	if (is_read) {
		read_len = len;
		write_len = alen;
		p->num_msgs = 2;
	} else {
		read_len = 0;
		write_len = alen + len;
		p->num_msgs = 1;
	}

	size = sizeof(*p) + p->num_msgs * sizeof(*msg);
	if (size + write_len > sizeof(params)) {
		printk(BIOS_ERR, "Params too large for buffer\n");
		return -1;
	}
	if (sizeof(*r) + read_len > sizeof(response)) {
		printk(BIOS_ERR, "Read length too big for buffer\n");
		return -1;
	}

	/* Create a message to write the register address and optional data */
	pdata = (uint8_t *)p + size;
	msg->addr_flags = chip;
	msg->len = write_len;
	pdata[0] = addr;
	if (!is_read)
		memcpy(pdata + 1, buffer, len);
	msg++;

	if (read_len) {
		msg->addr_flags = chip | EC_I2C_FLAG_READ;
		msg->len = read_len;
	}

	cmd.cmd_code = EC_CMD_I2C_PASSTHRU;
	cmd.cmd_version = 0;
	cmd.cmd_data_in = p;
	cmd.cmd_size_in = size + write_len;
	cmd.cmd_data_out = r;
	cmd.cmd_size_out = sizeof(*r) + read_len;
	cmd.cmd_dev_index = 0;
	rv = google_chromeec_command(&cmd);
	if (rv != 0)
		return rv;

	/* Parse response */
	if (r->i2c_status & EC_I2C_STATUS_ERROR) {
		printk(BIOS_ERR, "Transfer failed with status=0x%x\n",
		       r->i2c_status);
		return -1;
	}

	if (cmd.cmd_size_out < sizeof(*r) + read_len) {
		printk(BIOS_ERR, "Truncated read response\n");
		return -1;
	}

	if (read_len)
		memcpy(buffer, r->data, read_len);

	return 0;
}

int google_chromeec_set_sci_mask(u32 mask)
{
	printk(BIOS_DEBUG, "Chrome EC: Set SCI mask to 0x%08x\n", mask);
	return google_chromeec_set_mask(
		EC_CMD_HOST_EVENT_SET_SCI_MASK, mask);
}

int google_chromeec_set_smi_mask(u32 mask)
{
	printk(BIOS_DEBUG, "Chrome EC: Set SMI mask to 0x%08x\n", mask);
	return google_chromeec_set_mask(
		EC_CMD_HOST_EVENT_SET_SMI_MASK, mask);
}

int google_chromeec_set_wake_mask(u32 mask)
{
	printk(BIOS_DEBUG, "Chrome EC: Set WAKE mask to 0x%08x\n", mask);
	return google_chromeec_set_mask(
		EC_CMD_HOST_EVENT_SET_WAKE_MASK, mask);
}

u32 google_chromeec_get_wake_mask(void)
{
	return google_chromeec_get_mask(
		EC_CMD_HOST_EVENT_GET_WAKE_MASK);
}

int google_chromeec_set_usb_charge_mode(u8 port_id, enum usb_charge_mode mode)
{
	struct chromeec_command cmd;
	struct ec_params_usb_charge_set_mode set_mode = {
		.usb_port_id = port_id,
		.mode = mode,
	};

	cmd.cmd_code = EC_CMD_USB_CHARGE_SET_MODE;
	cmd.cmd_version = 0;
	cmd.cmd_size_in = sizeof(set_mode);
	cmd.cmd_data_in = &set_mode;
	cmd.cmd_size_out = 0;
	cmd.cmd_data_out = NULL;
	cmd.cmd_dev_index = 0;

	return google_chromeec_command(&cmd);
}

int google_chromeec_set_usb_pd_role(u8 port, enum usb_pd_control_role role)
{
	struct ec_params_usb_pd_control req = {
		.port = port,
		.role = role,
		.mux = USB_PD_CTRL_MUX_NO_CHANGE,
		.swap = USB_PD_CTRL_SWAP_NONE,
	};
	struct ec_response_usb_pd_control rsp;
	struct chromeec_command cmd = {
		.cmd_code = EC_CMD_USB_PD_CONTROL,
		.cmd_version = 0,
		.cmd_data_in = &req,
		.cmd_size_in = sizeof(req),
		.cmd_data_out = &rsp,
		.cmd_size_out = sizeof(rsp),
		.cmd_dev_index = 0,
	};

	return google_chromeec_command(&cmd);
}

#ifndef __SMM__

static
int google_chromeec_hello(void)
{
	struct chromeec_command cec_cmd;
	struct ec_params_hello cmd_hello;
	struct ec_response_hello rsp_hello;
	cmd_hello.in_data = 0x10203040;
	cec_cmd.cmd_code = EC_CMD_HELLO;
	cec_cmd.cmd_version = 0;
	cec_cmd.cmd_data_in = &cmd_hello.in_data;
	cec_cmd.cmd_data_out = &rsp_hello.out_data;
	cec_cmd.cmd_size_in = sizeof(cmd_hello.in_data);
	cec_cmd.cmd_size_out = sizeof(rsp_hello.out_data);
	cec_cmd.cmd_dev_index = 0;
	google_chromeec_command(&cec_cmd);
	printk(BIOS_DEBUG, "Google Chrome EC: Hello got back %x status (%x)\n",
	       rsp_hello.out_data, cec_cmd.cmd_code);
	return cec_cmd.cmd_code;
}

static int ec_image_type; /* Cached EC image type (ro or rw). */

void google_chromeec_init(void)
{
	struct chromeec_command cec_cmd;
	struct ec_response_get_version cec_resp = {{0}};

	printk(BIOS_DEBUG, "Google Chrome EC: Initializing keyboard.\n");

	google_chromeec_hello();

	cec_cmd.cmd_code = EC_CMD_GET_VERSION;
	cec_cmd.cmd_version = 0;
	cec_cmd.cmd_data_out = &cec_resp;
	cec_cmd.cmd_size_in = 0;
	cec_cmd.cmd_size_out = sizeof(cec_resp);
	cec_cmd.cmd_dev_index = 0;
	google_chromeec_command(&cec_cmd);

	if (cec_cmd.cmd_code) {
		printk(BIOS_DEBUG,
		       "Google Chrome EC: version command failed!\n");
	} else {
		printk(BIOS_DEBUG, "Google Chrome EC: version:\n");
		printk(BIOS_DEBUG, "    ro: %s\n", cec_resp.version_string_ro);
		printk(BIOS_DEBUG, "    rw: %s\n", cec_resp.version_string_rw);
		printk(BIOS_DEBUG, "  running image: %d\n",
		       cec_resp.current_image);
		ec_image_type = cec_resp.current_image;
	}
}

int google_ec_running_ro(void)
{
	return (ec_image_type == EC_IMAGE_RO);
}
#endif /* ! __SMM__ */

#endif /* ! __PRE_RAM__ */
