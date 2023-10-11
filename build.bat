@echo off

pushd ..\build\
cl -Zi ..\code\algorithms.cpp 
popd