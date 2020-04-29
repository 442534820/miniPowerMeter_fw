# miniPowerMeter firmware
---

## Build
> make clean</br>
> make</br>

## Start OpenOCD
> openocd -f jlink.cfg -f stm32f0x.cfg</br>
__or using default openocd script files__</br>
> openocd -f interface/jlink.cfg -f target/stm32f0x.cfg</br>
__or using auto script__</br>
> ./script/run_openocd.sh

## Start Flash & Debug
> arm-none-linux-gnueabi-gdb</br>
> target remote 127.0.0.1:3333</br>
> monitor halt</br>
> monitor flash write_image erase build/mini_pm.elf</br>
> monitor reset</br>
__or using script__</br>
> arm-none-line-gnueabi-gdb</br>
> source script/gdb_download.gdb</br>
__or using makefile command__</br>
> make download</br>
> make debug</br>

## Flash via DFU (dfuse-tool needed)
> dfu-convert -b 0x08000000:build/mini_pm.bin build/mini_pm.dfu</br>
> dfu-util -a 0 -D build/mini_pm.dfu</br>

