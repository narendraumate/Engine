//
//  Position.h
//  Renderer
//
//  Created by Narendra Umate on 5/5/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Renderer__Position__
#define __Renderer__Position__

class Position
{
public:
	Position();
	~Position();

	void setFrameTime(const double& time);
	void getRotation(float& rotationX, float& rotationY, float& rotationZ);

	void turnUp(const bool& keyDown);
	void turnDown(const bool& keyDown);
	void turnLeft(const bool& keyDown);
	void turnRight(const bool& keyDown);
	void turnClockwise(const bool& keyDown);
	void turnAntiClockwise(const bool& keyDown);

private:
	double m_frameTime;

	float m_rotationX;
	float m_rotationY;
	float m_rotationZ;

	double m_upTurnSpeed;
	double m_downTurnSpeed;

	double m_leftTurnSpeed;
	double m_rightTurnSpeed;

	double m_clockTurnSpeed;
	double m_antiClockTurnSpeed;
};

#endif /* defined(__Renderer__Position__) */
