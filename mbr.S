.code16                 # 告诉汇编器：我们现在处于 16 位实模式 (Real Mode)
.global _start          # 导出入口符号

_start:
    # 1. 初始化段寄存器 (将数据段和额外段对齐到代码段)
    movw %cs, %ax
    movw %ax, %ds
    movw %ax, %es

    # 2. 准备打印字符串
    movw $msg, %si      # 将字符串 msg 的内存地址放入 %si 寄存器

print_loop:
    lodsb               # 从 %ds:%si 读取一个字节到 %al，并将 %si 加 1
    orb %al, %al        # 对 %al 进行按位或操作，用来判断是否到了字符串结尾 (0)
    jz halt             # 如果是 0，说明打印完了，跳到 halt 停机

    # 3. 调用 BIOS 中断打印字符
    movb $0x0e, %ah     # AH = 0x0E 表示 BIOS 视频服务中的 "Teletype 输出" 功能
    int $0x10           # 触发 0x10 中断，BIOS 会把 %al 中的字符显示到屏幕上
    jmp print_loop      # 循环处理下一个字符

halt:
    hlt                 # 让 CPU 停机休眠，降低功耗
    jmp halt            # 哪怕被唤醒也继续死循环

msg:
    .asciz "Hello, OS World!" # .asciz 会自动在字符串末尾补一个 0 字节

# 4. 填充与魔数 (Magic Number)
.org 510                # 将当前位置直接跳到第 510 字节处 (前面的空白用 0 填充)
.word 0xaa55            # 在最后两个字节 (510 和 511) 写入 0x55AA (x86是小端序，所以写成 0xaa55)