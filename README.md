# TPWorms
Final project for the subject Taller de Programacion I

## Authors
| Nombre | Apellido | Padrón | Mail                |
| ------ | -------- | ------ | ------------------- |
| Facundo  | Huttin | 107854 | fhuttin@fi.uba.ar |
| Theo | Lijs | 109472 | tlijs@fi.uba.ar |
| Ivan | Erlich | 105989 | ierlich@fi.uba.ar |

## SDL2
In order to properly run the game, you need to install the SDL2 library. To do so, run the following commands:
```
sudo apt-get install libsdl2-dev
```

## QT5
In order to properly run the game, you need to install the qt5 library. To do so, run the following commands:
```
sudo apt-get install qtbase5-dev
sudo apt-get install qtmultimedia5-dev
sudo apt-get install gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly
```

## YAML
In order to properly run the game, you need to install the yaml library. To do so, run the following commands:
```
sudo apt-get install -y libyaml-cpp-dev
```

Also you will need to incorporate the SDL2 and BOX2dsubmodule. To do so, run the following commands:
```
git submodule update --init --recursive
```


### Cmake
To run the cmake script, you need to install cmake first. You can do it by running:
```
sudo apt-get install cmake
```
Then, you need to enter the build folder and run the cmake script. To do so, run:
```
mkdir build
cd build
cmake ..
```
TIP: If you already have a build folder with the cmake script already ran (if not, skip this command/TIP), you can run the 
following command to re-build the project using the cache and compile it at the same time without
needing to be at the build folder (you need to be at the root folder of the project):
```
cmake --build build/ -j 12
```
Now, you can run the make install command (with sudo needed) by running (inside the build folder):
```
sudo make install -j4
```
This will generate the executable file which you'll be able to execute it from anywhere you want (not necessarily from the build folder).


-----------------
NOTE: If you run make install, this command will create the executable file inside the build folder, but it will also copy it to /usr/local/bin, so you will be able to execute it from anywhere you want. And it will also copy files in /var/worms and /etc/worms.
WARNING/NOTE 2: Running only make and trying to execute the executable file will not work, you need to run make install first because the maps are being fetched from /var/worms and that is not customizable.

-----------------

To run it, you need to run:
```
worms_server <port>
```
and
```
worms <host> <port>
```
where <port> is the port you want to use and <host> is the host you want to connect to. If you want to connect to the server in your own computer, you can use localhost as the host. For example:
```
worms_server 8080
```
and
```
worms 127.0.0.1 8080
```
In those examples you will be using the port 8080 and connecting to the server in your own computer using the default configuration.
If you want to run your own configuration, you can create a config.yaml file wherever you want and run the server with the absolute path to the file. For example:
```
worms_server 8080 /home/user/config.yaml
```
Make sure that the config.yaml file is in the same format as the one in the external/config folder of the project.

If you want to add more libraries or flags to the makefile, you can do it by adding them to the CMakeLists.txt file. For example, if you want to add the flag -Wall, you need to add it to the line:
```
set(CMAKE_CXX_FLAGS "-g -std=c++17")
```
so it looks like:
```
set(CMAKE_CXX_FLAGS "-g -std=c++17 -Wall")
```
and then run the cmake script again.



### Pre-commit
To run the pre-commit script, you need to install pre-commit first. You can do it by running:
```
pip install pre-commit
```
Then, you need to install the pre-commit hooks in your local repository. To do so, run:
```
pre-commit install
```
Now, every time you commit, the pre-commit script will run and check for errors. If there are any, the commit will be aborted.
Also, if you want to run them before doing a commit, you can run them manually by running:
```
pre-commit run --all-files
```


### Testing
In order to run the tests, you will need to run the following commands in /build:
First you will need to run the cmake script for removing the cache and re-generate it with the testing flag:
```
rm CMakeCache.txt && cmake .. -DTESTING=ON
```
Then you will need to run the makefile:
```
sudo make install -j4
```
And finally you will need to run the tests:
```
GTEST_COLOR=1 ctest --tests-dir build --output-on-failure -j 12
```
-----------------
NOTE: Remember that to run the tests you will need to be in the build folder.

-----------------

For running the project normally once again you will need to run the cmake script for removing the cache and re-generate it without the testing flag:
```
rm CMakeCache.txt && cmake ..
```
Then you will need to run the makefile:
```
sudo make install -j4
```

### Configuration

The configuration file is located in the external/config folder of the project and is called config.yaml.
There you can change the game settings such as the worm's health, max players, etc.
If you want to run the server with your own configuration, you can create a config.yaml file wherever you want and run the server with the absolute path to the file as explained before. Anyways, here is an example of a custom config.yaml file located in the a arbitrary folder:
```
worms_server 8080 /home/user/Desktop/config.yaml
```
Remember that the config.yaml file needs to be in the same format as the one in the external/config folder of the project.
(Replace /home/user/Desktop/config.yaml with the absolute path to your config.yaml file)

Also, if you want to change the default external/config/config.yaml file in order to try different configurations, you will be able to do it but, because this file is set as a default configuration file, you will need to recompile the project in order to see the changes Once you made the changes, you can run:
```
sudo make install -j4
```
and then run the server with the default configuration file but with your new changes.

### Maps
If you want to add or modify maps, you will need to do it in the external/maps folder of the project and recomplie it. Once you made the changes, you can run:
```
sudo make install -j4
```
and then run the server with the default configuration file but with your new changes for the maps.
