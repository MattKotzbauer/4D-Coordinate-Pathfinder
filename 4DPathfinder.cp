#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <vector>
#include <string>
#include <deque>
using namespace std;

int gridSize;
int totalRows, totalColumns, totalDepth, totalDimensionFour;
/*
 We will use nested vectors to lay out our coordinate plane: each vector within this allows us to expand outwards into a new dimension.
 */
vector<vector<vector<vector<bool>>>> blockedPoints;
vector<vector<vector<vector<bool>>>> visited;
vector<vector<int>> placeholderPath;
vector<vector<vector<vector<vector<vector<int>>>>>> allPaths;
/*
 And yes, this is indeed a sextuple-nested vector: though it seems like a confusing declaration, it allows for code that's easy to read later on (as we can represent the four dimensions as coordinates within the vector, and can declare the path to each coordinate as a simple list of points). Trust me, it will pay off.
 */
deque<vector<int>> queuedPoints;
vector<int> targetPoint;

void pathUtilityFunction(int currentRow, int currentColumn, int currentDepth, int currentDimensionFour, int modifiedRow, int modifiedColumn, int modifiedDepth, int modifiedDimensionFour)
{
	//Puts the modified point into the search queue
	queuedPoints.push_back({modifiedRow, modifiedColumn, modifiedDepth, modifiedDimensionFour});
	//Marks the modified point as visited
	visited[modifiedRow][modifiedColumn][modifiedDepth][modifiedDimensionFour] = true;
	//Inserts the shortest path to the modified point by referencing the shortest path to the current point
	placeholderPath = allPaths[currentRow][currentColumn][currentDepth][currentDimensionFour];
	placeholderPath.push_back({modifiedRow, modifiedColumn, modifiedDepth, modifiedDimensionFour});
	allPaths[modifiedRow][modifiedColumn][modifiedDepth][modifiedDimensionFour] = placeholderPath;
	//(Clears the placeholder vector for later use)
	placeholderPath.clear();
	
}

