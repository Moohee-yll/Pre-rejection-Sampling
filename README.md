# Pre-rejection Sampling Towards Dilithium

This repository is developed based on the original [Dilithium](https://github.com/pq-crystals/dilithium) repository. We implemented the pre-rejection sampling technnique in the key generation process. The usage of this repository is the same as that of [Dilithium](https://github.com/pq-crystals/dilithium). We explain our experiments as follows.

## Instructions of our experiment

#### Rejections of the fourth condition

You can count the number of rejections of the fourth rejection condition by adding a counter in the `crypto_sign_signature()` function of the file `ref/sign.c`.

When testing, you can use the CMake tools. For example, on Linux, by calling 
```sh
mkdir build && cd build && cmake .. && make
```
then, all the produced executables are listed in directory `build/ref`. You can run 
```sh
 cd ./build/ref && ./test_dilithium2_ref
```
to obtain the results of the parameter set 1 (corresponding to the NIST security level 2). Similarlly, the executables `./test_dilithium3_ref` and `./test_dilithium5_ref` are shown for the parameter set 2 (corresponding to the NIST security level 3) and the parameter set 3 (corresponding to the NIST security level 5), respectively.

#### Test speed
To test the running speed of each subroutine (KeyGen, Sign and Verify), you need to use `Makefile` that we provided in both `./ref` and `./avx2` directories. For example, in `./ref`, you can run 
```sh
make speed
```
then, the executables `test_speed2`,`test_speed3` and `test_speed5` are generated in directory `./ref/test`. Run
```sh
cd ./ref/test && ./test_speed2
```
can obtain the cycles of each subroutine for parameter set 1 (corresponding to the NIST security level 2).

We also note that the default optimization level of C compiler is `O3`. To test the unoptimized code (without C compiler optimization), one can change the optimization level to `O0`. Specifically, in the third and fourth lines of the file `./ref/Makefile`, change the compilation parameter `-O3` to `-O0`.

### Other Prerequisites

Some of the test programs in this repository also require [OpenSSL](https://openssl.org) as Dilithium.

We refer to [Dilithium](https://github.com/pq-crystals/dilithium) for other usages like shared libraries.