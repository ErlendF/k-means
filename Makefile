build:
	gcc main.c output.c utils.c grid.c init.c parallel.c brute_force.c pgrid.c kd_tree.c brute_force_kd_tree.c parallel_kd_tree.c grid_kd_seq.c grid_kd_par.c -lm -fopenmp -O2 -o k-means

test: build
	./k-means t

gprof:
	gcc main.c output.c utils.c grid.c init.c parallel.c brute_force.c pgrid.c -pg -lm -fopenmp -O2 -o k-means && ./k-means p g && gprof k-means gmon.out > myprog_output

cleanup:
	rm ./k-means


# For running various specific configurations

run: build
	./k-means

brute_pl: build
	./k-means p b

brute_seq: build
	./k-means s b

brute_both: build
	./k-means b p s

grid_seq: build
	./k-means s g

grid_pl: build
	./k-means p g

grid_both: build
	./k-means p s g

kd_seq: build
	./k-means k s

kd_pl: build
	./k-means k p

grid_kd_seq: build
	./k-means g k s

grid_kd_par: build
	./k-means g k p

