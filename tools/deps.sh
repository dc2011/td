#!/bin/bash

OS=$(uname | tr '[A-Z]' '[a-z]')
echo -n "Detecting Operating System... "

if [ "$OS" == "windowsnt" ]; then
    echo "Windows"
    echo "How exactly are you even running this script? o.O"
    exit
elif [ "$OS" == "darwin" ]; then
    echo "Mac OSX"
    portsbin=$(which port)
    if [[ -z "$portsbin" ]]; then
        echo "You need MacPorts installed to run this script!"
        exit
    fi
    # We need sudo at this point to install from ports
    echo "Now we will install the necessary development libraries"
    echo "Please enter your password at the prompt"

    sudo $portsbin install libvorbis

    qmbin=$(which qmake)
    if [[ -a "$qmbin" ]]; then
        echo "You need the Qt4 Development Kit installed"
        exit
    fi

elif [ "$OS" == "linux" ]; then
    echo "Linux"
    echo "Now we will install the necessary development libraries"
    echo "Please enter your password at the prompt"

    if [ -f /etc/debian_version -o -f /etc/lsb-release ]; then
        # This is Ubuntu or Debian => apt-get

        sudo apt-get install g++ make libopenal-dev libvorbis-dev libogg-dev \
            qt4-dev-tools qt4-qmake libqt4-network

    elif [ -f /etc/fedora-release ]; then
        # This is Fedora => yum

        sudo yum install gcc-c++ make openal-soft-devel libvorbis-devel \
            libogg-devel

    elif [ -f /etc/arch-release ]; then
        # This is Arch => pacman

        sudo pacman -S gcc make openal libvorbis libogg

    else
        echo "OOPS! Packages could not be installed for your system!"
        echo "Please make sure you have the libvorbis development files"
    fi
fi

echo ""
echo ""

pkg=$(which pkg-config)
if [[ -z "$pkg" ]]; then
    echo -e "\033[31mYou do not have pkg-config installed.\033[m We wish you luck."
fi

if [ "$OS" == "darwin" ]; then
    echo "For an XCode Project, type \"qmake\"."
    echo "Otherwise, type \"qmake -spec macx-g++ && make\"."
elif [ "$OS" == "linux" ]; then
    echo "Now type \"qmake && make\"."
fi
