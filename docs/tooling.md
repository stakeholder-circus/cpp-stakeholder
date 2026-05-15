# C++ Tooling

## Commands
- `python3 scripts/validate_scaffold.py`
- `make compiler-proof`
- `make test`
- `./build/cpp-stakeholder --list-values`
- `docker build -t cpp-stakeholder .`
- `docker run --rm cpp-stakeholder --list-values`

## Extended local checks
- Deterministic same-seed JSON diff for `platform_engineering`.
- Experimental-provider fail-fast smoke.
- C++17 warning-clean compile with `-Wall -Wextra -Werror`.

## Notes
- The Docker path is the reproducible Linux baseline.
- Native CI should still cover macOS and Linux compiler semantics.
