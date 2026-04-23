all:
	# -O0 表示关闭编译器优化，-lpthread 表示链接多线程库
	gcc -O0 sum_posix.c -o sum_posix -lpthread

run: all
	./sum_posix

clean:
	rm -f sum_posix