// Arrays and Structs Programming Project.cpp : This program will create a table based on multiple
// runners' performances in preparation for a marathon. The program will read a data file containing
// the names of the runners and how many miles each runner has completed for each day of the week, and
// it will display the infomation in the form of a table, showing additional information such as
// total miles completed for the week and the average number of miles completed in a day.

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

//User-defined constants; help define the maximum number of runners the program can process, how many
//days the runners ran, and the name of the text file containing the information.
const int MAX_RUNNERS = 10;
const int DAYS_RAN = 7;
const string dataFile = "runners.txt";

//Individual arrays ready to contain names and daily number of miles must exist and must be parallel; 
//file containing runner information must be available; function must also be able to receive integer
//value representing the maximum number of runners able to be processed.
//Function must return the number of runners in the text file for further array processing; name and 
//daily miles arrays must be updated, and file being processed must be closed.
int getRunnerData(string runners[], double miles[][DAYS_RAN], string fileName, int maximum);

//Function takes number of runners in file and reference to daily miles arrays (must not be altered);
//function also expects individual arrays containing total miles and average daily miles per runner to 
//exist; these arrays must be parallel.
//Total miles and average miles arrays will be updated.
void getMileData(const int numRunners, const double miles[][DAYS_RAN], double total[], double avg[]);

//Function expects to receive the number of runners in the file as well as references to all arrays to exist;
//all arrays must contain the appropriate information and must be parallel to accuarately build table.
//Function will output systematic table with various columns representing the names of each runner as well as
//the number of miles run per day, the total number of miles completed, and the average number of daily miles completed.
void dispRunnerReport(string runners[], const int numRunners, const double miles[][DAYS_RAN], double total[], double avg[]);

int main()
{
	//All arrays are initialized using constants
	string runners[MAX_RUNNERS];
	double dailyMiles[MAX_RUNNERS][DAYS_RAN];
	double totalMiles[MAX_RUNNERS];
	double avgMiles[MAX_RUNNERS];

	//Number of runners is obtained by the function to use for array processing
	//Function also updates runners[] and dailyMiles[] arrays
	int numRunners = getRunnerData(runners, dailyMiles, dataFile, MAX_RUNNERS);
	
	//Function updates totalMiles[] and avgMiles[] arrays
	getMileData(numRunners, dailyMiles, totalMiles, avgMiles);

	//Function outputs formatted table displaying runner names, daily miles, total miles,
	//and every miles completed for each runner.
	dispRunnerReport(runners, numRunners, dailyMiles, totalMiles, avgMiles);
	return 0;
}

int getRunnerData(string runners[], double miles[][DAYS_RAN], string fileName, int maximum)
{
	//Creates file object
	ifstream inputFile(fileName);
	if (!inputFile)
	{
		//Program ends if file could not open the file
		cout << "Could not open file.\n";
		exit(1);
	}
	
	//Initializes variable to begin counting number of runners in file
	int num = 0;

	//Loop repeats until either the end of the file or the maximum number
	//able to be processed is reached
	while (!inputFile.eof() && num < maximum)
	{
		//Stores runner names in runners[]
		inputFile >> runners[num];

		for (int col = 0; col < DAYS_RAN; col++)
		{
			//Stores miles per day per runner in dailyMiles[]
			inputFile >> miles[num][col];
		}
		//Increases runner count by 1
		num++;
	}
	//Closes file and returns number of runners
	inputFile.close();
	return num;
}

void getMileData(const int numRunners, const double miles[][DAYS_RAN], double total[], double avg[])
{
	//Initializes variable to calculate sum of daily miles per runner
	int totalMiles;

	//Per runner
	for (int row = 0; row < numRunners; row++)
	{
		//Counter resets
		totalMiles = 0;

		for (int col = 0; col < DAYS_RAN; col++)
		{
			//Adds daily miles to total for each day
			totalMiles += miles[row][col];
		}
		//Stores total in totalMiles[] per runner
		total[row] = totalMiles;

		//Stores average daily miles in avgMiles[] per runner
		avg[row] = total[row] / DAYS_RAN;
	}

}

void dispRunnerReport(string runners[], const int numRunners, const double miles[][DAYS_RAN], double total[], double avg[])
{
	//Creates "Name" heading
	cout << left << setw(20) << "Name";

	//Creates a heading for every day runners ran, given the number of days
	for (int day = 0; day < DAYS_RAN; day++)
	{
		cout << "Day " << left << setw(6) << (day + 1);
	}
	//Creates heading for total and average daily miles
	cout << left << setw(14) << "Total Miles" << left << setw(14) << "Avg Miles";
	cout << endl;

	//Per runner
	for (int row = 0; row < numRunners; row++)
	{
		//Displays runner name
		cout << left << setw(20) << runners[row];

		//Displays daily miles for each day
		for (int col = 0; col < DAYS_RAN; col++)
		{
			//Program checks to see if miles ran is greater than 100
			//to display the value correctly.
			cout << left << setw(10);
			if (miles[row][col] < 100)
				cout << setprecision(2);
			else
				cout << setprecision(3);
			cout << miles[row][col];
		}

		//Displays total miles
		//Program checks to see if miles ran is greater than 100
		//to display the value correctly.
		cout << left << setw(14);
		if (total[row] < 100)
			cout << setprecision(2);
		else
			cout << setprecision(3);
		cout << total[row];

		//Displays average daily miles
		cout << left << setw(14) << setprecision(2) << fixed << avg[row];

		//Disables fixed to display other values appropriately
		cout.unsetf(ios::fixed);
		cout << endl;
	}
}