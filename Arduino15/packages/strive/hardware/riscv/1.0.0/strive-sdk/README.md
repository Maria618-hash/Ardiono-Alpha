# README #

This repository, maintained by ISS, makes it easy to get started developing software for the Strive Series Boards. 

### Contents ###

* RISC-V Software Toolchain 
* RISC-V Debugging Toolchain
* Board Support Packages for Strive-1 and Development Kits
* A Few Example Programs

### Setting up the SDK ###

First, clone this repository:

```
git clone --recursive https://github.com/sifive/freedom-e-sdk.git
```

Ubuntu packages needed:

	$ sudo apt-get install autoconf automake libmpc-dev libmpfr-dev libgmp-dev gawk bison flex texinfo libtool libusb-1.0-0-dev make g++ pkg-config libexpat1-dev zlib1g-dev  

```

```
### Updating your SDK ###

If you'd like to update your SDK to the latest version:

```
```

If you would like to recompile the entire toolchain after performing the above:

```
```

### Benchmarking ###

#### Dhrystone ####

After setting up the software and debug toolchains, you can build and
execute everyone's favorite benchmark as follows:

- Compile the benchmark with the command `make software PROGRAM=dhrystone`.

```

<snip>

Microseconds for one run through Dhrystone: 1.3
Dhrystones per Second:                      729927.0
```

#### CoreMark ####

We cannot distribute the CoreMark benchmark, but following are instructions
to download and run the benchmark on the HiFive1 board:

- Download CoreMark from EEMBC's web site and extract the archive from
  http://www.eembc.org/coremark/download.php.
- Copy the following files from the extracted archive into the
  `software/coremark` directory in this repository:
  - `core_list_join.c`
  - `core_main.c`
  - `coremark.h`
  - `core_matrix.c`
  - `core_state.c`
  - `core_util.c`
- Compile the benchmark with the command `make software PROGRAM=coremark`.

### For More Information ###

Documentation, Forums, and much more available at

[dev.iss.com](https://dev.iss.com)
