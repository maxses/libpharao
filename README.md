# libpharao

<p align="center" width="100%" style="vertical-align: middle;">
    <img src="doc/canio_2.jpg">
    <img src="doc/16384.png">
</p>

## Overview

Libpharao (naming from 'pharaoh ant', a very small ant) is a library which helps
reducing the binary size of small bare metal microcontroller applications. It 
assumes that the  application is not multithreaded so some symbols for reentrance 
can be dropped. See below for further assumptions.

The library does not provide additional functionality. It will just shrink the 
applications binary size and may overload existing functions.

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
| Rufa        | Ubuntu 22.04<br>gcc-arm-none-eabi 10.3.1<br>newlib(nano) | 23712 Bytes | 15264 Bytes | 8448 Bytes |

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

## Configuration

Depending on the usecase some symbols should not get dropped. For example most 
tiny application do not ever free any memory because they just run their event 
loop forever. But some applications may need to be able to free memory.

To tweak the behaviour, features can be added or removed by 
the cmake list variables 'PHARAO_ADD_FEATURES' and 'PHARAO_ADD_FEATURES'. They 
have to be set before the 'add_subdirectory' for libpharao.

Example:

```
[...]
list( APPEND PHARAO_REMOVE_FEATURES remove_free remove_divide )
list( APPEND PHARAO_ADD_FEATURES replace_stdio )

add_subdirectory( libpharao )
[...]
```

Following features are available:

| Feature           | Description                                                             |
| ----------------- | ----------------------------------------------------------------------- |
| remove_free       | Remove symbols for freeing memory                                       |
| remove_signal (*) | Remove symbols for signals                                              |
| remove_impure (*) | Remove symbols reentrance                                               |
| replace_stdio (*) | Replace printf functions by own implementation from libpharao           |
| malloc (*)        | Drop some malloc symbols. Probably no impact.                           |
| remove_divide     | Remove symbols for division (e.g. cortex-m0). Probably not very useful. |

*(\*) Default setting*

