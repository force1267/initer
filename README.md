# initer
simple `a = b c d` init-file reader

## add initer :
1. add `initer.h` and `initer.cpp` files to your project
2. include `initer.h` in you source
3. add `initer.cpp` to your build system (maybe `make`)

## use initer

### `initer` namespace
initer tools are inside initer namespace.
you can add `using namespace initer;` or prefix the tools with `initer::`

### `initer::cfg` type
it holds a key and its values.
each init option can have multiple values.
it's typedefed `pair<string, vector<string>>`

### `initer::ini` type
tasked to hold init value.
it's typedefed `vector<initer::cfg>`

### `initer::laod` function
`int load(string filename, ini& file, string& parse_error)`
it takes a filename and a [maybe not empty] `ini` refrence and fills it [even more].
if any error happens `parse_error` will be filled with a string and returns a non-zero integer.

### `initer::save` function
`int save(string filename, ini& file)`
it takes a filename and an `ini` refrence and saves it to file.
in case any error happens the function returns a non-zero integer.
it is not recommended to change an ini file programaticaly although the tool is provided.