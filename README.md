# Unix utilities in pure C++20

This tool set use C++ as build scripting language. First compile builder, then compile tools

```console
$ g++ build.cc -std=c++20 -o build
$ ./build
```

## Limitations

- **ls**: Cannot implement printing owner and group due to lack of such API
