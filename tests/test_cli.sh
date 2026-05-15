#!/usr/bin/env bash
set -euo pipefail

BIN="${BIN:-./build/cpp-stakeholder}"
TMPDIR="${TMPDIR:-/tmp}"

"$BIN" --list-values >"$TMPDIR/cpp-list.json"
grep -q '"id": "code_analyzer"' "$TMPDIR/cpp-list.json"
grep -q '"rendererKey": "modern-core.platform_engineering"' "$TMPDIR/cpp-list.json"
grep -q '"registryId": "knowledge-retrieval"' "$TMPDIR/cpp-list.json"

"$BIN" --output-format json --focus-family code_analyzer --seed 123 >"$TMPDIR/cpp-code.json"
grep -q '"family": "code_analyzer"' "$TMPDIR/cpp-code.json"
grep -q '"rendererKey": "classic-six.code_analyzer"' "$TMPDIR/cpp-code.json"

"$BIN" --output-format json --focus-family platform-engineering --seed 456 >"$TMPDIR/cpp-platform-a.json"
"$BIN" --output-format json --focus-family platform_engineering --seed 456 >"$TMPDIR/cpp-platform-b.json"
diff -u "$TMPDIR/cpp-platform-a.json" "$TMPDIR/cpp-platform-b.json"

"$BIN" --output-format json --focus-family ai_inference_ops --seed 7 >"$TMPDIR/cpp-fallback.json"
grep -q '"rendererKey": "fallback.ai_governance"' "$TMPDIR/cpp-fallback.json"

if "$BIN" --experimental-provider local-demo >"$TMPDIR/cpp-exp.out" 2>"$TMPDIR/cpp-exp.err"; then
  echo "expected experimental-provider fail-fast" >&2
  exit 1
fi
grep -qi 'experimental provider' "$TMPDIR/cpp-exp.err"
