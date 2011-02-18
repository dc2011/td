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
    mkdir -p '../img'

    curl -O "$url/SOUNDINFO"

    while read line; 
    do  
	fname=`echo "$line" | cut -d " " -f 3`
	fhash=`echo "$line" | cut -d " " -f 1`

	if [ -e "../$fname" ] 
	    then
	    CHKSUM=`md5 "../$fname" | cut -d "=" -f 2 | tr " " ""`
	else
	    CHKSUM=""
	fi

	if [ "$fhash" != "$CHKSUM" ]
	    then
	    echo "$fname Out of date....Updating"
	    curl $url/$fname > ../$fname
	else
	    echo "$fname Up to Date"
	fi

    done < SOUNDINFO;
    rm SOUNDINFO

elif [ "$OS" == "linux" ]; then
    echo "Linux"
    echo "Now we will download the sound files"

    mkdir -p '../sound/'
    mkdir -p '../sound/music'
    mkdir -p '../sound/sfx'
    mkdir -p '../img'

    wget "$url/SOUNDINFO"

    while read line; 
    do  
	fname=`echo "$line" | cut -d " " -f 3`
	fhash=`echo "$line" | cut -d " " -f 1`

	if [ -e "../$fname" ]; 
	then
	    CHKSUM=`md5sum "../$fname" | cut -d " " -f 1`
	else
	    CHKSUM=""
	fi

	if [ "$fhash" != "$CHKSUM" ];
	then
	    echo "$fname Out of date....Updating"
	    wget "$url/$fname" -O "../$fname"
	else
	    echo "$fname Up to Date"
	fi

    done < SOUNDINFO;
    rm SOUNDINFO

fi
