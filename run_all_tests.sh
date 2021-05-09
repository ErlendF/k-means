#!/bin/bash

echo "Deleting all performance files"
find . -name \performance.csv -type f -delete

rm results -r
mkdir results

cd 500pts
echo "Running 500pts test"
make test
cp performance.csv ../results/pts500.csv
cd ../1kpts
echo "Running 1kpts test"
make test
cp performance.csv results/pts1k.csv
cd ../2kpts
echo "Running 2,5kpts test"
make test
cp performance.csv ../results/pts2500.csv
cd ../5kpts 
echo "Running 5kpts test"
make test
cp performance.csv ../results/pts5k.csv
cd ../10kpts 
echo "Running 10kpts test"
make test
cd ../15kpts 
cp performance.csv ../results/pts15k.csv
echo "Running 15kpts test"
make test
cd ../30kpts
echo "Running 30kpts test"
make test
cp performance.csv ../results/pts30k.csv
cd ../50kpts
echo "Running 50kpts test"
make test
cp performance.csv ../results/pts50k.csv
cd ../100kpts
echo "Running 100kpts test"
make test
cp performance.csv ../results/pts100k.csv
cd ../200kpts
echo "Running 200kpts test"
make test
cp performance.csv ../results/pts200k.csv

cd ../1dim
echo "Running 1dim test"
make test
cp performance.csv results/dim1.csv
cd ../2dim
echo "Running 2dim test"
make test
cp performance.csv results/dim2.csv
cd ../3dim
echo "Running 3dim test"
make test
cp performance.csv results/dim3.csv
cd ../10dim
echo "Running 10dim test"
make test
cp performance.csv results/dim10.csv
cd ../100dim
echo "Running 100dim test"
make test
cp performance.csv results/dim100.csv
cd ../300dim
echo "Running 300dim test"
make test
cp performance.csv results/dim300.csv


cd ../1clust
echo "Running 1 cluster test"
make test
cp performance.csv results/clust1.csv
cd ../5clust
echo "Running 5 cluster test"
make test
cp performance.csv results/culst5.csv
cd ../10clust
echo "Running 10 cluster test"
make test
cp performance.csv results/culst10.csv
cd ../25clust
echo "Running 25 cluster test"
make test
cp performance.csv results/clust25.csv
cd ../50clust
echo "Running 50 cluster test"
make test
cp performance.csv results/clust50.csv
cd ../100clust
echo "Running 100 cluster test"
make test
cp performance.csv results/clust100.csv
cd ../500clust
echo "Running 500 cluster test"
make test
cp performance.csv results/clust500.csv
cd ../1000clust
echo "Running 1000 cluster test"
make test
cp performance.csv results/clust1000.csv
cd ../2kclust
echo "Running 2000 cluster test"
make test
cp performance.csv results/clust2000.csv
cd ../10kclust
echo "Running 10000 cluster test"
make test
cp performance.csv results/clust10k.csv
cd ../25kclust
echo "Running 25000 cluster test"
make test
cp performance.csv results/clust25000.csv
cd ../50kclust
echo "Running 50000 cluster test"
make test
cp performance.csv results/clust50000.csv
cd ..






