#!/bin/bash

touch "listahome-`date`"
ls ~ | cat > "listahome-`date`"

