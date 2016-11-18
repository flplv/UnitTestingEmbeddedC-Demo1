# Dependencies #

## Tests Build ##

CppUTest will be downloaded and compiled by an script, the dependencies are the same CppUTest's.

## MSP430 Build  ##
- binutils-msp430
- gcc-msp430
- msp430-libc
- mspdebug

On Ubuntu, run `sudo apt-get install binutils-msp430 gcc-msp430 msp430-libc mspdebug`

# Project Files Structure #
- setup-cpputest.sh - Automatic download and compile cpputest inside the tree.

## Directories ##
- cpputest - The cpputest project, downloaded and compiled by `setup-cpputest.sh`
- lib - Where all .a or .so files will be stored during builds
- lib/X - X stands for a platform name of the build
- objs - Where all objects goes during builds
- objs/X - same as lib/X
- src - Where the application src goes, only platform independent code here.
- src_X - Where platform dependent code goes, where X is the name of the platform.

## Makefiles ##
- MakeX.mk - Is the Makefile that builds platform X
- Makefile - Is the root Makefile, it only forwards to children according to target.
