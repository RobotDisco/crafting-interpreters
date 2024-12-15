# Crafting Interpreters - Clox

Clox is the Java Implementation of the Lox language interpeter we are studying
in Robert Nystrom's book [Crafting
Interpreters](https://craftinginterpreters.com/).

This directory contains the codebase for the various chapter exercises the book
will ask us to do.

## Installation

I am using the Nix-based [devenv](https://devenv.sh) to set up my environments,
and now I am making you do the same :)

    # Install the nix package manager. https://nixos.org/download/ for details.
    sh <(curl -L https://nixos.org/nix/install) --daemon
    # I assume you want to learn as little about nix as possible; install devenv.
    nix-env -iA devenv -f https://github.com/NixOS/nixpkgs/tarball/nixpkgs-unstable

## Usage

    # Enter the development environment.
    devenv shell
    # Find out what make tasks we've run
    make help
    # For example, to build run the first chapter's Hello World code
	make hello_world && ./hello_world
	# You can also build all binaries by running cmake
	cmake --build .

### Tooling
Note that we use CMake to generate our Makefiles, so you have to edit the
`CMakeLists.txt` file if you add new binaries and run `cmake .` to regenerate
the makefile.

You should probably read the [CMake
Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html) to
learn how to use this tool, it's a lot nice than Make itself.

### Cleanup
Currently binaries and source files live in the same directory. This is
unfortunate, but I am still learning CMake, so at some point I will figure out
how they handle dedicated source and build directories.

Until then, you can use `make clean` to get rid of compilation artifacts and
binaries.

## Contributing

Unfortunately, I will be attempting to tackle all the exercises on my own. If
you provide possible solutions or improvements, I will gratefully look over them
at some point when I give up, and credit you if I adopt them.

## License

Both the book author's code and my exercise code are licensed under the
[MIT](https://choosealicense.com/licenses/mit/) license.
