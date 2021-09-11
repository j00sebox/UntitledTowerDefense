#ifndef _COL_MAN
#define _COL_MAN

class CollisionManager
{
public:

	static bool check_collison(const float& x1, const float& y1, const float& x2, const float& y2, const float& rSqaured)
	{

		float f_result = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);

		if (f_result <= rSqaured)
			return true;
		else
			return false;
	}
};

#endif 

