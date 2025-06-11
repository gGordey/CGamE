### CGamE
-------------

CGamE is an inovative game engine, where you use C/C++ to write code!
This means you can use external C/C++ libraries and do ANYTHING you want with your computer!

### Build engine localy
--------------

To build CGamE you need to install `Cmake`, `gcc` and get binary files `lib/glad.dll` and `lib/glwf3.dll`.

```
mkdir build

cmake -G "MinGW Makefiles" -S src -B build

cmake --build build
```
I would recomend using `"MinGW Makefiles"` and `gcc` because `MSVC` isn't happy about code :/ 
 