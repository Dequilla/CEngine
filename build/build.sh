#!/bin/sh

echo "\n -CE- Building: \n"
echo " ██████╗███████╗███╗   ██╗ ██████╗ ██╗███╗   ██╗███████╗██╗"
echo "██╔════╝██╔════╝████╗  ██║██╔════╝ ██║████╗  ██║██╔════╝██║"
echo "██║     █████╗  ██╔██╗ ██║██║  ███╗██║██╔██╗ ██║█████╗  ██║"
echo "██║     ██╔══╝  ██║╚██╗██║██║   ██║██║██║╚██╗██║██╔══╝  ╚═╝"
echo " ██████╗███████╗██║ ╚████║╚██████╔╝██║██║ ╚████║███████╗██╗"
echo " ╚═════╝╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝╚═╝  ╚═══╝╚══════╝╚═╝"

# Create bin dir if it doesn't exist
if [ ! -d "$bin/" ]; then
    mkdir bin/
fi

# Enter bin
cd bin/

# If we want a clean build clear bin
if [ "$1" = "--clean" ]; then
    echo "\n\n -CE- Clearing previous build..."

    rm -rf *
fi

# Run cmake in our root folder where our topmost CMakeLists.txt file is
echo "\n -CE- Running cmake..."
cmake ../../

# Compile program
echo "\n -CE- Running make..."
make

# Now move resources files
echo "\n -CE- Moving resources..."
cd src/

if [ -d "$Resources/" ]; then
    rm -rf Resources/
fi

cp -r ../../../src/Resources/ Resources/

if [ -d "$Shaders/" ]; then
    rm -rf Shaders/
fi

cp -r ../../../src/Shaders/ Shaders/
