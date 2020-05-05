#!/bin/bash

set -e

SELF=$(dirname $(readlink -f $0))
tmp="tmp-git-deploy"

cd $SELF

echo ":: Cleaning previous build"
rm -rf ./"$tmp"
mkdir -p ./"$tmp"

echo ":: Building"
if git worktree list | grep "gh-pages" &>/dev/null; then
  echo ":: gh-pages already checked out, skipping"
else
  echo ":: Checking out gh-pages"
  git worktree add "$tmp" gh-pages
fi
mdbook build

echo ":: Copying generated files"
cp -rp book/* "$tmp"/

echo ":: Pushing to gh-page branch"
cd "$tmp"
git add -A
git commit -m "specification updated on $(date)"
git push origin gh-pages -f
cd -
