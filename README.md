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
gcc main.c output.c utils.c grid.c init.c parallel.c brute_force.c pgrid.c kd_tree.c brute_force_kd_tree.c parallel_kd_tree.c grid_kd_seq.c grid_kd_par.c -lm -fopenmp -O2 -o k-means
```


*During the project, we used [Vscode liveshare](https://marketplace.visualstudio.com/items?itemName=MS-vsliveshare.vsliveshare). Therefore, the commit history is not representative of the distribution of work.*