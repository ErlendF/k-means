#!/bin/bash

# Used for running numerous automated tests

echo "Deleting all performance files"
find . -name \performance.csv -type f -delete

cd 500pts
echo "Running 500pts test"
make test
cd ../1kpts
echo "Running 1kpts test"
make test
cd ../2kpts
echo "Running 2,5kpts test"
make test
cd ../5kpts 
echo "Running 5kpts test"
make test
cd ../10kpts 
echo "Running 10kpts test"
make test
cd ../15kpts 
echo "Running 15kpts test"
make test
cd ../30kpts
echo "Running 30kpts test"
make test
cd ../50kpts
echo "Running 50kpts test"
make test
cd ../100kpts
echo "Running 100kpts test"
make test
cd ../200kpts
echo "Running 200kpts test"
make test

cd ../1dim
echo "Running 1dim test"
make test
cd ../2dim
echo "Running 2dim test"
make test
cd ../3dim
echo "Running 3dim test"
make test
cd ../10dim
echo "Running 10dim test"
make test
cd ../100dim
echo "Running 100dim test"
make test
cd ../300dim
echo "Running 300dim test"
make test

cd ../1clust
echo "Running 1 cluster test"
make test
cd ../5clust
echo "Running 5 cluster test"
make test
cd ../25clust
echo "Running 25 cluster test"
make test
cd ../50clust
echo "Running 50 cluster test"
make test
cd ../100clust
echo "Running 100 cluster test"
make test
cd ../500clust
echo "Running 500 cluster test"
make test
cd ../1000clust
echo "Running 1000 cluster test"
make test
cd ..

echo "Copying all performance files to reults"

cp 500pts/performance.csv results/pts500.csv
cp 1kpts/performance.csv results/pts1k.csv
cp 2kpts/performance.csv results/pts2k.csv
cp 5kpts/performance.csv results/pts5k.csv
cp 10kpts/performance.csv results/pts10k.csv
cp 15kpts/performance.csv results/pts15k.csv
cp 30kpts/performance.csv results/pts30k.csv
cp 50kpts/performance.csv results/pts50k.csv
cp 100kpts/performance.csv results/pts100k.csv



cp 1dim/performance.csv results/dim1.csv
cp 2dim/performance.csv results/dim2.csv
cp 3dim/performance.csv results/dim3.csv
cp 10dim/performance.csv results/dim10.csv
cp 100dim/performance.csv results/dim100.csv
cp 300dim/performance.csv results/dim300.csv

cp 1clust/performance.csv results/clust1.csv
cp 5clust/performance.csv results/culst5.csv
cp 10clust/performance.csv results/clust10.csv
cp 25clust/performance.csv results/clust25.csv
cp 50clust/performance.csv results/clust50.csv
cp 100clust/performance.csv results/clust100.csv
cp 500clust/performance.csv results/clust500.csv
cp 1000clust/performance.csv results/clust1000.csv
cp 2000clust/performance.csv results/clust2000.csv
cp 10000clust/performance.csv results/clust10000.csv
cp 25000clust/performance.csv results/clust25000.csv
cp 50000clust/performance.csv results/clust50000.csv