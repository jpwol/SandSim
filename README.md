# Sand Simulator

A very simple (and very inefficient) cellular automata for basic particle types. Made for my own enjoyment, simulates sand/water/fire/stone/wood.

> [!WARNING]
> Currently, most functionality is broken as I've started rewriting most of the logic. Unfortunately I didn't know about branches at the time and as a result, the main branch has suffered as a consequence.

## Dependencies

This project uses [SDL2](https://www.libsdl.org/) for window creation and rendering.

### Installing SDL2

#### Windows

> [!NOTE]
> This project is set to link statically on Windows, so if you download the zip from SDL, make sure to change the linker flag. Otherwise, build SDL2 from source to get the static libraries.

Use the link to SDL2's webpage, and navigate to the Downloads/Releases tab. SDL recently released SDL3,
and I'm not sure on the backwards compatibility with SDL2, so it's safest to just fetch the SDL2 zip.

Alternatively, you may build it yourself if you want static libraries.

1. Navigate to [SDL](https://github.com/libsdl-org/SDL) on github
2. Run the commands below

```bash
git clone https://github.com/libsdl-org/SDL
cd SDL
git checkout SDL2
cd ..
mkdir build
cd build
cmake ../SDL
cmake --build .
```

This should build the static and dynamic versions of SDL in the `build` directory. Consult SDL's github page if any issues are encountered, or submit and issue.

Also be sure to adjust the `CMakeLists.txt` based on the path of your libraries/header files.

#### Linux

> [!NOTE]
> This project is set to dynamically link on Linux, so the easiest (and recommended) approach is just to get the SDL2 library from your package manager

<details>
    <summary>Arch</summary>

```bash
sudo pacman -S sdl2
```

</details>

<details>
    <summary>Void</summary>

```bash
sudo xbps-install -S SDL2-devel
```

</details>

<details>
    <summary>Debian</summary>

```bash
sudo apt install libsdl2-dev
```

</details>

## Building

Once you have the dependencies, simply run the following commands:

```bash
cmake . -B build
cd build
make
```

There are currently no options for a release build, but you're free to build in release mode.
