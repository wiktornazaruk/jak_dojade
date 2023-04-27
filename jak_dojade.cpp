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

void checkPositionAndAddName(int x, int y, int height, int width, char** map, string& cityName) 
{
	bool startAddingLetters = false;
	bool nextElseQuit = false;
	while (isInMap(x, y, height, width))
	{
		if (map[y][x] != EMPTY && map[y][x] != ROAD && map[y][x] != CITY)
		{
			if (!startAddingLetters)
			{
				if (x > 0)
				{
					x--;
				}
				else
				{
					startAddingLetters = true;
				}
			}
			else
			{
				cityName += map[y][x];
				map[y][x] = EMPTY;
				nextElseQuit = true;
				x++;
			}
		}
		else
		{
			startAddingLetters = true;
			x++;
			if (nextElseQuit) return;
		}
	}
}

void addCity(City*& cities, int& cityIndex, int x, int y, int height, int width, char** map)
{
	string cityName;

	// it will check all positions around x y in search for city name and add it to variable
	checkPositionAndAddName(x + 1, y, height, width, map, cityName); // right
	checkPositionAndAddName(x + 1, y + 1, height, width, map, cityName); // bottom right
	checkPositionAndAddName(x, y + 1, height, width, map, cityName); // bottom
	checkPositionAndAddName(x - 1, y + 1, height, width, map, cityName); // bottom left
	checkPositionAndAddName(x - 1, y, height, width, map, cityName); // left
	checkPositionAndAddName(x - 1, y - 1, height, width, map, cityName); // top left
	checkPositionAndAddName(x, y - 1, height, width, map, cityName); // top
	checkPositionAndAddName(x + 1, y - 1, height, width, map, cityName); // top right

	// add city to an array
	cities[cityIndex] = { x, y, cityName };
	//cout << cities[cityIndex].name;
	cityIndex++;
}

int main()
{
	int x, y, w, h, k, q;
	int numOfCities = 0;
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

	//cout << endl << numOfCities << endl;

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