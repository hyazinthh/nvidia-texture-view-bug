@echo off
git submodule update --init --recursive
cmake -B build
cmake --build build