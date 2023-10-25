# TPWorms
Final project for the subject Taller de Programacion I

## Authors
| Nombre | Apellido | Padrón | Mail                |
| ------ | -------- | ------ | ------------------- |
| Facundo  | Huttin | 107854 | *** |
| Theo | Lijs | 109472 | *** |
| Ivan | Erlich | 105989 | ierlich@fi.uba.ar |

## SDL2
In order to properly run the game, you need to install the SDL2 library. To do so, run the following commands:
```
sudo apt-get install libsdl2-dev
```
Also you will need to incorporate the SDL2 submodule. To do so, run the following commands:
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
cd build
cmake ..
```
Now, you can run the makefile by running (inside the build folder):
```
make
```
This will generate the executable file. To run it, you need to run:
```
./server <port>
```
and
```
./client <host> <port>
```
where <port> is the port you want to use and <host> is the host you want to connect to. If you want to connect to the server in your own computer, you can use localhost as the host. For example:
```
./server 8080
```
and
```
./client 127.0.0.1 8080
```
If you want to add more libraries or flags to the makefile, you can do it by adding them to the CMakeLists.txt file. For example, if you want to add the flag -Wall, you need to add it to the line:
```
set(CMAKE_CXX_FLAGS "-g -std=c++11")
```
so it looks like:
```
set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wall")
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


