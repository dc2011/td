#!/bin/bash

music[0]="3.ogg"
music[1]="4.ogg"
music[2]="5.ogg"
music[3]="6.ogg"
url="http://dl.dropbox.com/u/20219175/sound"

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

    for i in 0 1 2 3
    do
	curl -O "$url/music/${music[i]}" -o "../sound/music/${music[i]}"
    done

elif [ "$OS" == "linux" ]; then
    echo "Linux"
    echo "Now we will download the sound files"

    mkdir -p '../sound/'
    mkdir -p '../sound/music'
    mkdir -p '../sound/sfx'

    for i in `seq 0 3`
    do
	wget "$url/music/${music[i]}" -O "../sound/music/${music[i]}"
    done


fi
