#!/usr/bin/env python3
from pathlib import Path

required = [
    "AGENTS.md",
    "README.md",
    "STATUS.md",
    "GAPS.md",
    "PARITY.md",
    "AI_DISCLOSURE.md",
    "docs/remotes.md",
    "docs/provenance.md",
    "docs/toolchain.md",
    "docs/traceability/first-push-families.md",
    "flake.nix",
    "Dockerfile",
    ".github/workflows/ci.yml",
    ".github/workflows/ci-native.yml",
    ".github/workflows/docker-smoke.yml",
    "Makefile",
    "src/main.cpp",
    "tests/test_cli.sh",
]

missing = [path for path in required if not Path(path).exists()]
if missing:
    raise SystemExit(f"missing required files: {missing}")

for removed in ["Cargo.toml", "Cargo.lock", "rust-toolchain.toml"]:
    if Path(removed).exists():
        raise SystemExit(f"rust scaffold file still present: {removed}")

print("cpp tranche validated")
