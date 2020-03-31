# miniPowerMeter firmware
---

## Build
> make clean</br>
> make</br>

## Start OpenOCD
> openocd -f jlink.cfg -f stm32f0x.cfg</br>
__or using default openocd script files__</br>
> openocd -f interface/jlink.cfg -f target/stm32f0x.cfg</br>

## Start Flash & Debug
> arm-none-linux-gnueabi-gdb</br>
> target remote 127.0.0.1:3333</br>
> monitor halt</br>
> monitor flash write_image erase build/mini_pm.elf</br>
> monitor reset</br>
__or using script__</br>
> arm-none-line-gnueabi-gdb</br>
> source script/gdb_download.gdb
__or using makefile command__</br>
> make download
> make debug

