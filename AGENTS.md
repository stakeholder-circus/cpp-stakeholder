    # cpp-stakeholder AGENTS

    - Preserve imported Rust history and provenance.
    - Queue state: deterministic-first implementation in the next-20 autonomous sprint.
    - Origin: `git@github.com:stakeholder-circus/cpp-stakeholder.git`
    - Upstream: `https://github.com/giacomo-b/rust-stakeholder`
    - Deterministic normalized JSON is the first implementation target.
    - Missing behavior must fail fast and be recorded in `GAPS.md`.
    - No placeholder runtime behavior once implementation starts.

    ## Validation commands
    - `python3 scripts/validate_scaffold.py`
    - `make compiler-proof`
    - `make test`
    - `docker build -t cpp-stakeholder .`
