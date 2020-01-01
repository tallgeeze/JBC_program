# JBC_program

HOW WE DIY A MOTOR WITH ANGLE FEEDBACK?

An experimental program, in which try to use DC common motors (usually only few dollars) and Hall effect sensors to build 
a motor, which is able to detect its current angle value as a feedback.

That means, with few bucks can we build a motor system which is widely used in robot-arms area. Imagine you diy an robotarm 
with for example Arduino and 3d-print, but it's really hard to have a precise motor which can also feedback angle or speed .
And those industry or professional motors are just too expensive and heavy for arduino or other diy system. 

Let me explain how it works : It's a reaaaaally simple system. We need a Arduino board, Uno is just Okay. Piece of magnet and 
also 3 Hall sensors. Of course, a DC motor. Basically it only need 2 digitalWrite port as the positive and negative of a 
simple DC motor. If your DC motor is strong, also a drive board is needed. Then we build a support rack for 3 round-
-placed Hall effect sensors. That means, the motor moves but the sensors are still.

Coding part is a little complex: 
[part1:calibration] First we need 181*3 values, in each row are 3 value from senor no.1-3 (v1,v2,v3), which is 
a voltage value read by analogRead function in Arduino. 181 rows means from degree 0 to 180, we got 180 sets value of 
v1,v2 and v3 while the motor was asked to move a little distance for 181 times.

[part2:calculation] Then we save those value sets into .csv file. And feed it in python code called calculation.py.
It will randomly split the whole data sets in 2 set, randomly sample in each subsets called : training set and test set.
Then, we use a linear regression--Newtown regression, try it from 1 dimension to 8, and calculate its polymerization R 
square. After doing cross validating, we can tell with dimension is pretty reasonable for our system. Then we chose a model which 
has best polymerization of this dataset and return it as a reference model called "best fit".

[part3:control_system] In this part we need feed the reference model generated in calibration program and fit and cross 
validated by calculation program. The model is represent as 3 sets of coefficient discribing 3 fitting curve of  the 3 Hall
effect sensors. With our newly generated model and angle to move (given in Serial channel), we can estimate the v1,v2,v3
values it shall have in demanded angle. Then we just move to the angle.

To sum it up, after every time we reboot or do any change to our system, the relationship between v1,v2,v3 at each degree
will be slightly different. So we have to firstly test to figure out the real v1,v2,v3 value of each degree in current time
and situation. Then we copy the long list of value to python program and calculate a reference model of how our v1,v2,v3 
values change when motor moves. Then we manually edit the control_system program, insert those coefficient of model.
Finally we are able to be relatively accurate while moving the DC motor with angle feedback

thank you for watching, if you have further interest, contact me at tallgeezee@gmail.com.

