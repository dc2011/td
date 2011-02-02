#!/bin/bash

url="http://dl.dropbox.com/u/20219175"


##CHECK DIR
DIR=`pwd`

DIR=${DIR:(-6)}

if [[ $DIR != "/tools" ]]; then
    echo "Run from the tools dir please"
    exit
fi 

OS=$(uname | tr '[A-Z]' '[a-z]')
echo -n "Detecting Operating System... "

if [ "$OS" == "windowsnt" ]; then
    echo "Windows"
    echo "How exactly are you even running this script? o.O"
    exit

elif [ "$OS" == "darwin" ]; then
    echo "Mac OSX"
    echo "Now we will download the sound files"

    mkdir -p '../sound/'
    mkdir -p '../sound/music'
    mkdir -p '../sound/sfx'

    curl -O "$url/SOUNDINFO"

    while read line; 
    do  
	curl -O "$url/$line" -o "../$line"

    done < SOUNDINFO;

    rm SOUNDINFO

elif [ "$OS" == "linux" ]; then
    echo "Linux"
    echo "Now we will download the sound files"

    mkdir -p '../sound/'
    mkdir -p '../sound/music'
    mkdir -p '../sound/sfx'

    wget "$url/SOUNDINFO"

    while read line; 
    do  
	wget "$url/$line" -O "../$line"

    done < SOUNDINFO;

    rm SOUNDINFO

fi
