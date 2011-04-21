#!/bin/bash
OS=$(uname | tr '[A-Z]' '[a-z]')
if [ "$OS" != "linux" ]; then
    echo "Don't run this on non-Linux (this means you, Mac people)"
    exit
fi

wget --no-check-certificate https://gist.github.com/raw/930364/9c282f4c41a6512bc0b77888019e05c233454051/td.conf -O tmpconfig
cat tmpconfig >> ~/.config/dc2011/td.conf
rm tmpconfig
