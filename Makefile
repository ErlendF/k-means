build:
	gcc main.c output.c utils.c grid.c init.c parallel.c brute_force.c -lm -fopenmp -O2 -o k-means

run: build
	./k-means