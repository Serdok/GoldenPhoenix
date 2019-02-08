#!/bin/bash
# Installer for custom cmake version

echo "Welcome to the custom cmake installer!"
read -p "Enter the wanted cmake version [ 3.13.3 ] : " WANTED_VERSION
WANTED_VERSION=${WANTED_VERSION:-3.13.3}

CURRENT_CMAKE_VERSION=$(cmake --version 2>/dev/null)

WORDS=$(echo $CURRENT_CMAKE_VERSION | tr " " "\n")
CMPT=1
NUMBER=""
for word in $WORDS
do
    if [ "$CMPT" -eq 3 ]
    then
        NUMBER="$word"
        break
    else
        CMPT=$(expr $CMPT + 1)
    fi
done

if [ "$NUMBER" != "$WANTED_VERSION" ]
then
    echo "Installing cmake $WANTED_VERSION for Linux ..."

    if [ -e /tmp/tempCMakeInstall ]
    then
        rm -rf /tmp/tempCMakeInstall
    fi
    mkdir /tmp/tempCMakeInstall/ ; cd /tmp/tempCMakeInstall/

    WANTED_VERSION_SPACES=$(echo $WANTED_VERSION | sed 's/\./ /g')
    VERSION=$(echo $WANTED_VERSION_SPACES | tr " " "\n")
    CMPT=0
    MAJOR=0
    MINOR=0
    for number in $VERSION
    do
        if [ $CMPT -eq 0 ]
        then
            MAJOR=$number
            CMPT=$(expr $CMPT + 1)
        elif [ $CMPT -eq 1 ]
        then
            MINOR=$number
            break
        fi
    done

    wget "https://cmake.org/files/v$MAJOR.$MINOR/cmake-$WANTED_VERSION.tar.gz" &&
    tar -xzvf "cmake-$WANTED_VERSION.tar.gz" &&
    cd "cmake-$WANTED_VERSION/" &&
    ./bootstrap &&
    make -j4 &&
    make install &&
    echo "cmake successfully installed : " &&
    echo "cmake version : " &&
    cmake --version
else
    echo "cmake version $WANTED_VERSION already installed."
fi
