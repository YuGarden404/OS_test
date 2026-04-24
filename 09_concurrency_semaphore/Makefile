all:
	# -O0 表示关闭编译器优化，-lpthread 表示链接多线程库
	gcc -O0 pc_sem.c -o pc_sem -lpthread

run: all
	./pc_sem

clean:
	rm -f pc_sem