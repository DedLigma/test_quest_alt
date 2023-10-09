# test\_quest\_alt
# About
This program is designed to generate json files containing information about packages contained in branches specified by the user.
- {branch1\_name}\_exclusive.json - contains all packages that are in the 1st specified branch, but which are not in the 2nd
- {branch2\_name}\_exclusive.json - contains all packages that are in the 2nd specified branch, but which are not in the 1st
- release\_diff\_{branch1\_name}\_and\_{branch2\_name}.json - contains information about packages whose version in 1 specified branch is greater than in 2

The program is divided into two parts. The main.cpp is responsible for data input and output and is essentially a CLI interface. The lib\_package\_handler.cpp is a dynamic library, which compares packages lists and generates a JSON response.

# Requirements
- [nlohmann/json](https://github.com/nlohmann/json) - JSON for modern C++.
- [libcurl](https://curl.se/libcurl/) - URL transfer library.
- [CMake](https://cmake.org/) - build system for C++.
- [gcc compiler](https://gcc.gnu.org/) - GCC or any other compiler such ass clang, etc.

# Install
### Alt Linux
Dependencies:
```
apt-get update
apt-get install gcc-c++ cmake nlohmann-json-devel libcurl-devel
```
after installing all dependencies, git clone or download .zip. 
Run this commands in directory with source files:
```
mkdir build
cmake ..
make
```
Now you can see alt\_test and libpackageshandler.so.
# How to use it
You can just run the executable file without arguments. In that case programm generate (or rewrite if exist): {branch1\_name}\_exclusive.json, {branch2\_name}\_exclusive.json, release\_diff\_{branch1\_name}\_and\_{branch2\_name}.json.
```
./alt_test
```
You can specify three files in arguments:
```
./alt_test file1.json file2.json file3.json
```
in this example, file1.json - {branch1\_name}\_exclusive.json, file2 - {branch2\_name}\_exclusive.json, file3 - release\_diff\_{branch1\_name}\_and\_{branch2\_name}.json.
Files do not need to have .json. However, it is worth considering that the output data will be JSON format.
After you enter the files names or just start the program, you should enter branch names:
```
Enter first branch name (e.g. p10, /p10, sisyphus, etc.).
p10
Enter second branch name.
/p9
```
You can enter them with '/' or without. If you entered an incorrect branch or something went wrong, the program will display a message with error information.

After that you just have to press Y or N if you don't enter files names and wait for the program to complete. 

# Output JSON files structure
The structure of the output JSON files is similar to the received ones. First, the number of packages is written in "length", and then an array "packages" with information about each of them.
Example:
```
{
  "length": 3,
  "packages": [
    {
      "arch": "aarch64",
      "buildtime": 1665497454,
      "disttag": "p10+307479.400.5.1",
      "epoch": 1,
      "name": "0ad",
      "release": "alt0_1_alpha.p10",
      "source": "0ad",
      "version": "0.0.26"
    },
    {
      "arch": "i586",
      "buildtime": 1632409606,
      "disttag": "p10+284327.3100.7.1",
      "epoch": 0,
      "name": "libfreeaptx-tools",
      "release": "alt1",
      "source": "libfreeaptx",
      "version": "0.1.1"
    },
    {
      "arch": "ppc64le",
      "buildtime": 1557876550,
      "disttag": "",
      "epoch": 0,
      "name": "splitvt",
      "release": "alt1.qa1",
      "source": "splitvt",
      "version": "1.6.6_6"
    }
  ]
}
```
