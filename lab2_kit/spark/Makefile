TARGETS = spark spark_original
CFLAGS =  -lrt

all: $(TARGETS)

spark: spark.c
	$(CC) $(CFLAGS) spark.c -o spark

spark_o: spark_o.c
	$(CC) $(CFLAGS) spark_o.c -o spark_o

clean:
	rm -f $(TARGETS) *.o *.stderr *.stdout core *~
	rm *.out *.dat
	touch spark_plot.dat
