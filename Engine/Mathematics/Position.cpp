//
//  Position.cpp
//  Renderer
//
//  Created by Narendra Umate on 5/5/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Position.h"

Position::Position()
{
	m_frameTime = 0.0;
	m_rotationY = 0.0f;
	m_leftTurnSpeed = 0.0;
	m_rightTurnSpeed = 0.0;
	m_clockTurnSpeed = 0.0;
	m_antiClockTurnSpeed = 0.0;
}

Position::~Position()
{}

void Position::setFrameTime(const double& time)
{
	m_frameTime = time;
}

void Position::getRotation(float& rotationX, float& rotationY, float & rotationZ)
{
	rotationX = m_rotationX;
	rotationY = m_rotationY;
	rotationZ = m_rotationZ;
}

void Position::turnUp(const bool& keyDown)
{
	if (keyDown)
	{
		m_upTurnSpeed += m_frameTime * 0.01f;

		if (m_upTurnSpeed > (m_frameTime * 0.15f))
		{
			m_upTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_upTurnSpeed -= m_frameTime * 0.005f;

		if (m_upTurnSpeed < 0.0f)
		{
			m_upTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationX -= m_upTurnSpeed;
}

void Position::turnDown(const bool& keyDown)
{
	if (keyDown)
	{
		m_downTurnSpeed += m_frameTime * 0.01f;

		if (m_downTurnSpeed > (m_frameTime * 0.15f))
		{
			m_downTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_downTurnSpeed -= m_frameTime * 0.005f;

		if (m_downTurnSpeed < 0.0f)
		{
			m_downTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationX += m_downTurnSpeed;
}


void Position::turnLeft(const bool& keyDown)
{
	if (keyDown)
	{
		m_leftTurnSpeed += m_frameTime * 0.01f;

		if (m_leftTurnSpeed > (m_frameTime * 0.15f))
		{
			m_leftTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime * 0.005f;

		if (m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationY -= m_leftTurnSpeed;
}

void Position::turnRight(const bool& keyDown)
{
	if (keyDown)
	{
		m_rightTurnSpeed += m_frameTime * 0.01f;

		if (m_rightTurnSpeed > (m_frameTime * 0.15f))
		{
			m_rightTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime * 0.005f;

		if (m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationY += m_rightTurnSpeed;
}

void Position::turnClockwise(const bool& keyDown)
{
	if (keyDown)
	{
		m_clockTurnSpeed += m_frameTime * 0.01f;

		if (m_clockTurnSpeed > (m_frameTime * 0.15f))
		{
			m_clockTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_clockTurnSpeed -= m_frameTime * 0.005f;

		if (m_clockTurnSpeed < 0.0f)
		{
			m_clockTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationZ -= m_clockTurnSpeed;
}

void Position::turnAntiClockwise(const bool& keyDown)
{
	if (keyDown)
	{
		m_antiClockTurnSpeed += m_frameTime * 0.01f;

		if (m_antiClockTurnSpeed > (m_frameTime * 0.15f))
		{
			m_antiClockTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_antiClockTurnSpeed -= m_frameTime * 0.005f;

		if (m_antiClockTurnSpeed < 0.0f)
		{
			m_antiClockTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationZ += m_antiClockTurnSpeed;
}
