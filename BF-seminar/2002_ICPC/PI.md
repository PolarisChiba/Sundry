# Merrily, We Roll Along! 

[Link](https://vjudge.net/contest/538106#problem/I)

## Description

Given $n$ horizontal and vertical continuous segments with $x$ coordinat acsending.

It is guranteed the first and the last segments are horizontal.

There's a ball at the left end point of the first segment at first.

The ball will go to the right end point of the last segment while remaining contact with the segments.

Note that the ball may go along a straight line or rotate around a corner.

It's guranteed that the ball will not be tangent to two vertical segments simutaneously.

Find the distance moved by the center of the ball.

## Input Format

$1\le n\le 100$

The length of each segments are given in real number.

The length of the first and the last segments are strictly larger than the radius of the ball.

## Output Format

Output the distance moved by the center of the ball with $3$ digits to the right of the decimal point.

## Solution

For each corner and segment, draw the track of the ball moves if there's nothing blocks. 

Then iterate other corner and segment to block the track. 

Find the length left and sum them up.

Complexity: $O(n^2)$

## AC code

Not yet AC.