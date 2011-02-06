#!/bin/bash
isclean=$(git status --porcelain 2>/dev/null| wc -l)

if [[ -n $isclean ]]; then
    echo "You have uncommitted changes. DO NOT RUN THIS SCRIPT YET!"
    exit
fi

git filter-branch --index-filter 'git rm --cached --ignore-unmatch audio/example/2.ogg' HEAD

rm -rf .git/refs/original/
git reflog expire --expire=now --all
git gc --prune=now
git gc --aggressive --prune=now

echo "Push now: git push origin master --force"
