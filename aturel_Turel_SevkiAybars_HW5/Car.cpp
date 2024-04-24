/*
	Sevki Aybars Turel 28238
*/
#include <iostream>
#include "Car.h"

using namespace std;

Car::Car(const double & fuel, const double & insurance, const double & totalDistance) // constructor
	: myFuel(fuel), myInsurance(insurance), myTotaLDistance(totalDistance)
{ }


void Car::display() // It displays the info.
{
	
	cout << "Fuel Level: " << myFuel << endl;
	cout << "Insurance Fee: " << myInsurance << endl;
	cout << "Total distance that the car has travlled: " << myTotaLDistance << endl;
}