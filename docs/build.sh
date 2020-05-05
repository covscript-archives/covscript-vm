#!/bin/bash

set -e

SELF=$(dirname $(readlink -f $0))
tmp="tmp-git-deploy"

cd $SELF

echo ":: Cleaning previous build"
rm -rf ./"$tmp"

echo ":: Building"
git worktree remove "$tmp" &>/dev/null || true
git worktree add "$tmp" gh-pages
mdbook build

echo ":: Copying generated files"
cp -rp book/* "$tmp"/

echo ":: Pushing to gh-page branch"
cd "$tmp"
git add -A
git commit -m "specification updated on $(date)"
git push origin gh-pages -f
cd -
