# C++ Toolchain

- State: deterministic-first local validation complete
- Toolchain source: `built-in`

## Native commands
- `clang++ --version`
- `c++ --version`
- `python3 scripts/validate_scaffold.py`
- `make compiler-proof`
- `make test`
- `./build/cpp-stakeholder --list-values`
- `./build/cpp-stakeholder --output-format json --focus-family code_analyzer --seed 123`

## Docker commands
- `docker build -t cpp-stakeholder .`
- `docker run --rm cpp-stakeholder --list-values`
- `docker run --rm cpp-stakeholder --output-format json --focus-family platform_engineering --seed 123`

## Nix
- `/nix/var/nix/profiles/default/bin/nix --extra-experimental-features 'nix-command flakes' flake lock`
- `/nix/var/nix/profiles/default/bin/nix --extra-experimental-features 'nix-command flakes' flake show`

## Current limitation
- Full live-provider/runtime support is deferred. The deterministic runtime fails fast for provider flags.