void gridSearch(int currentRow, int currentColumn, int currentDepth, int currentDimensionFour)
{
	/*
	 Summary of function: Searches grid similarly to a breadth-first search, prioritizing elements closest to origin point in search by using a queue (first-in-first-out) and sequentially removing visited elements. This method of searching is mathematically guaranteed to generate the shortest path due to being recursively made up of shortest paths. The 'edges' in this graph are the adjacencies in the fourth dimension: the horizontal next element, horizontal previous element, vertical next element, vertical previous element, depth next element, depth previous element, dimension-four next element, and dimension-four previous element. We can traverse to these edges using similar modules, plugging them into the path utility function to update the pathfinder with shortest path and visited coordinates. Once we've found the shortest path to our target point, we can terminate, as we have all the information we need (and to save computing power, would like to exit 4D as quickly as possible!).
	 */
	while(queuedPoints.size() > 0)
	{
		//Taking the element at the front of the queue as our current point
		currentRow = queuedPoints.front()[0];
		currentColumn = queuedPoints.front()[1];
		currentDepth = queuedPoints.front()[2];
		currentDimensionFour = queuedPoints.front()[3];
		//For each adjacent coordinate, we will test if it's in bounds and qualifies to be searched. If so, we will run it through our path utility function: and, if we've reached our destination, we will terminate.
		//Horizontal Next Element:
		if(currentRow+1 < totalRows && blockedPoints[currentRow+1][currentColumn][currentDepth][currentDimensionFour] == false && !visited[currentRow+1][currentColumn][currentDepth][currentDimensionFour])
		{
			pathUtilityFunction(currentRow, currentColumn, currentDepth, currentDimensionFour, currentRow + 1, currentColumn, currentDepth, currentDimensionFour);
			if(targetPoint[0] == currentRow+1 && targetPoint[1] == currentColumn && targetPoint[2] == currentDepth && targetPoint[3] == currentDimensionFour){return;}
		}
		//Horizontal Previous Element:
		if(currentRow-1 >= 0 && blockedPoints[currentRow-1][currentColumn][currentDepth][currentDimensionFour] == false && !visited[currentRow-1][currentColumn][currentDepth][currentDimensionFour])
		{
			pathUtilityFunction(currentRow, currentColumn, currentDepth, currentDimensionFour, currentRow-1, currentColumn, currentDepth, currentDimensionFour);
			if(targetPoint[0] == currentRow-1 && targetPoint[1] == currentColumn && targetPoint[2] == currentDepth && targetPoint[3] == currentDimensionFour){return;}
		}
		//Vertical Next Element:
		if(currentColumn+1 < totalColumns && blockedPoints[currentRow][currentColumn+1][currentDepth][currentDimensionFour] == false && !visited[currentRow][currentColumn+1][currentDepth][currentDimensionFour])
		{
			pathUtilityFunction(currentRow, currentColumn, currentDepth, currentDimensionFour, currentRow, currentColumn+1, currentDepth, currentDimensionFour);
			if(targetPoint[0] == currentRow && targetPoint[1] == currentColumn+1 && targetPoint[2] == currentDepth && targetPoint[3] == currentDimensionFour){return;}
		}
		//Vertical Previous Element:
		if(currentColumn-1 >=0 && blockedPoints[currentRow][currentColumn-1][currentDepth][currentDimensionFour] == false && !visited[currentRow][currentColumn-1][currentDepth][currentDimensionFour])
		{
			pathUtilityFunction(currentRow, currentColumn, currentDepth, currentDimensionFour, currentRow, currentColumn-1, currentDepth, currentDimensionFour);
			if(targetPoint[0] == currentRow && targetPoint[1] == currentColumn-1 && targetPoint[2] == currentDepth && targetPoint[3] == currentDimensionFour){return;}
		}
		//Depth Next Element:
		if(currentDepth+1 < totalDepth && blockedPoints[currentRow][currentColumn][currentDepth+1][currentDimensionFour] == false && !visited[currentRow][currentColumn][currentDepth+1][currentDimensionFour])
		{
			pathUtilityFunction(currentRow, currentColumn, currentDepth, currentDimensionFour, currentRow, currentColumn, currentDepth+1, currentDimensionFour);
			if(targetPoint[0] == currentRow && targetPoint[1] == currentColumn && targetPoint[2] == currentDepth+1 && targetPoint[3] == currentDimensionFour){return;}
		}
		//Depth Previous Element:
		if(currentDepth-1 >= 0 && blockedPoints[currentRow][currentColumn][currentDepth-1][currentDimensionFour] == false && !visited[currentRow][currentColumn][currentDepth-1][currentDimensionFour])
		{
			pathUtilityFunction(currentRow, currentColumn, currentDepth, currentDimensionFour, currentRow, currentColumn, currentDepth-1, currentDimensionFour);
			if(targetPoint[0] == currentRow && targetPoint[1] == currentColumn && targetPoint[2] == currentDepth-1 && targetPoint[3] == currentDimensionFour){return;}
		}
		//Dimension-Four Next Element:
		if(currentDimensionFour+1 < totalDimensionFour && blockedPoints[currentRow][currentColumn][currentDepth][currentDimensionFour+1] == false && !visited[currentRow][currentColumn][currentDepth][currentDimensionFour+1])
		{
			pathUtilityFunction(currentRow, currentColumn, currentDepth, currentDimensionFour, currentRow, currentColumn, currentDepth, currentDimensionFour+1);
			if(targetPoint[0] == currentRow && targetPoint[1] == currentColumn && targetPoint[2] == currentDepth && targetPoint[3] == currentDimensionFour+1){return;}
		}
		//Dimension-Four Previous Element:
		if(currentDimensionFour-1 >= 0 && blockedPoints[currentRow][currentColumn][currentDepth][currentDimensionFour-1] == false && !visited[currentRow][currentColumn][currentDepth][currentDimensionFour-1])
		{
			pathUtilityFunction(currentRow, currentColumn, currentDepth, currentDimensionFour, currentRow, currentColumn, currentDepth, currentDimensionFour-1);
			if(targetPoint[0] == currentRow && targetPoint[1] == currentColumn && targetPoint[2] == currentDepth && targetPoint[3] == currentDimensionFour-1){return;}
		}
		//Pops the front element from the queue, as it has now been visited and searched from
		queuedPoints.pop_front();
	}
}

vector<int> inputPoint(){
	/*
	 Input function: takes in four integers for the four-dimensional coordinates, prompting the user for another input if the value is not a number or is negative
	 */
	vector<string> inputString;
	vector<int> gridPoint;
	inputString.resize(4);
	gridPoint.resize(4);
	bool numeric;
	bool loop = false;
	bool first = true;
	do
	{
		if(!first)
		{
			cout<<"Please enter valid integers within grid:\n";
		}
		cin>>inputString[0]>>inputString[1]>>inputString[2]>>inputString[3];
		numeric = true;
		loop = false;
		for(int i=0; i<inputString.size(); i++){
			for(int q=0; q<inputString[i].size(); q++)
			{
				if(!isdigit(inputString[i][q])){numeric = false;}
			}
		}
		if(!numeric)
		{
			first = false;
			loop = true;
			continue;
		}
		for(int i=0; i<inputString.size(); i++)
		{
			gridPoint[i] = stoi(inputString[i]);
		}
		first = false;
	} while(loop || gridPoint[0] < 0 || gridPoint[0] >= gridSize || gridPoint[1] < 0 || gridPoint[1] >= gridSize || gridPoint[2] < 0 || gridPoint[2] >= gridSize || gridPoint[3] < 0 || gridPoint[3] >= gridSize);
	
	return gridPoint;
}

