# ex: set ts=8 noet:

CFLAGS = -W -Wall -std=c99 -pedantic -Os
LDFLAGS =

histogram: histogram.o

clean:
	$(RM) histogram *.o
