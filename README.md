# Compass
Determine the compass heading of an object given its yaw, pitch, and roll.

NOTE: For the sake of simplicity I assume that the degrees for yaw and pitch are clockwise.

Some feedback I’d have for the creator of the API is to specify whether the device’s orientation is relative to the Earth or to itself. If it’s relative to itself then the order in which we should read the data is extremely important since different permutations can yield a different orientation. For my solution I assumed the former to be true since the prompt mentioned “physical space.” I determined the object’s orientation by first calculating the yaw and then the pitch. I dismissed the roll as it would have no influence on the objects compass heading. One final note is that I think the API should allow a flag that standardizes the degrees to be between 0 and 359 degrees. 
