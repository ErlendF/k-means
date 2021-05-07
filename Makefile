build:
	gcc main.c output.c utils.c grid.c init.c parallel.c brute_force.c -lm -fopenmp -O2 -o k-means

run: build
	./k-means

parallel: build
	./k-means p

sequential: build
	./k-means s

both: build
	./k-means

cleanup:
	rm ./k-means