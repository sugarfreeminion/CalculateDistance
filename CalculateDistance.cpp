#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;

/* struct to hold x,y coordinate info */
struct coordinate
{
	int x;
	int y;
};

/*
 * Function Name:	ParseInput
 * Description:		Input format is (x1,y1) (x2,y2). Function returns
 *					(x1,y1) as one vector and (x2,y2) as another.
 */
vector<string> ParseInput(string input)
{
	vector<string> coordinates;

	int coordEnd;
	
	unsigned int index = 0;
	
	// format for coordinates is: (x,y)
	while(index < input.size())
	{
		// the start of a coordinate
		if(input[index] == '(')
		{
			// find where the coordinate ends in the string
			coordEnd = input.find(")",index);
			
			coordinates.push_back(input.substr(index,(coordEnd-index)+1));
			
			//cout << "Coord start found at: " << index << endl;
			//cout << "Coord end found at: " << coordEnd << endl;
			//cout << "Coords are: " << coordinates.back() << endl;
			
			// update index
			index = coordEnd;
		}
		
		++index;
	}
	
	return coordinates;
}

/*
 * Function Name: 	GetCoordinates
 * Description:		parses (x,y) and creates a coordinate 
 * 					data structure to store values in.
 */
coordinate GetCoordinates(string input)
{
	unsigned int delimiter;
	
	coordinate coord;
	
	string x;
	string y;
	
	// x and y are separated by a ","
	delimiter = input.find(",");
	
	// start at 1 to ignore open brace
	x = input.substr(1,delimiter-1);
	y = input.substr(delimiter+2,(input.size()-delimiter)-3);
	
	coord.x = atoi(x.c_str());
	coord.y = atoi(y.c_str());
	
	//cout << "X: " << coord.x << endl;
	//cout << "Y: " << coord.y << endl;
	
	return coord;
}

/*
 * Function Name: 	Distance
 * Description:		calculates distance between two points
 *					           ------------------------
 *							  /          2			2
 *				distance =	 /	(x2 - x1)  + (y2-y1)	 
 *						   \/ 
 */
int Distance(vector<coordinate> coords)
{
	int x = 0;
	int y = 0;
	int distance = 0;
	
	//cout << coords.size() << endl;
	//cout << "First value of y: " << coords.front().y << endl;
	//cout << "Second value of y: " << coords.back().y << endl;
	
	x = coords.back().x - coords.front().x;
	y = coords.back().y - coords.front().y;
	
	distance = sqrt(pow(x,2) + (pow(y,2)));
	
	//cout << "Distance for x: " << x << endl;
	//cout << "Distance for y: " << y << endl;
	
	return distance;
}

int main(int argc, char *argv[])
{
	// input file
	ifstream ifs(argv[1]);
	
	// holds a single line of input from text file
	string input;
	
	vector<string> sCoordinates;
	vector<coordinate> coordinates;
	
	int distance = 0;
	
	// make sure that the input file is opened
	if(ifs.is_open())
	{
		// read all the lines
		while(getline(ifs,input))
		{
			// parse the input into first (x1,y1) and second (x2,y2) coordinates  
			sCoordinates = ParseInput(input);
			
			for(vector<string>::iterator it=sCoordinates.begin(); it!=sCoordinates.end(); ++it)
			{
				coordinates.push_back(GetCoordinates(*it));
			}
			
			distance = Distance(coordinates);
			
			cout << distance << endl;
			
			coordinates.clear();
		}
	}
	else
	{
		cout << "Input file error" << endl;
	}
	
	// make sure to close the input file
	ifs.close();
	
	return 0;
}