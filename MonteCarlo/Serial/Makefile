SOURCES = monte_pi.c
TARGET = monte_pi
CFLAGS = -std=c99 -O2
#CC = /opt/local/bin/gcc-mp-7

omp:
	$(CC) $(SOURCES) $(CFLAGS) -fopenmp -o $(TARGET)

acc:
	$(CC) $(SOURCES) $(CFLAGS) -fopenacc -o $(TARGET)

run:
	./$(TARGET) 100000000

clean:
	rm $(TARGET)
