# Unix utilities

## Linux low-level API exploration

- [__ls__](linux/ls.cc) - exploration of iterating over directory without using `dirent` api

## Pure C++20 implementations

This section describes content of  directory [pure-cpp](./pure-cpp).

This tool set use C++ as build scripting language. First compile builder, then compile tools.

### Building

```console
$ cd pure-cpp
$ g++ build.cc -std=c++20 -o build
$ ./build
```

### Limitations

- **ls**: Cannot implement printing owner and group due to lack of such API
