#!/bin/bash

cmake ../Integrator
make
./Integrator
python3 display.py