#!/bin/bash

problem="maximum_period"

g++ -std=gnu++17 -O2 -Wall -pipe -static -o "${problem}" "${problem}.cpp"
