#!/bin/bash
# Installer for custom cmake version

echo "Welcome to the custom cmake installer!"
read -p "Enter the wanted cmake version [ 3.13.3 ] : " WANTED_VERSION
WANTED_VERSION=${WANTED_VERSION:-3.13.3}

CURRENT_CMAKE_VERSION=$(cmake --version 2>/dev/null)
read CMAKE VERSION NUMBER REST <<< "$CURRENT_CMAKE_VERSION"

if [ "$NUMBER" != "$WANTED_VERSION" ]
then
    echo "Installing cmake $WANTED_VERSION for Linux ..."

    if [ -e /tmp/tempCMakeInstall ]
    then
        rm -rf /tmp/tempCMakeInstall
    fi
    mkdir /tmp/tempCMakeInstall/ ; cd /tmp/tempCMakeInstall/

    WANTED_VERSION_SPACES=$(echo $WANTED_VERSION | sed 's/\./ /g')
    read MAJOR MINOR BUILD <<< "$WANTED_VERSION_SPACES"

    wget "https://cmake.org/files/v$MAJOR.$MINOR/cmake-$MAJOR.$MINOR.$BUILD.tar.gz" &&
    tar -xzvf "cmake-$MAJOR.$MINOR.$BUILD.tar.gz" &&
    cd "cmake-$MAJOR.$MINOR.$BUILD/" &&
    ./bootstrap &&
    make -j4 &&
    make install &&
    echo "cmake successfully installed : " &&
    echo "cmake version : " &&
    cmake --version
else
    echo "cmake version $WANTED_VERSION already installed."
fi