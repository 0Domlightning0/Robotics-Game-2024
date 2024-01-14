// Game simulation of 2024 Crecendo
// FRC 2609
// FRC2024_GameSim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <random>
#include <windows.h>

using namespace std;


class Robot {
public:

	int AvgPickupTime, AvgTravelTime, time = 135, Count = 0, Pcount = 0, PointsScored = 0, PiecesScored = 0;

	bool HaveRing = false, AtSource = false;
};

// Robot that only Shoots in the speaker
class Shooter : public Robot {
public:
	int AvgShootingTime, Accuracy, Scount = 0, Consistancy;

	bool ShootingR = false, Amped = false;

	int ShooterGameSim() {

		// Creates a Random shooting Time 
		// ( (random number % range) + Variable )
		int RandShootingTime = (((rand() % (6 - Consistancy)) + AvgShootingTime + (4 - Consistancy)));

		int RandTravelTime = (((rand() % (6 - Consistancy)) + AvgShootingTime + (4 - Consistancy)));

		int RandPickupTime = (((rand() % (6 - Consistancy)) + AvgShootingTime + (4 - Consistancy)));

		for (int i = 0; i < time; i++) {

			int RandShootingTime = ((rand() % (7 - Consistancy) + AvgShootingTime));



			Count += 1;

			// Travelling to Source
			if (Count >= RandTravelTime and HaveRing == false) {
				AtSource = true;

			}

			// Picking Up Piece
			if (AtSource == true and HaveRing == false) {
				cout << "Picking up" << endl;
				Pcount += 1;


			}
			// Picking up from Source
			if (Pcount >= RandPickupTime and HaveRing == false) {
				cout << "Picked up!" << endl;
				HaveRing = true;
				AtSource = false;
				Count = 0;
				Pcount = 0;
			}

			// Travelling back and getting ready to Shoot
			if (Count >= RandTravelTime and HaveRing == true) {
				ShootingR = true;
			}

			// Ready to Shoot
			if (ShootingR == true) {
				cout << "Preparing to Shoot" << endl;
				Scount += 1;
			}

			// Aiming and Shooting 
			if (Scount >= RandShootingTime) {
				cout << "Shot Fired!" << endl;
				if (rand() % (100) < (10 * Consistancy + 55)) {
					PointsScored += 2;
					PiecesScored += 1;
					cout << "Point scored!" << endl;
				}
				else {
					cout << "Missed Ring!" << endl;
				}

				Count = 0;
				Scount = 0;
				ShootingR = false;
				HaveRing = false;
			}

			if (ShootingR == false and AtSource == false) {
				cout << "Driving" << endl;
			}

			Sleep(300);
		}
		return PointsScored;
	}
};

class AmpScorer : public Robot {

	int AvgScoringTime, Accuracy;
};


int main()
{
	srand(time(NULL));

	Shooter Shooter1;
	Shooter1.AvgPickupTime = 5;
	Shooter1.AvgShootingTime = 5;
	Shooter1.AvgTravelTime = 6;
	Shooter1.Consistancy = 4;
	cout << endl;
	cout << endl;
	cout << "This bot Scored:" << Shooter1.ShooterGameSim() << " Points" << endl;
	cout << endl;
	cout << endl;
	cout << "This bot Scored:" << Shooter1.PiecesScored << " Pieces" << endl;


}
