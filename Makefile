scinstdlib.a: Array.c Hashmap.c Utils.c
	gcc -c *.c
	ar rcs scinstdlib.a *.o

install: scinstdlib.a
	cp scinstdlib.a /usr/lib/scinstdlib.a
	cp scinstdlib.h /usr/include/scinstdlib.h

clean:
	rm *.o scinstdlib.a
