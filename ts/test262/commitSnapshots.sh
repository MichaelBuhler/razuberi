#!/bin/sh
set -e

cd "$(dirname "$0")"

git add "snapshots/**/*.snap"
git commit --message "test262: update snapshots"
git add "snapshots/**/*.md"
git commit --message "test262: update reports"
