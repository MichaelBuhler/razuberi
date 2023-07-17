#!/bin/sh
set -e

cd "$(dirname "$0")"/snapshots

grep --recursive --files-with-matches "$1" . | sed s/\.md//
