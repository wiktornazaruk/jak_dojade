#include <iostream>
#include <string>
using namespace std;
#define EMPTY '.'
#define ROAD '#'
#define CITY '*'

struct City
{
	int x, y;
	string name;
};

bool isInMap(int x, int y, int height, int width)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		return true;
	}
	return false;
}

void addCity(City*& cities, int& cityIndex, int x, int y, int height, int width, char** map)
{
	string cityName;
	bool startAddingLetters = false;
	bool nextElseQuit = false;
	bool quit = false;
	int i = 0;
	int firstIteration = 0;
	// check to the right
	while (isInMap(x + i + 1, y, height, width) && !quit)
	{
		if (map[y][x + i + 1] != EMPTY && map[y][x + i + 1] != ROAD && map[y][x + i + 1] != CITY)
		{
			cityName += map[y][x + i + 1];
			i++;
		}
		else
		{
			quit = true;
		}
	}
	quit = false;
	// check to the left
	while (isInMap(x + i - 1, y, height, width) && !quit)
	{
		if (map[y][x + i - 1] != EMPTY && map[y][x + i - 1] != ROAD && map[y][x + i - 1] != CITY)
		{
			if (!startAddingLetters)
			{
				i--;
			}
			else
			{
				cityName += map[y][x + i - 1];
				nextElseQuit = true;
				i++;
			}
		}
		else
		{
			startAddingLetters = true;
			i++;
			if(nextElseQuit) quit = true;
		}
	}
	cities[cityIndex] = { x, y, cityName };
	cout << cities[cityIndex].name;
	cityIndex++;
}

int main()
{
	int x, y, w, h, k, q, numOfCities = 0;
	int cityIndex = 0;
	cin >> w >> h;
	char** map = new char*[h];
	for (y = 0; y < h; y++)
	{
		map[y] = new char[w];
		for (x = 0; x < w; x++)
		{
			cin >> map[y][x];
			if (map[y][x] == CITY)
			{
				numOfCities++;
			}
		}
	}

	cout << endl << numOfCities << endl;

	City* cities = new City[numOfCities];
	
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			if (map[y][x] == CITY)
			{
				addCity(cities, cityIndex, x, y, h, w, map);
			}
			//cout << map[y][x];
		}
		//cout << endl;
	}
	
}