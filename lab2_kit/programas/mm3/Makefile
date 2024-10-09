TARGETS = mm3 mm3v2
PAPILIB_ALAMEDA=/run/current-system/sw/lib/libpapi.so
PAPILIB_TAGUS=/usr/local/lib/libpapi.so
CFLAGS=-O1

all: $(TARGETS)

mm3: mm3.c
ifeq ($(shell test -e $(PAPILIB_ALAMEDA) && echo -n yes),yes)
	$(CC) $(CFLAGS) mm3.c $(PAPILIB_ALAMEDA) -o mm3
else
	$(CC) $(CFLAGS) mm3.c $(PAPILIB_TAGUS) -o mm3
endif

mm3: mm3v2.c
ifeq ($(shell test -e $(PAPILIB_ALAMEDA) && echo -n yes),yes)
	$(CC) $(CFLAGS) mm3v2.c $(PAPILIB_ALAMEDA) -o mm3v2
else
	$(CC) $(CFLAGS) mm3v2.c $(PAPILIB_TAGUS) -o mm3v2
endif

clean:
	rm -f $(TARGETS) *.o *.stderr *.stdout core *~
