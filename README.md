I designed a line-following car with obstacle avoidance using the frame of a parallax robot shield. 
While following a black track, the car constantly checks for objects in front of it. 
If there is an object detected, it checks left and right to see where the available space is. 
It then moves around the object towards the available space while signaling its waterfall-like blinkers. 
After avoiding the obstacle, the car returns to the track and continues to follow the line.


Inputs:
- 1 Ping sensor for object avoidance
- 2 Infrared sensors for line following

Outputs:
- 3 Servos
- 2 continuous for wheels
- 1 for rotating the ping sensor to check left and right
- Multiple LEDs for brake lights and blinkers


