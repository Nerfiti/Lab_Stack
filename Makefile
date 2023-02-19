all:
	g++ main.cpp Stack_dynamic.cpp Stack_list.cpp -o Stack.out
	./Stack.out

debug:
	g++ -g main.cpp Stack_dynamic.cpp Stack_list.cpp -o Stack.out
	gdb ./Stack.out