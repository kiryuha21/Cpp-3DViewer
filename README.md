# 3D viewer

## Overview

This project was made to render object(.obj) files into 3D-models. 
It is written in C++ language with the GTKMM+ 3.0 framework. 
It was designed with MVC pattern, and its structure contains such design patterns as builder, facade and singleton. 

3D-model supports such operations as loading from .obj file, three axis rotation, scaling and movement.
In the interface you can accordingly choose/enter

* Object file
* XYZ scaling delta
* XYZ rotating delta
* XYZ movement delta

## Main functions

Project contains classes to perform affine transformations, use gnuplot, parse from file/write to file object model and to build requests for data changes

## Testing

All tests are present in `tests/` folder and are made with GTest library

## Samples

.obj files are forbidden by immutable .gitignore, but you can find them in internet by yourself

