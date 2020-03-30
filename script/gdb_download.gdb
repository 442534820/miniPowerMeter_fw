
target remote 127.0.0.1:3333
monitor halt
monitor flash write_image erase build/mini_pm.elf
monitor reset

