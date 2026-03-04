This repository demonstrates a potential OpenGL driver bug with NVIDIA Blackwell GPUs on Windows 11. Using a texture view of a 2D depth-stencil texture array as a framebuffer attachment leads to a crash. The event viewer shows the following error:

> Unable to recover from a kernel exception. The application must close.
> 
> Error code: 3 (subcode 7)
>  (pid=17292 tid=228 nvidia-texture-view-bug.exe 64bit)
> 
> Visit http://www.nvidia.com/page/support.html for more information.

This seems to only affect textures with a depth-stencil format (depth-only and color formats are fine) and only if the view is of a non-zero layer index.

Tested and confirmed on the following system:
 - GPU: NVIDIA GeForce RTX 5070 Ti
 - Driver: 595.71
 - OS: Windows 11

 The crash does not occur on:
 - NVIDIA GeForce RTX 2080 Ti
 - NVIDIA GeForce RTX 4070 Ti SUPER

## Build
Clone the repository and run `build.cmd` (requires CMake):
```bat
git submodule update --init --recursive
cmake -B build
cmake --build build
```
