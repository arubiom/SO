#!/bin/bash

numero=0

for i in $(seq 1 $1)
do
	let numero++
done
echo $numero
