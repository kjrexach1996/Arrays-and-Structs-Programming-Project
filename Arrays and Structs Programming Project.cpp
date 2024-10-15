// Arrays and Structs Programming Project.cpp : This program will create a table based on multiple
// runners' performances in preparation for a marathon. The program will read a data file containing
// the names of the runners and how many miles each runner has completed for each day of the week, and
// it will display the infomation in the form of a table, showing additional information such as
// total miles completed for the week and the average number of miles completed in a day.

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const int numRunners = 5;
const int daysRan = 7;
const string dataFile = "runners.txt";

void getRunnerData(string runners[], int miles[][daysRan], string fileName);
void getMileData(int miles[][daysRan], int total[], double avg[]);
void dispRunnerData(string runners[], int miles[][daysRan], int total[], double avg[]);

int main()
{
	string runners[numRunners];
	int dailyMiles[numRunners][daysRan];
	int totalMiles[numRunners];
	double avgMiles[numRunners];

	getRunnerData(runners, dailyMiles, dataFile);
	
	getMileData(dailyMiles, totalMiles, avgMiles);

	dispRunnerData(runners, dailyMiles, totalMiles, avgMiles);
	return 0;
}

void getRunnerData(string runners[], int miles[][daysRan], string fileName)
{
	ifstream inputFile;
	inputFile.open(fileName);

	for (int row = 0; row < numRunners; row++)
	{
		inputFile >> runners[row];

		for (int col = 0; col < daysRan; col++)
		{
			inputFile >> miles[row][col];
		}
	}
	inputFile.close();
}

void getMileData(int miles[][daysRan], int total[], double avg[])
{
	for (int row = 0; row < numRunners; row++)
	{
		int totalMiles = 0;

		for (int col = 0; col < daysRan; col++)
		{
			totalMiles += miles[row][col];
		}
		total[row] = totalMiles;
	}

	for (int row = 0; row < numRunners; row++)
	{
		avg[row] = total[row] / 7.0;
	}
}

void dispRunnerData(string runners[], int miles[][daysRan], int total[], double avg[])
{
	cout << left << setw(20) << "Name";
	for (int day = 0; day < daysRan; day++)
	{
		cout << "Day " << left << setw(6) << (day + 1);
	}
	cout << left << setw(14) << "Total Miles" << left << setw(14) << "Avg Miles";
	cout << endl;

	for (int row = 0; row < numRunners; row++)
	{
		cout << left << setw(20) << runners[row];

		for (int col = 0; col < daysRan; col++)
		{
			cout << left << setw(10) << miles[row][col];
		}
		cout << left << setw(14) << total[row];
		cout << left << setw(14) << setprecision(2) << fixed << avg[row];
		cout << endl;
	}
}