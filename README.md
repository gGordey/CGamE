### CGamE
-------------

CGamE is an inovative game engine, where you use C/C++ to write code!
This means you can use external C/C++ libraries and do ANYTHING you want with your computer!

### Build engine localy
--------------

To build CGamE you need to install `Cmake`

```
mkdir build

cmake -S . -B build

cmake --build build
```

I would recomend using `"MinGW Makefiles"` and `gcc` because `MSVC` isn't usually happy about code :/

Use this for `gcc` on Windows

```
cmake -G "MinGW Makefiles" -S . -B build
```