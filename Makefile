CFLAGS = -g -O3
LDFLAGS =
DEMOS = $(patsubst %.c,%,$(shell ls *-demo.c))

all: $(DEMOS)

clean:
	$(RM) *.o $(DEMOS)

%.o: %.c
	$(CC) $(CFLAGS) $(filter %.c,$^) -o $@ -c

%-demo: %-demo.o %.o
	$(CXX) $(filter %.o,$^) -o $@ $(LDFLAGS)
