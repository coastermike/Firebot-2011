#ifndef STEPPER_H
#define STEPPER_H

void SetSpeed (int leftSpeed, int rightSpeed);
void SetSpeedDir (int leftSpeed, char dirL, int rightSpeed, char dirR);
void SetTurn (int speed, char direction, int angle);
void SetTurnFire (int speed, char direction, int angle);
void FollowRightWall(unsigned int speed);
void FollowRightWallMod (unsigned int speed);
#endif
