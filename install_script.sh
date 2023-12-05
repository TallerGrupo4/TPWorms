#!/bin/bash
sudo apt-get install libsdl2-dev
sudo apt-get install qtbase5-dev
sudo apt-get install qtmultimedia5-dev
sudo apt-get install gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly
sudo apt-get install -y libyaml-cpp-dev
git submodule update --init --recursive
sudo apt-get install cmake

mkdir build
cd build
cmake ..
sudo make install -j4