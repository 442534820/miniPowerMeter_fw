
target remote 127.0.0.1:3333
file build/mini_pm.elf
monitor halt
hb main
monitor reset

