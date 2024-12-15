# Crafting Interpreters - Jlox

Jlox is the Java Implementation of the Lox language interpeter we are studying
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

I believe you can get by if you have a copy of Java 8+ and gradle, however you would
like to install them.

## Usage

    # Enter the development environment.
    devenv shell
    # Find out what gradle tasks we've run
    gradle tasks
    # For example, to build run the first chapter's Hello World code
    gradle :chapter01:run

## Contributing

Unfortunately, I will be attempting to tackle all the exercises on my own. If
you provide possible solutions or improvements, I will gratefully look over them
at some point when I give up, and credit you if I adopt them.

## License

Both the book author's code and my exercise code are licensed under the
[MIT](https://choosealicense.com/licenses/mit/) license.
