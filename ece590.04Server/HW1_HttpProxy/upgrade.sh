#! /bin/sh
sudo apt-get install g++-5 #install latest g++ 5
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-5 1 #set g++ 5 as default
