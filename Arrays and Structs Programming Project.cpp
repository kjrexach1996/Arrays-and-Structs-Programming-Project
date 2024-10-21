// Arrays and Structs Programming Project.cpp : This program centered around structs
// will create a table based on multiple runners' performances in preparation for a marathon. 
// The program will read a data file containing the names of the runners and how many miles
// each runner has completed for each day they ran. It will then create structs which will hold 
// the information for each runner received from the data file as well as additional information such as
// total miles completed for the week and the average number of miles completed in a day. Finally, an
// organized table will be created displaying all the information stored in the individual structs.

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

//Struct definition with members representing the runner's name, the miles they ran each day, 
//the total number of miles completed and the average number of miles completed daily.
struct runnerData
{
	string name;
	double miles[DAYS_RAN];
	double total;
	double average;
};

//An array available to store structs representing data for each runner must exist; 
//file containing runner information must be available; function must also be able to receive integer
//value representing the maximum number of runners able to be processed.
//Function must return the number of runners in the text file--the program will used this returned
//value to know how many runners are in the struct array and how many times loops processing the array
//will be iterated; name and miles[] in individual structs members will be updated.
int getRunnerData(runnerData runners[], string fileName, int maximum);

//Function takes number of runners in file (must not be altered) and reference to struct array.
//Total miles and average miles members in individual structs will be updated.
void getMileData(runnerData runners[], const int numRunners);

//Function expects to receive the number of runners in the file as well as references to the struct array.
//Function will output systematic table with various columns representing the names of each runner as well as
//the number of miles run per day, the total number of miles completed, and the average number of daily miles completed.
//Each member in each struct in struct array will be processed and displayed.
void dispRunnerReport(runnerData runners[], const int numRunners);

int main()
{
	//Initializes array to create and store structs for each runner
	//with members representing names, miles, etc.
	runnerData runners[MAX_RUNNERS];

	//Number of runners is obtained by the function to use for struct array processing
	//Function also updates runners[].name and runners[].miles[] members for each runner struct
	int numRunners = getRunnerData(runners, dataFile, MAX_RUNNERS);
	
	//Function updates runners[].total and runners[].average for each runner struct
	getMileData(runners, numRunners);

	//Function outputs formatted table displaying runner names, daily miles, total miles,
	//and every miles completed for each runner.
	dispRunnerReport(runners, numRunners);
	return 0;
}

int getRunnerData(runnerData runners[], string fileName, int maximum)
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
	//of runners able to be processed is reached
	while (!inputFile.eof() && num < maximum)
	{
		//Stores runner names in runners[].name for each runner
		inputFile >> runners[num].name;

		for (int day = 0; day < DAYS_RAN; day++)
		{
			//Updates runners[].miles[] for each day ran
			inputFile >> runners[num].miles[day];
		}
		//Increases runner count by 1
		num++;
	}
	//Closes file and returns number of runners
	inputFile.close();
	return num;
}

void getMileData(runnerData runners[], const int numRunners)
{
	//Initializes variable to calculate sum of daily miles per runner
	int totalMiles;

	//Per runner
	for (int runner = 0; runner < numRunners; runner++)
	{
		//Counter resets
		totalMiles = 0;

		//Per day
		for (int day = 0; day < DAYS_RAN; day++)
		{
			//Adds daily miles to total for each day
			totalMiles += runners[runner].miles[day];
		}
		//Stores total miles in runners[].total per runner
		runners[runner].total = totalMiles;

		//Stores average daily miles in runners[].average per runner
		runners[runner].average = runners[runner].total / DAYS_RAN;
	}

}

void dispRunnerReport(runnerData runners[], const int numRunners)
{
	//Creates "Name" heading
	cout << left << setw(20) << "Name";

	//Creates a heading for every day runners ran, given a number of days
	for (int day = 0; day < DAYS_RAN; day++)
	{
		cout << "Day " << left << setw(6) << (day + 1);
	}
	//Creates heading for total and average daily miles
	cout << left << setw(14) << "Total Miles" << left << setw(14) << "Avg Miles";
	cout << endl;

	//Per runner
	for (int runner = 0; runner < numRunners; runner++)
	{
		//Displays runner name
		cout << left << setw(20) << runners[runner].name;

		//Displays daily miles for each day
		for (int day = 0; day < DAYS_RAN; day++)
		{
			//Program checks to see if miles ran is greater than 100
			//to display the value correctly.
			cout << left << setw(10);
			if (runners[runner].miles[day] < 100)
				cout << setprecision(2);
			else
				cout << setprecision(3);
			cout << runners[runner].miles[day];
		}

		//Displays total miles
		//Program checks to see if miles ran is greater than 100
		//to display the value correctly.
		cout << left << setw(14);
		if (runners[runner].total < 100)
			cout << setprecision(2);
		else
			cout << setprecision(3);
		cout << runners[runner].total;

		//Displays average daily miles
		cout << left << setw(14) << setprecision(2) << fixed << runners[runner].average;

		//Disables fixed to display other values appropriately
		cout.unsetf(ios::fixed);
		cout << endl;
	}
}