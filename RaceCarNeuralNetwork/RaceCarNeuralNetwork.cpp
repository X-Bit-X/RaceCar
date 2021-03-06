// RaceCarNeuralNetwork.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <thread>
#include <chrono>
#include <string>

#include "Display2.1.h"
#include "RandomGenerator.h"
#include "Road.h"
#include "Car.h"
#include "NeuralNet3.1.h"


int main()
{
	Display screen(60, 60);
	RandomGenerator<Generator::Linear> linearGen;

	//Training
	/*for (std::vector<Agent> population(20, Agent(&linearGen, { 2, 3, 3 })); true; population = geneticAlgorithm(&linearGen, population))
		for (auto &val : population)
		{
			Road track(&screen, &linearGen);
			Car car(&screen);
			for (unsigned long long score = 0; true;)
			{
				screen.refresh();

				if (GetKeyState(VK_UP))
					std::this_thread::sleep_for(std::chrono::milliseconds(200 - score > 60 ? 200 - score++ : 60));

				Matrix<double> pred(val.getBrain().getPred(DataPackage({ car.distanceLeft(track), car.distanceRight(track) }, { 0 })));
				if (pred.accessLoc(0) > pred.accessLoc(1) > pred.accessLoc(2))
					car.left(track);
				else if (pred.accessLoc(2) > pred.accessLoc(1) > pred.accessLoc(0))
					car.right(track);

				track.updateRoad();
				if (car.checkCrash(track))
					break;

				val.increaseFit(1);

				if (val.getFitness() > 1000)
					val.getBrain().save("best");

				track.updateScreen();
				car.updateScreen();
				screen.bufferOutput();
			}
		}*/

	//Testing
	Agent driver(&linearGen, { 2, 3, 3 });
	driver.getBrain().open("best");
	Road track(&screen, &linearGen);
	Car car(&screen);
	for (long long score = 0; true;)
	{
		screen.refresh();

		std::this_thread::sleep_for(std::chrono::milliseconds(200 - score++ > 60 ? 200 - score : 60));

		Matrix<double> pred(driver.getBrain().getPred(DataPackage({ car.distanceLeft(track), car.distanceRight(track) }, { 0 })));
		if (pred.accessLoc(0) > pred.accessLoc(1) > pred.accessLoc(2))
			car.left(track);
		else if (pred.accessLoc(2) > pred.accessLoc(1) > pred.accessLoc(0))
			car.right(track);

		track.updateRoad();
		if (car.checkCrash(track))
			break;

		track.updateScreen();
		car.updateScreen();
		std::wstring scoreText(std::to_wstring(score));
		screen.writeInLoc(CellCoords(screen.get_xScreen() / 2 - scoreText.size() / 2, 1), scoreText);
		screen.bufferOutput();
	}


	getchar();
	return 0;
}