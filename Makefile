build:
	gcc-10 main.c output.c utils.c grid.c init.c parallel.c brute_force.c KD_tree.c -lm -fopenmp -O2 -o k-means

run: build
	./k-means

parallel: build
	./k-means p

sequential: build
	./k-means s

both: build
	./k-means

gprof:
	gcc main.c output.c utils.c grid.c init.c parallel.c brute_force.c -pg -lm -fopenmp -O2 -o k-means && ./k-means && gprof a.out gmon.out > myprog_output

cleanup:
	rm ./k-means