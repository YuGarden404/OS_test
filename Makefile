# 编译选项：生成 32 位目标文件（虽然代码是16位的），不使用标准库
CFLAGS = -m32 -c

all: run

# 1. 将汇编代码编译为目标文件 (.o)
mbr.o: mbr.S
	gcc $(CFLAGS) mbr.S -o mbr.o

# 2. 将目标文件链接到 0x7c00 地址，并转换为 ELF 格式
mbr.elf: mbr.o
	ld -m elf_i386 -Ttext 0x7c00 mbr.o -o mbr.elf

# 3. 使用 objcopy 把 ELF 格式的壳去掉，只提取纯二进制数据 (.bin)
mbr.bin: mbr.elf
	objcopy -O binary mbr.elf mbr.bin

# 4. 运行 QEMU 模拟器
run: mbr.bin
	env -u LD_LIBRARY_PATH qemu-system-i386 -drive format=raw,file=mbr.bin

# 清理生成的文件
clean:
	rm -f *.o *.elf *.bin