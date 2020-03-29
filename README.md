

# Build
> make clean
> make

# Start OpenOCD
> openocd -f jlink.cfg -f stm32f0x.cfg
# or using default openocd script files
> openocd -f interface/jlink.cfg -f target/stm32f0x.cfg

# Start Flash & Debug
> arm-none-linux-gnueabi-gdb
> target remote 127.0.0.1:3333
> monitor halt
> monitor flash write_image erase build/mini_pm.elf
> monitor reset

