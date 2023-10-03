# cmake-asan

Demonstrates using compiler "sanitization" with CMake.

# Using Sanitization

Both compile AND link steps need the sanitization options!

```
-g -fsanitize=address -fno-omit-frame-pointer
```

MSVC [supports](https://learn.microsoft.com/en-us/cpp/sanitizers/asan?view=msvc-170)
sanitization, but only if you have the component installed. Also, there are some
really [weird](https://developercommunity.visualstudio.com/t/enabled-asan-address-sanitizer-for-x64-build-cause/1139763)
issues in older versions of the compiler, so make sure you're using the latest.

## Inside CMake

```
target_compile_options(asan-target PRIVATE -fsanitize=address -fno-omit-frame-pointer)
target_link_options(asan-target PRIVATE -fsanitize=address -fno-omit-frame-pointer)
```
