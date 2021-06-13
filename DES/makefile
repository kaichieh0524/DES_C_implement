main: test.c DES.c
	gcc test.c DES.c -o test -g

.PHONY : clean test1 test2

test1: main
	./test

test2: main 
	./test test_vector

clean:
	rm *.o test -rf
	
