/*
	Sevki Aybars Turel 28238
*/

#include <iostream>
#include "Driver.h"
#include <string>

using namespace std;

Driver::Driver(Car & car, const double & Initialbudget) // constructor
	: mySharedCar(car), myInitialBudget(Initialbudget)
{ }

void Driver::drive(int km) // it calculates how much money spent by a certain driver. It shows the remaining fuel, it updates total distance that travel by a car and it updates the mney that driver has.
{
	mySharedCar.myTotaLDistance =  mySharedCar.myTotaLDistance + km;
	spentMoney = 0.25 * km;
	mySharedCar.myFuel = 300 - spentMoney;
	myInitialBudget = myInitialBudget - spentMoney;
}

void Driver::repairCar(string accidentType) // It takes the cost of the accident from driver budget and updates the insurance.
{
	if(accidentType == "SMALL")
	{
		myInitialBudget = myInitialBudget - 50;
		mySharedCar.myInsurance = mySharedCar.myInsurance + mySharedCar.myInsurance * 5 / 100;
		cout << "50$ is reduced from the driver's budget because of the SMALL accident" << endl;
		cout << "Yearly insurance fee is increased to " << mySharedCar.myInsurance << " because of the SMALL accident" << endl;
	}
	else if(accidentType == "MEDIUM")
	{
		myInitialBudget = myInitialBudget - 150;
		mySharedCar.myInsurance = mySharedCar.myInsurance + mySharedCar.myInsurance * 10 / 100;
		cout << "150$ is reduced from the driver's budget because of the MEDIUM accident" << endl;
		cout << "Yearly insurance fee is increased to " << mySharedCar.myInsurance << " because of the MEDIUM accident" << endl;
	}
	else if(accidentType == "LARGE")
	{
		myInitialBudget = myInitialBudget - 300;
		mySharedCar.myInsurance = mySharedCar.myInsurance + mySharedCar.myInsurance * 20 / 100;
		cout << "300$ is reduced from the driver's budget because of the LARGE accident" << endl;
		cout << "Yearly insurance fee is increased to " << mySharedCar.myInsurance << " because of the LARGE accident" << endl;
	}

}

void Driver::fullFuel() // it fulls he fuel.
{
	mySharedCar.myFuel = 300;
	cout << endl;
	cout << "Fuel is full." << endl;
	cout << endl;
}

void Driver::display()
{
	cout << "Driver Budget: " << myInitialBudget << endl;
}