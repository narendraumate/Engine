//
//  Actor.h
//  Application
//
//  Created by Narendra Umate on 11/16/14.
//
//

#ifndef __Application__Actor__
#define __Application__Actor__

#include "../Mathematics/Vector.h"
#include "../Mathematics/Quaternion.h"

namespace Engine
{
	class Actor
	{
	public:
		Actor();
		~Actor();
		virtual void getPosition(Vec3& position);
		virtual void setPosition(const Vec3& position);
		virtual void getAxes(Vec3& look, Vec3& right, Vec3& up);
		virtual void setAxes(const Vec3& look, const Vec3& right, const Vec3& up);
		virtual void getView(Vec3& position, Vec3& look, Vec3& right, Vec3& up);
		virtual void setView(const Vec3& position, const Vec3& look, const Vec3& right, const Vec3& up);

	protected:
		Vec3 m_position;
		Vec3 m_look;
		Vec3 m_right;
		Vec3 m_up;
	};
}
#endif /* defined(__Application__Actor__) */
