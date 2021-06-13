main: test.c DES.c
	gcc test.c DES.c -o test.exe -g

.PHONY : clean all

all: main run

clean:
	del *.o test.exe -rf
	
run: test.exe
	./test.exe