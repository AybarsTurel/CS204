/*
	Sevki Aybars Turel 28238
*/

#ifndef _DRIVER_H
#define _DRIVER_H
#include "Car.h"
class Driver
{
	private:
		double myInitialBudget; // drivers' initial budget
		double spentMoney; // money that were spent by drivers
		Car &mySharedCar; // it represents the car that were used by the smae drivers.
	public:
		Driver (Car &, const double &);
		void drive(int);
		void repairCar(string);
		void display();
		void fullFuel();
};
#endif