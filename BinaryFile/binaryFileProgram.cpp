/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  This program reads in the name of the program from the command line as well as reads in the meta data to 
//  determine the different types of data in the file for the possible data sets present: sea temperature, sea
//  salinity, and sea height.  It will also read in the quantity for each if they are present.  It will then
//  separate each data set into its own binary file with a name formatting of type.size.
//  
//  Christy Mims
//
//  6/27/2019
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Functions
void DoWork(string);
int GetMetaData(ifstream &, int*, int);
void ReadInData(ifstream &, int*, int);
void WriteData(int*, string, int);

int main(int argc, char* argv[])
{


	if (argc != 2)
	{
		// checks to see if valid filename was entered
		cout << "You must enter a valid filename" << endl;
		system("PAUSE");
		return(1);
	}

	// takes in file name from command window
	string fileName = argv[1];
	
	// calls the DoWork function
	DoWork(fileName);
	
	// pauses output
	//system("pause");
	return(0);
}

void DoWork(string fileName)
{
	// outputs the name of the file to the console
	cout << endl << endl << "The name passed in was " << fileName << endl;

	// creates the binary stream reader
	ifstream ReadBinary;

	// opens the file
	ReadBinary.open(fileName, ios::in | ios::binary);

	// checks to see if the binary file opened
	if (!ReadBinary)
	{
		// outputs if file did not open
		cout << endl << "Could not open text file for reading." << endl << endl;
	}

	// array to hold the meta data
	int fileData[3];

	// intializes the metaData to zeroes
	for (int i = 0; i < 3; i++)
	{
		fileData[i] = 0;
	}

	// variable to hold the size of the data
	int dataSize = 0;

	// function call GetMetaData
	dataSize = GetMetaData(ReadBinary, fileData, dataSize);

	// to see what is returned after calling GetMetaData
	cout << endl;
	cout << "Temperature is " << fileData[0] << endl;
	cout << "Salinity is " << fileData[1] << endl;
	cout << "Height is " << fileData[2] << endl;
	cout << "Data size is " << dataSize << endl;

	// variable to put file name in
	string name = "";

	// if the metadata eqauls one then this will execute
	if (fileData[0] == 1)
	{
		// name for file
		name = "Temperature";

		// Dynamic array to hold the temperature data
		int *temperatureData;
		temperatureData = new int[dataSize];

		// function call to read in the data for temperature
		ReadInData(ReadBinary, temperatureData, dataSize);
		
		// call function to write data to file
		WriteData(temperatureData, name, dataSize);

		// delete the temperature dynamic array 
		delete[] temperatureData;

	}

	// if the metadata eqauls one then this will execute
	if (fileData[1] == 1)
	{
		// name for file
		name = "Salinity";

		// Dynamic array to hold the Salinity data
		int *SalinityData;
		SalinityData = new int[dataSize];

		// function call to read in the data for salinity
		ReadInData(ReadBinary, SalinityData, dataSize);
		
		// call funtion to write to file
		WriteData(SalinityData, name, dataSize);

		// delete salinity dynamic array
		delete[] SalinityData;
	}

	// if the metadata eqauls one then this will execute
	if (fileData[2] == 1)
	{
		// name for file
		name = "SeaHeight";

		// Dynamic array to hold the Sea Height Data
		int *seaHeightData;
		seaHeightData = new int[dataSize];

		// function call to read in the data for sea height
		ReadInData(ReadBinary, seaHeightData, dataSize);
		
		// call function to write to file
		WriteData(seaHeightData, name, dataSize);

		// delete sea height dynamic array
		delete[] seaHeightData;
	}
	

}

int GetMetaData(ifstream &ReadBinary, int *fileData, int dataSize)
{
	// variable to store data from file
	int dataCatch = 0;



	// for loop to read in the meta data
	for (int i = 0; i < 3; i++)
	{
		ReadBinary.read(reinterpret_cast<char *>(&dataCatch), sizeof(int));
		fileData[i] = dataCatch;
	}
	
	// read in the size of the data
	ReadBinary.read(reinterpret_cast<char *>(&dataCatch), sizeof(int));
	dataSize = dataCatch;

	// returns the data read in
	return(dataSize);

}

void ReadInData(ifstream &ReadBinary, int *fileData , int totalData)
{
	// variable to catch data
	int dataCatch = 0;

	// output to tell how much data will be read in
	//cout << "The total data is " << totalData << endl;

	// read in data and reinterpret and put in array
	for (int i = 0; i < totalData; i++)
	{
		ReadBinary.read(reinterpret_cast<char *>(&dataCatch), sizeof(int));
		fileData[i] = dataCatch;
	}



}

void WriteData(int *data, string name, int dataSize)
{
	// create the out stream writer and name WriteData
	ofstream WriteBinaryData;

	// create the file name from passed in variables
	string newFileName = name + "." + to_string(dataSize);

	// this will create the file or overwrite an existing file
	WriteBinaryData.open(newFileName, ios::out | ios::binary);

	// check to see if file was opened for writing
	if (!WriteBinaryData)
	{
		cout << "File could not be opened or created for writing." << endl << endl;
	}

	// notify user that file is being written to 
	cout << "The file is now going to be written" << endl << endl;
	
	// does a write to the file each time through the loop
	for (int i = 0; i < dataSize; i++) 
	{
		WriteBinaryData.write(reinterpret_cast<const char *>(&data[i]), sizeof(int));
	}

	// close the binary file
	WriteBinaryData.close();
	
}
