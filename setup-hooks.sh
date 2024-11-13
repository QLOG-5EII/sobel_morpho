#!/bin/bash

# execute this script right after having cloned the repo to setup the automatic format check

rm .git/hooks/pre-commit.sample

cp git-hooks/pre-commit .git/hooks/pre-commit

chmod +x .git/hooks/pre-commit

