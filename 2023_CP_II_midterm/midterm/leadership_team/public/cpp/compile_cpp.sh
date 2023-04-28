#!/bin/bash

problem="leadership_team"

g++ -std=gnu++17 -O2 -Wall -pipe -static -o "${problem}" "${problem}.cpp"
