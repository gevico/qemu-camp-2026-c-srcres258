#!/bin/bash

set -e

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
EXERCISE_DIR="${ROOT_DIR}/exercises/20_mybash"
BINARY="${EXERCISE_DIR}/bin/mybash"
COMMAND_FILE="${ROOT_DIR}/tests/mybash_cmd.sh"

if [ ! -x "$BINARY" ]; then
    echo "mybash binary not found or not executable: $BINARY" >&2
    exit 1
fi

if [ ! -f "$COMMAND_FILE" ]; then
    echo "command file not found: $COMMAND_FILE" >&2
    exit 1
fi

(
    cd "$EXERCISE_DIR"
    ./bin/mybash "$COMMAND_FILE"
)
