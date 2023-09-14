CFLAGS = -g -O3
LDFLAGS =

all: presum-demo

clean:
	$(RM) *.o presum-demo

%.o: %.c
	$(CC) $(CFLAGS) $(filter %.c,$^) -o $@ -c

%: %.o
	$(CXX) $(filter %.o,$^) -o $@ $(LDFLAGS)

presum-demo: presum-demo.o presum.o
