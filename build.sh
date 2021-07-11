#!/bin/bash

make annepro2/c18:default-layer-indicators && sudo annepro2-qmk-setup flash-update
sleep 3
sudo annepro2_tools --boot annepro2_c18_default-layer-indicators.bin
