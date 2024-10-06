TARGETS = spark spark_original
CFLAGS =  -lrt

all: $(TARGETS)

spark: spark.c
	$(CC) $(CFLAGS) spark.c -o spark

spark_original: spark_original.c
	$(CC) $(CFLAGS) spark_original.c -o spark_original

clean:
	rm -f $(TARGETS) *.o *.stderr *.stdout core *~
	rm *.out *.dat
	touch spark_plot.dat
