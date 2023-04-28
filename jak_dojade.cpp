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

struct Flight
{
	string src, dest;
	int time;
};

struct Query
{
	string src, dest;
	// If the type is zero, the query is only for the time. If the type is one, the route should also be provided.
	bool type;
};

bool isInMap(int x, int y, int height, int width)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		return true;
	}
	return false;
}

bool checkPositionAndAddName(int x, int y, int height, int width, char** map, string& cityName)
{
	if (!isInMap(x, y, height, width) || map[y][x] == EMPTY || map[y][x] == ROAD || map[y][x] == CITY) return false;
	bool addName = false;
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
				if(!addName) addName = true;
				cityName += map[y][x];
				map[y][x] = EMPTY;
				nextElseQuit = true;
				x++;
			}
		}
		else
		{
			x++;
			startAddingLetters = true;
			if (nextElseQuit)
			{
				break;
			}
		}
	}
	if (addName)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void bfs(City city, char **map)
{
	return;
}

void addToGraph(City*& cities, int numOfCities, char** map)
{
	for (int i = 0; i < numOfCities; i++)
	{
		bfs(cities[0], map);
	}
}

void addCity(City*& cities, int& cityIndex, int x, int y, int height, int width, char** map)
{
	bool gotName = false;
	string cityName = "";

	// it will check all positions around x y in search for city name and add it to variable
	if (!gotName && checkPositionAndAddName(x + 1, y, height, width, map, cityName)) gotName = true; // right
	if (!gotName && checkPositionAndAddName(x + 1, y + 1, height, width, map, cityName)) gotName = true; // bottom right
	if (!gotName && checkPositionAndAddName(x, y + 1, height, width, map, cityName)) gotName = true; // bottom
	if (!gotName && checkPositionAndAddName(x - 1, y + 1, height, width, map, cityName)) gotName = true; // bottom left
	if (!gotName && checkPositionAndAddName(x - 1, y, height, width, map, cityName)) gotName = true; // left
	if (!gotName && checkPositionAndAddName(x - 1, y - 1, height, width, map, cityName)) gotName = true; // top left
	if (!gotName && checkPositionAndAddName(x, y - 1, height, width, map, cityName)) gotName = true; // top
	if (!gotName && checkPositionAndAddName(x + 1, y - 1, height, width, map, cityName)) gotName = true; // top right

	if (gotName)
	{
		// add city to an array
		cities[cityIndex] = { x, y, cityName };
		//cout << cities[cityIndex].name;
		cityIndex++;
	}
}


int shortestTravelTimeBetweenCities(Query query)
{
	int result = 0;
	return result;
}

void printIntermediateCities(Query query)
{
	return;
}

void fillAmocbc(int** amocbc, City* cities, char** map)
{
	return;
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
	cin >> k;
	Flight* flights = new Flight[k];
	for (int i = 0; i < k; i++)
	{
		cin >> flights[i].src;
		cin >> flights[i].dest;
		cin >> flights[i].time;
	}
	cin >> q;
	Query* queries = new Query[q];
	for (int i = 0; i < q; i++)
	{
		cin >> queries[i].src;
		cin >> queries[i].dest;
		cin >> queries[i].type;
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
		}
	}

	int** amocbc = new int* [numOfCities]; // "amocbc" - adjacency matrix of connections between cities
	for (y = 0; y < numOfCities; y++)
	{
		amocbc[y] = new int[numOfCities];
		for (x = 0; x < numOfCities; x++)
		{
			amocbc[y][x] = 0;
		}
	}

	//fillAmocbc();

	// print map
	/*cout << endl;
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			cout << map[y][x];
		}
		cout << endl;
	}*/

	// print cities
	/*cout << endl;
	for (int i = 0; i < numOfCities; i++)
	{
		cout << "City " << i + 1 << " have cords (" << cities[i].x << ", " << cities[i].y << ") is: " << cities[i].name << endl;
	}*/

	// output
	//for (int i = 0; i < q; i++)
	//{
		//cout << shortestTravelTimeBetweenCities(queries[i]);
		//if (queries[i].type == 1)
		//{
			//printIntermediateCities(queries[i]);
		//}
	//}
	
}