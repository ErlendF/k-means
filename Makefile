build:
	gcc main.c output.c utils.c grid.c init.c pl_bf.c seq_bf.c pl_grid.c kd_tree.c seq_bf_kd_tree.c pl_bf_kd_tree.c seq_grid_kd_tree.c pl_grid_kd_tree.c seq_grid.c -lm -fopenmp -O2 -o k-means

test: build
	./k-means t

gprof:
	gcc main.c output.c utils.c grid.c init.c pl_bf.c seq_bf.c pl_grid.c kd_tree.c seq_bf_kd_tree.c pl_bf_kd_tree.c seq_grid_kd_tree.c pl_grid_kd_tree.c seq_grid.c -lm -fopenmp -O2 -o k-means && ./k-means p g && gprof k-means gmon.out > myprog_output

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

