#!/bin/sh
find . -name '._*' -exec rm '{}' ';'
find . -name '.DS_Store' -exec rm '{}' ';'
