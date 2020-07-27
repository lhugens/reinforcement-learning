## About

This repository is a collection of reinforcement learning algorithms, as taught by David Silver in his lectures "Introduction to Reinforcement Learning", available for free at https://www.youtube.com/playlist?list=PLqYmG7hTraZDM-OYHWgPebj2MfCFzFObQ and https://www.davidsilver.uk/teaching/ .
## Windy Gridworld

A robot starts at S and has to arrive at G with the minimum number of steps. After each step that it takes, which can be left, down, up and right, wind pushes the robot up by the number of steps indicated below the grid.

```
[[0. 0. 0. 0. 0. 1. 1. 1. 1. 1.]
 [0. 0. 0. 0. 1. 0. 0. 0. 0. 1.]
 [0. 0. 0. 1. 0. 0. 0. 0. 0. 1.]
 [S  1. 1. 0. 0. 0. 0. G  0. 1.]
 [0. 0. 0. 0. 0. 0. 0. 0. 0. 1.]
 [0. 0. 0. 0. 0. 0. 0. 0. 1. 1.]
 [0. 0. 0. 0. 0. 0. 0. 0. 0. 1.]]
  0  0  0  1  1  1  2  2  1  0  ----> wind that blows up
```
 
 Example output of './windy-gridworld.py':
```
Last epsilon:  2.5e-07 

Sequence of states: 
 [[3, 0], [3, 1], [4, 1], [4, 2], [3, 3], [2, 4], [1, 5], [0, 6], [0, 7], [0, 8], [0, 9], [1, 9], [2, 9], [3, 9], [4, 9], [5, 9], [6, 9], [5, 8], [3, 7]] 

Trajectory: 
 [[0. 0. 0. 0. 0. 0. 1. 1. 1. 1.]
 [0. 0. 0. 0. 0. 1. 0. 0. 0. 1.]
 [0. 0. 0. 0. 1. 0. 0. 0. 0. 1.]
 [1. 1. 0. 1. 0. 0. 0. 1. 0. 1.]
 [0. 1. 1. 0. 0. 0. 0. 0. 0. 1.]
 [0. 0. 0. 0. 0. 0. 0. 0. 1. 1.]
 [0. 0. 0. 0. 0. 0. 0. 0. 0. 1.]] 

Steps histogram:
steps : no. of episodes with those steps 

18 : 1978
19 : 1
20 : 2
21 : 1
22 : 1
23 : 2
24 : 1
25 : 1
26 : 1
27 : 2
46 : 1
47 : 1
49 : 1
58 : 1
62 : 1
74 : 1
90 : 1
92 : 1
183 : 1
4232 : 1
```
