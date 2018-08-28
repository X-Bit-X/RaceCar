#ifndef ROAD
#define ROAD

#include <deque>
#include <array>

#include "Display2.1.h"
#include "RandomGenerator.h"

class Road
{
public:

	Road(Display *screen, RandomGenerator<> *randGen) : m_screen{ screen }, m_randGen{ randGen }
	{
		for (int i = m_screen->get_yScreen() - 1; i >= m_screen->get_xScreen() - 30; i--)
			m_coords.push_back({ CellCoords(m_screen->get_xScreen() / 2 - m_trackWidth / 2, i), CellCoords(m_screen->get_xScreen() / 2 + m_trackWidth / 2, i) });
		genRoad();
	}

	void updateScreen() const
	{
		for (unsigned int i = 0; i < m_coords.size() - 1; i++)
			for (const auto &val : m_coords[i])
				m_screen->accessLoc(val) = 0x25A0;
	}

	void genRoad()
	{
		for (int i = m_screen->get_yScreen() - m_coords.size() - 1; i >= -1; i--)
		{
			const char randNum = m_randGen->randNumber<char>(m_coords.back()[0].m_x == 0 ? 0 : -1, m_coords.back()[1].m_x == m_screen->get_xScreen() - 1 ? 0 : 1);
			m_coords.push_back({ CellCoords(m_coords.back()[0].m_x + randNum, i), CellCoords(m_coords.back()[1].m_x + randNum, i) });
		}
	}

	void updateRoad()
	{
		for (auto &val : m_coords)
			for (auto &val2 : val)
				val2.m_y++;
		m_coords.pop_front();
		genRoad();
	}

	const std::deque<std::array<CellCoords, 2>>& coords() const { return m_coords; }

private:

	std::deque<std::array<CellCoords, 2>> m_coords;
	Display *m_screen;
	RandomGenerator<> *m_randGen;
	const char m_trackWidth = 7;
};

#endif // !ROAD
