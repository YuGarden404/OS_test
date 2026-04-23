all:
	# -O0: 关掉所有优化，老老实实按你写的代码编译
	gcc -O0 order.c -o order_O0 -lpthread
	# -O2: 开启高级别优化，让编译器尽情发挥
	gcc -O2 order.c -o order_O2 -lpthread

run_O0: all
	./order_O0

run_O2: all
	./order_O2

clean:
	rm -f order_O0 order_O2