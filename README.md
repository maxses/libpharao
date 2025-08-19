# libpharao

<p align="center" width="100%">
    <img src="doc/16384.png">
</p>

## Overview

Libpharao (naming from 'pharaoh ant', a very small ant) is a library which helps
reducing the binary size of small bare metal microcontroller applications. It 
assumes that the  application is not multithreaded so some symbols for reentrance 
can be dropped. See below for further assumptions.

The library does not provide additional functions. It will just shrink the 
applications binary size.

The library is testet with tollchains based on newlib(nano) and picolib for 
STM32 controllers.

**Warning**
Don't use this library if you don't know what this is about. It can break your 
application.
A clean solution for small binarie sizes would be to use a propper toolchain with propper
libc-implementation/configuration like picolibc.

## Usecase

* Usage of microcontrollers with small flash size e.g. 16KB.
* Enhance application compile tests by using multiple available toolchains. Produced binaries don't even need to be functional.

## Savings

These are some example camparisons:

| Application | Toolchain      |Size<br>without libpharao | Size<br>with libpharao       | Delta |
| ----------- | -------------- | ------------------------ | ---------------------------- | ----- |
| Sample      | Ubuntu 22.04<br>gcc-arm-none-eabi 10.3.1<br>newlib(nano) | 24700 Bytes | 16524 Bytes | 8176 Bytes |
| Sample      | TCB 1.8<br>gcc-arm-none-eabi 14.2<br>picolibc | 15496 Bytes | 14648 Bytes | 848 Bytes |
| Sample      | Debian Forky<br>gcc-arm-none-eabi 14.2.1<br>newlib(nano) | 23452 Bytes | 16368 Bytes | 7084 Bytes |
| CANIO       | Debian Bookworm<br>gcc-arm-none-eabi 12.2.0<br>newlib(nano) | 23340 Bytes | 15488 Bytes | 7852 Bytes |

## Assumptions

* Signals are not used.
* Application will never shutdown correctly. The exit path will not finish but 
end up in an 'abort()'
* There is only a singe file, stdin/stdout.
* No data buffering on files. Every operation is direct.
* There is no multithreading. ISRs must not allocate memory or print stuff.
* Performance is not imnportant.

## Usage

The repository can be added to an existing project as git submodule. The 
submodule can be added as CMake subdirectory via "add_subdir".

Example snipet of CMakeLists.txt:
```
[...]
add_subdirectory( libpharao )

target_link_libraries(
   hello
   HALWrapper::HALWrapper
   pharao
)
[...]
```
