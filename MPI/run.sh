#!/bin/sh

for slots in {1,2,3,4,5,6,7,8}; do
for threads in {1,2,3,4}; do
	sge=trapezoid_parallel.sge
	cp $sge aux.sge
	aux=aux.sge
	sed -i 's/$THREADS/'$threads'/g' $aux
	sed -i 's/$SLOTS/'$slots'/g' $aux
	qsub $aux
done;
done;
