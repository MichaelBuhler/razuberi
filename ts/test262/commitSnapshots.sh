#!/bin/sh
set -e

cd "$(dirname "$0")"

git commit --message "test262: update snapshots" -- "snapshots/**/*.snap"
git commit --message "test262: update reports" -- "snapshots/**/*.md"
