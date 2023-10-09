# test_quest_alt
# About
This program is designed to generate json files containing information about packages contained in branches specified by the user.
- first_have.json - contains all packages that are in the 1st specified branch, but which are not in the 2nd
- second_have.json - contains all packages that are in the 2nd specified branch, but which are not in the 1st
- release_difference.json - contains information about packages whose version in 1 specified branch is greater than in 2

# Requirements
- [nlohmann/json](https://github.com/nlohmann/json) - JSON for modern C++.
- [libcurl](https://curl.se/libcurl/) - URL transfer library.

# Install
## Alt Linux
Dependencies:
```
apt-get updateapt-get install gcc-c++ cmake nlohmann-json-devel libcurl-devel
```
after installing all dependencies, git clone or download .zip. In directory with source files:
```
mkdir build
cmake ..
make
```
# How to use it
You can just run the executable file without arguments. In that case programm generate (or rewrite if exist): first_have.json, second_have.json, release_difference.json.
```
./alt_test
```
You can specify three files in arguments:
```
./alt_test file1.json file2.json file3.json
```
in this example, file1.json - first_have.json, file2 - second_have.json, file3 - release_difference.json.

After you enter the files names or just start the program, you should enter branch names:
```
Enter first branch name (e.g. p10, /p10, sisyphus, etc.).
p10
Enter second branch name.
/p9
```
You can enter them with '/' or without. If you entered an incorrect branch or something went wrong, the program will display a message with error information

After that you just have to wait for the program to complete. 

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
