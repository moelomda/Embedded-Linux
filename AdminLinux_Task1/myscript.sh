#!/bin/bash

cd ~
mkdir -p myDirectory

cd myDirectory || exit

mkdir -p secondDirectory

cd secondDirectory || exit

touch myNotePaper

cd ..

cp secondDirectory/myNotePaper .

mv myNotePaper myOldNotePaper

cd -
