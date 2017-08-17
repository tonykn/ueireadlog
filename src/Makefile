HEADERS = readlog.h

default: ueireadlog

ueireadlog: readlog.c $(HEADERS)
	$(CC) $(CFLAGS) -O0 -o ueireadlog readlog.c

clean: ueireadlog
	rm -f ueireadlog
