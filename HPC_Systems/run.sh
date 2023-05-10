#!/bin/sh

mkdir results
for j in 10 100 500 1000 1500
do
	qsub "$j.sge"
done
watch -n 2 -d qstat
