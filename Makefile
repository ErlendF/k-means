build:
	gcc main.c output.c utils.c grid.c init.c parallel.c brute_force.c pgrid.c KD_tree.c brute_force_kd_tree.c -lm -fopenmp -O2 -o k-means

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

brute_seq_kd: build
	./k-means b k

test: build
	./k-means t

gprof:
	gcc main.c output.c utils.c grid.c init.c parallel.c brute_force.c pgrid.c -pg -lm -fopenmp -O2 -o k-means && ./k-means p g && gprof k-means gmon.out > myprog_output

cleanup:
	rm ./k-means