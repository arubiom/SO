#!/bin/bash

if [[ $# != 1 ]]
then
	echo "Error en el numero de parametros"
	exit 1
fi

top -n 1 -p $1 -b | cat > salida.txt
