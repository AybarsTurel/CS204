/*
	Sevki Aybars Turel 28238
*/
#ifndef _CAR_H
#define _CAR_H

using namespace std;

class Car
{
	private:
		
	public:
		Car(const double & , const double & , const double &); // constructor
		void display();
		double myFuel;
		double myInsurance;
		double myTotaLDistance;
};
#endif