int main()
{
	/*
	 Driver Function: Takes user input (accounting for error inputs), initializes the queue and paths using the starting point, and calls the function to search the grid. Proceeds to display either the shortest path to the point (in the case of an existing viable path), or a failure to find the path (in the case of no existing viable path to the point in the 4-dimensional grid)
	 */
	cout<<"Enter Grid Size (g):\n";
	cin>>gridSize;
	while(gridSize <= 0)
	{
		cout<<"Please enter valid non-negative integer:\n";
		cin>>gridSize;
	}
	cout<<"Loading Grid...\n";
	//Initializes the grid to empty vectors so that the searching functions may refer to the points freely. Note that, depending on grid size, this may take time, as time complexity is O(N^4) from grid size (the same goes for the search function in general if the point is too far out)
	totalRows = gridSize;
	totalColumns = gridSize;
	totalDepth = gridSize;
	totalDimensionFour = gridSize;
	blockedPoints.resize(gridSize);
	visited.resize(gridSize);
	allPaths.resize(gridSize);
	for(int x=0; x<gridSize; x++)
	{
		blockedPoints[x].resize(gridSize);
		visited[x].resize(gridSize);
		allPaths[x].resize(gridSize);
	}
	for(int x=0; x<gridSize; x++)
	{
		for(int y=0; y<gridSize; y++)
		{
			blockedPoints[x][y].resize(gridSize);
			visited[x][y].resize(gridSize);
			allPaths[x][y].resize(gridSize);
		}
	}
	for(int x=0; x<gridSize; x++)
	{
		for(int y=0; y<gridSize; y++)
		{
			for(int z=0; z<gridSize; z++)
			{
				blockedPoints[x][y][z].resize(gridSize);
				visited[x][y][z].resize(gridSize);
				allPaths[x][y][z].resize(gridSize);
			}
		}
	}
	//Starting point user input
	vector<int> startingPoint;
	cout<<"Enter Starting Point (Format: X Y Z A)\n";
	startingPoint = inputPoint();
	//Target point user input
	cout<<"Enter Target Point (Format: X Y Z A):\n";
	targetPoint = inputPoint();
	//Blocked points user input
	int noBlockedPoints;
	cout<<"Number of Points to Block:\n";
	cin>>noBlockedPoints;
	while(noBlockedPoints--)
	{
		cout<<"Enter Blocked Point (Format: X Y Z A):\n";
		vector<int> blockedPoint;
		blockedPoint = inputPoint();
		blockedPoints[blockedPoint[0]][blockedPoint[1]][blockedPoint[2]][blockedPoint[3]] = true;
	}
	cout<<"Loading Path...\n";
	//Initialization of queue and path
	queuedPoints.push_back({startingPoint[0],startingPoint[1],startingPoint[2],startingPoint[3]});
	visited[startingPoint[0]][startingPoint[1]][startingPoint[2]][startingPoint[3]] = true;
	allPaths[startingPoint[0]][startingPoint[1]][startingPoint[2]][startingPoint[3]].push_back({startingPoint[0],startingPoint[1],startingPoint[2],startingPoint[3]});
	//Calling of gridSearch from our starting point
	gridSearch(startingPoint[0], startingPoint[1], startingPoint[2], startingPoint[3]);
	
	if(visited[targetPoint[0]][targetPoint[1]][targetPoint[2]][targetPoint[3]] && blockedPoints[targetPoint[0]][targetPoint[1]][targetPoint[2]][targetPoint[3]] == false)
	{
		//If our target point has been found, we print out its path
		cout<<"Path:\n";
		for(vector<int> singlePathVecs: allPaths[targetPoint[0]][targetPoint[1]][targetPoint[2]][targetPoint[3]])
		{
			cout<<"("<<singlePathVecs[0]<<", "<<singlePathVecs[1]<<", "<<singlePathVecs[2]<<", "<<singlePathVecs[3]<<")\n";
		}
		cout<<"(End of Path)\n";
		cout<<"Path Length: "<<allPaths[targetPoint[0]][targetPoint[1]][targetPoint[2]][targetPoint[3]].size()-1<<"\n";
	}
	else
	{
		//Otherwise, we print that we were unable to reach the point
		cout<<"Unable to Reach Point: No Possible Path :(\n";
	}
}
