#!/bin/bash
DIR=`pwd`
DIR=${DIR:(-6)}
if [[ $DIR == "/tools" ]]; then
    echo "Run from the root directory please"
    exit
fi 

cd ./src
astyle -pfHUxjk1vz2uSr "*.cpp"
astyle -pfHUxjk1vz2uSr "*.h"
