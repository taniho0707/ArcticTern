# BUILD

```
mkdir build_arm
cd build_arm
cmake  -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi-gcc_toolchain.cmake ..
make
```
