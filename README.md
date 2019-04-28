## Windows

Clone Box2D:

```
git submodule update --init
```

Install [premake](https://premake.github.io) version 5. Copy the executable to `bin/premake5.exe`.

Install [MinGW](http://www.mingw.org) or [Cygwin](https://www.cygwin.com/) and add to system `PATH`.

Make sure you have

1. A modern C++ compiler
2. GNU `make`
3. X11 `xorg-server`, `xinit`, and `libX11-devel`, `libXcursor-devel`, `libXrandr-devel`, `libXinerama-devel`
