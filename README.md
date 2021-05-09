# k-means INF236 final project

## Usage

Commands:
```
make build
make test
make gprof
make cleanup
```

There are also various commands for running specific configurations.

Set threads:
```
export OMP_NUM_THREADS='x'
```

Building program manually:
```
gcc main.c output.c utils.c grid.c init.c pl_bf.c seq_bf.c pl_grid.c kd_tree.c seq_bf_kd_tree.c pl_bf_kd_tree.c seq_grid_kd_tree.c pl_grid_kd_tree.c seq_grid.c -lm -fopenmp -O2 -o k-means
```


*During the project, we used [Vscode liveshare](https://marketplace.visualstudio.com/items?itemName=MS-vsliveshare.vsliveshare). Therefore, the commit history is not representative of the distribution of work.*