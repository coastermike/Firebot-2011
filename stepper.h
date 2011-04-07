#ifndef STEPPER_H
#define STEPPER_H

void SetSpeed (int leftSpeed, int rightSpeed);
void SetSpeedDir (int leftSpeed, char dirL, int rightSpeed, char dirR);
void SetTurn (int speed, char direction, char angle);

void FollowRightWall(unsigned int speed);

#endif
