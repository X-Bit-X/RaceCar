#ifndef CAR
#define CAR

#include "Display2.1.h"
#include "Road.h"

class Car
{
public:

	Car(Display *screen) : m_coords{ screen->get_xScreen() / 2, screen->get_yScreen() - 20 }, m_screen{ screen } {}

	void updateScreen() const { m_screen->accessLoc(m_coords, FG_GREEN) = 0x2588; }

	void left() { if (m_coords.m_x != 0) m_coords.m_x--; }
	void right() { if (m_coords.m_x != 59) m_coords.m_x++; }

	bool checkCrash(Road &track)
	{
		for (const auto &val : track.coords())
			for (const auto &val2 : val)
				if (val2 == m_coords)
					return true;
		return false;
	}

private:

	CellCoords m_coords;
	Display *m_screen;
};

#endif // !CAR
