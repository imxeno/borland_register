# borland_register
A translation layer for calling functions using Borland's `register` calling convention from `cdecl` C++ scope and vice versa.

## Example usage
```c++
// Warning: the translator MUST be in scope!
// If it goes out of scope, all proxy functions bound to it will be deallocated
borland_register::translator brt;

// Generating a proxy for an exported function compiled with Delphi 7 Personal

HMODULE hModule = LoadLibrary("Example.dll");
FARPROC farProc = GetProcAddress(hModule, "FunctionName");

typedef uint32_t(*delphi_function_3)(uint32_t, uint32_t, uint32_t);
delphi_function_3 func = (delphi_function_3)brt.cdecl_to_register(farProc, 3);

// Calling the proxy is as simple as
func(1, 2, 3);

// You can also generate a proxy that will translate it the other way using translator::register_to_cdecl
```
