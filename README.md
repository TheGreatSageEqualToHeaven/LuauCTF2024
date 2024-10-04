# Luau CTF 2024

Welcome to the Luau CTF challenge! This repository contains the necessary files to participate.

## Challenge Overview

The objective of this challenge is to open `notepad.exe` through the help of the `unsafe.loadbytecode` function.

### Luau fundamentals

`L` - Lua state  
`A`, `B`, `C`, `D`, `E` - Registers
`TValue` - Wrapper for all Lua values  
`TString` - Immutable objects used for Lua strings  
`L->namecall` - Lua state field that is a `TString` pointer, used when a userdata has a `__namecall` method  

### Instructions
1. Clone the repository.
2. Build the LuauCTF project.
3. Run Luau scripts by doing `LuauCTF.exe <filename>`.

### References

[Luau Deserializer](https://github.com/luau-lang/luau/blob/master/VM/src/lvmload.cpp)  
[Luau Interpreter](https://github.com/luau-lang/luau/blob/master/VM/src/lvmexecute.cpp)  
[lstate.h](https://github.com/luau-lang/luau/blob/master/VM/src/lstate.h)  
[L->namecall](https://github.com/luau-lang/luau/blob/master/VM/src/lstate.h#L273)  
[lobject.h](https://github.com/luau-lang/luau/blob/master/VM/src/lobject.h)  
[Closure](https://github.com/luau-lang/luau/blob/master/VM/src/lobject.h#L383-L411)  
[C closure function pointer](https://github.com/luau-lang/luau/blob/master/VM/src/lobject.h#L399)  
[lbaselib.cpp](https://github.com/luau-lang/luau/blob/master/VM/src/lbaselib.cpp)  
