### CGamE
-------------

CGamE is an inovative game engine, where you use C/C++ to write code!
This means you can use external C/C++ libraries and do ANYTHING you want with your computer!

### Build engine localy
--------------

To build CGamE you need to install `Cmake`

```
cmake -S . -B build

cmake --build build
```

Use this for `gcc` on Windows

```
cmake -G "MinGW Makefiles" -S . -B build
```

If you want to build tests:

```
cmake -S . -B tests-build -DBUILD_CGE_TESTS=ON
```