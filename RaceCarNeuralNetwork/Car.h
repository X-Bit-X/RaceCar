#ifndef CAR
#define CAR

#include "Display2.1.h"
#include "Road.h"

class Car
{
public:

	Car(Display *screen) : m_coords{ screen->get_xScreen() / 2, screen->get_yScreen() - 20 }, m_screen{ screen } {}

	void updateScreen() const { m_screen->accessLoc(m_coords, FG_GREEN) = 0x2588; }

	void left(Road &track) { if (m_coords.m_x - 1 != track.coords()[m_screen->get_yScreen() - m_coords.m_y - 1][0].m_x) m_coords.m_x--; }
	void right(Road &track) { if (m_coords.m_x + 1 != track.coords()[m_screen->get_yScreen() - m_coords.m_y - 1][1].m_x) m_coords.m_x++; }

	bool checkCrash(Road &track)
	{
		for (const auto &val : track.coords()[m_screen->get_yScreen() - m_coords.m_y - 1])
			if (val == m_coords)
				return true;
		return false;
	}

	double distanceLeft(Road &track) { return m_coords.m_x - track.coords()[m_screen->get_yScreen() - m_coords.m_y - 1][0].m_x - 1; }
	double distanceRight(Road &track) { return track.coords()[m_screen->get_yScreen() - m_coords.m_y - 1][1].m_x - m_coords.m_x - 1; }

private:

	CellCoords m_coords;
	Display *m_screen;
};

#endif // !CAR
