#!/bin/bash

qmk compile -kb keebio/bdn9/rev2 -km sirjson
cp -fv ./keebio_bdn9_rev2_sirjson.bin /mnt/c/temp/
