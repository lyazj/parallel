CFLAGS = -g -O3

all: presum-demo

clean:
	$(RM) *.o presum-demo

presum-demo: presum.o
