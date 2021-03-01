#!/bin/bash

if [ -d "Tengo prioridad c" ]
then 
	if [ -d "Tengo prioridad d" ]
	then
		cd "Tengo prioridad c"/"Tengo prioridad d"
		mkdir "Tengo prioridad e"
	fi
fi
