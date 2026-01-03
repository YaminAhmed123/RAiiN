# HATE Engine  ![Vulkan](https://img.shields.io/badge/Vulkan-API-orange?logo=vulkan&style=flat-square)

## Notes
- This engine is still in alpha and probably will stay in alpha for a long time.
- Abstraction layer might break sooner or later.
- This project was created to dive into Vulkan and learn about CG Math and GPU execution.

## Features
- This a really simple game engine to build 3D games.
- Additinal info coming soon.

## How to compile ? ![GCC](https://img.shields.io/badge/GCC-GNU-red)  ![Clang](https://img.shields.io/badge/Clang-LLVM-blue)  ![MSVC](https://img.shields.io/badge/MSVC-Visual%20Studio-0078D7)   ![Meson](https://img.shields.io/badge/Meson-Build%20System-339999)


WARNING THIS SCETION STLL LACKS A LOT OF INFORMATION!


In order to compile the engine from source you must have [Meson](https://mesonbuild.com/) installed on your system.
After you have done this you can clone the repo by doing this:
```powershell
git clone https://github.com/YaminAhmed123/HATE.git
```
Now you can continue with building

```powershell
cd HATE
meson setup build
cd build
meson compile
```
