main: test.c DES.c
	gcc test.c DES.c -o test.exe -g

.PHONY : clean test1 test2

test1: main
	./test.exe

test2: main 
	./test test_vector

clean:
	del *.o test.exe -rf
	
