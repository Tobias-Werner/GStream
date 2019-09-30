# install dependencies
sudo apt-get install cmake git lemon flex libsqlite3-0 libsqlite3-dev

# install Catch2 Test-Framework
cd ~
git clone https://github.com/catchorg/Catch2.git
cd Catch2
cmake -Bbuild -H. -DBUILD_TESTING=OFF
sudo cmake --build build/ --target install