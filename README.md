# DYNALOAD
A single-header cross-platform dynamic library loader for C &amp; C++

- #### REQUIRES [HARDFORM.H](https://github.com/PcNm/HARDFORM)

### USAGE
```c
#include "DYNALOAD.H"
```
wherever you want it in your code, but you'll also need to 
```c
#define DYNALOAD_IMPLEMENTATION
```
before including the header file in *one* C or C++ file to create the implementation.
<br>
```c
// One of your source files should have something that may look like this
#include ...  
#include ...  
#define DYNALOAD_IMPLEMENTATION  
#include "DYNALOAD.H"  
```
For more documentation, check out the header file and the sample.
<br><br>
*That's
all! Enjoy the dynamic library loader.*
<br>
###### Go ahead and create C wrapper-loaders for D3D11, PhysX, Vulkan, or whatever you like. :-)
<br>

#### STATUS
Version: **1.0** <br>
Platforms supported: Windows, Linux, Mac. <br>
It has been tested with: VS2017, GCC, CLANG, Pelles C, VC6.
<br><br>
