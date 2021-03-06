// RaceCar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <thread>
#include <chrono>
#include <string>

#include "Display2.1.h"
#include "RandomGenerator.h"
#include "Road.h"
#include "Car.h"


int main()
{
	Display screen(60, 60);
	RandomGenerator<Generator::Linear> linearGen;
	Road track(&screen, &linearGen);
	Car car(&screen);

	unsigned long long score = 0;

	for (;true; score++)
	{
		screen.refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(200 - score > 60 ? 200 - score : 60));

		if (GetAsyncKeyState(VK_LEFT))
			car.left(track);
		if (GetAsyncKeyState(VK_RIGHT))
			car.right(track);

		track.updateRoad();
		if (car.checkCrash(track))
			break;

		track.updateScreen();
		car.updateScreen();
		screen.bufferOutput();
	}
	screen.refresh();

	std::wstring scoreText(L"Score: " + std::to_wstring(score));
	const CellCoords topLeft(screen.get_xScreen() / 2 - scoreText.size() / 2 - 2, screen.get_yScreen() / 2 - 2);
	const CellCoords bottomRight(screen.get_xScreen() / 2 + scoreText.size() / 2 + 2, screen.get_yScreen() / 2 + 2);
	screen.fill(topLeft, bottomRight, L' ');
	screen.box(topLeft, bottomRight, 0x2588);
	screen.writeInLoc(CellCoords(screen.get_xScreen() / 2 - scoreText.size() / 2, screen.get_yScreen() / 2), scoreText);

	screen.bufferOutput();

	
	getchar();
    return 0;
}