//
//  Actor.cpp
//  Application
//
//  Created by Narendra Umate on 11/16/14.
//
//

#include "Actor.h"

namespace Engine
{
	Actor::Actor()
	:	m_position(0.0f, 0.0f, 0.0f)
	,	m_look(0.0f, 0.0f, 0.0f)
	,	m_right(0.0f, 0.0f, 0.0f)
	,	m_up(0.0f, 0.0f, 0.0f)
	{ }

	Actor::~Actor()
	{ }

	void Actor::getPosition(Vec3& position)
	{
		position = m_position;
	}

	void Actor::setPosition(const Vec3& position)
	{
		m_position = position;
	}

	void Actor::getAxes(Vec3& look, Vec3& right, Vec3& up)
	{
		look = m_look;
		right = m_right;
		up = m_up;
	}

	void Actor::setAxes(const Vec3& look, const Vec3& right, const Vec3& up)
	{
		m_look = look.normal();
		m_right = right.normal();
		m_up = up.normal();
	}

	void Actor::getView(Vec3& position, Vec3& look, Vec3& right, Vec3& up)
	{
		position = m_position;
		look = m_look;
		right = m_right;
		up = m_up;
	}

	void Actor::setView(const Vec3& position, const Vec3& look, const Vec3& right, const Vec3& up)
	{
		m_position = position;
		m_look = look;
		m_right = right;
		m_up = up;
	}
}
