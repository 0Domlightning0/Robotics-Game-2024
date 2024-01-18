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

	int ShooterGameSimTele() {

		// Creates a Random shooting Time 
		// ( (random number % range) + Variable )
		int RandShootingTime = (((rand() % (6 - Consistancy)) + AvgShootingTime));

		int RandTravelTime = (((rand() % (6 - Consistancy)) + AvgTravelTime));

		int RandPickupTime = (((rand() % (6 - Consistancy)) + AvgPickupTime));


		PointsScored = 0;
		Count = 0;
		Scount = 0;
		ShootingR = false;
		HaveRing = false;
		AtSource = false;

		for (int i = 0; i < time; i++) {

			Count += 1;

			// Travelling to Source
			if (Count >= RandTravelTime and HaveRing == false) {
				AtSource = true;

			}

			// Picking Up Piece
			if (AtSource == true and HaveRing == false) {
				//cout << "Picking up" << endl;
				Pcount += 1;


			}
			// Picking up from Source
			if (Pcount >= RandPickupTime and HaveRing == false) {
				//cout << "Picked up!" << endl;
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
				//cout << "Preparing to Shoot" << endl;
				Scount += 1;
			}

			// Aiming and Shooting 
			if (Scount >= RandShootingTime) {
				//cout << "Shot Fired!" << endl;
				if (rand() % (100) < (10 * Consistancy + 50)) {
					PointsScored += 2;
					PiecesScored += 1;
					//cout << "Point scored!" << endl;
				}
				else {
					//cout << "Missed!" << endl;
				}

				Count = 0;
				Scount = 0;
				ShootingR = false;
				HaveRing = false;
			}

			if (ShootingR == false and AtSource == false) {
				//cout << "Driving" << endl;
			}

			//Sleep(100);
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

	int minscore = 12, maxscore = 24, rows = 0;

	int Iterations = 1000, Simualtions = 500;

	double array[1000][3], resaults[50][3];

	double Total = 0, TotalPickup = 0, TotalShooting = 0, TotalTravel = 0;

		for (int i = 0; i < Iterations; i++) {

			Total = 0;

			Shooter1.AvgPickupTime = ((rand() % (9))+1);
			Shooter1.AvgShootingTime = ((rand() % (9))+1);
			Shooter1.AvgTravelTime = ((rand() % (9))+2);
			Shooter1.Consistancy = 3;

			for (int j = 0; j < Simualtions; j++) {
				Total += Shooter1.ShooterGameSimTele();

			}

			if ((Total / Simualtions) >= minscore and (Total / Simualtions) <= maxscore) {

				array[i][0] = Shooter1.AvgPickupTime;
				array[i][1] = Shooter1.AvgShootingTime;
				array[i][2] = Shooter1.AvgTravelTime;
				//cout << array[i][0] << endl;

				TotalPickup += array[i][0];
				TotalShooting += array[i][1];
				TotalTravel += array[i][2];

				rows += 1;
				//cout << rows << endl;
			}




		}

		
		cout << "Score Range " << minscore << " To " << maxscore << ":   Average Pickup: " << TotalPickup / rows << "   Average Shooting: " << TotalShooting / rows << "    Average Travel: " << TotalTravel / rows << endl << endl;

	
}
