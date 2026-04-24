all:
	# -O0 表示关闭编译器优化，-lpthread 表示链接多线程库
	gcc -O0 pc.c -o pc -lpthread

run: all
	./pc

clean:
	rm -f pc