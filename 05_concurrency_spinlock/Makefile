all:
	# -O0 表示关闭编译器优化，-lpthread 表示链接多线程库
	gcc -O0 sum_my_lock.c -o sum_my_lock -lpthread

run: all
	./sum_my_lock

clean:
	rm -f sum_my_lock