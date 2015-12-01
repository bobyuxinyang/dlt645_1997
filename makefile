objs=main.o dlt645_api_97.o
cc=gcc
1:$(objs)
	cc -o 1 $(objs) -lpthread 
main.o:dlt645_api_97.h
dlt645_api_97.o:dlt645_api_97.h

gdb:
	cc -o 1 dlt645_api_97.c dlt645_api_97.h main.c -g -
clean:
	rm 1 $(objs)