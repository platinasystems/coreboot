FROM platina-buildroot

RUN rm -rf builds/*/build/coreboot-master/build && rm -f builds/*/build/coreboot-master/.stamp_built builds/*/build/coreboot-master/.stamp_target_installed builds/*/build/coreboot-master/.stamp_staging_installed

COPY . builds/example-amd64/build/coreboot-master
COPY . builds/platina-mk1/build/coreboot-master

RUN make -C buildroot O=../builds/example-amd64 example-amd64_defconfig && make -C builds/example-amd64 all
RUN make -C buildroot O=../builds/platina-mk1 platina-mk1_defconfig && make -C builds/platina-mk1 all
