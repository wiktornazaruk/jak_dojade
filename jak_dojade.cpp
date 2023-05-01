#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;
#define EMPTY '.'
#define ROAD '#'
#define CITY '*'

struct Pair
{
	int id, edge;
};

class Graph {
public:
	vector<list<Pair>> adj;
	Graph(int size) :adj(size) { }
	void addEdge(int id, Pair pair) {
		adj[id].push_back(pair);
	}
	void print()
	{
		for (int i = 0; i < adj.size(); i++)
		{
			for (auto v : adj[i])
				cout << i << " " << v.id << " " << v.edge << "\n";
		}
	}


};

struct City
{
	int x, y;
	string name;
	int id;
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

struct Point
{
	int x, y;
	int dist;
};

struct QNode {
	Point data;
	QNode* next;
	QNode(Point p)
	{
		data = p;
		next = NULL;
	}
};

struct Queue {
	QNode* front, * rear;
	Queue() { front = rear = NULL; }


	void push(Point p)
	{

		QNode* temp = new QNode(p);

		if (rear == NULL) {
			front = rear = temp;
			return;
		}

		rear->next = temp;
		rear = temp;
	}

	void pop()
	{
		if (front == NULL)
			return;

		QNode* temp = front;
		front = front->next;

		if (front == NULL)
			rear = NULL;

		delete (temp);
	}
	bool empty()
	{
		if (front == NULL && rear == NULL) return true;
		else return false;
	}
};


void checkPos(Point& pos, char** map, int numOfCities, City* cities, Graph& g, City city)
{
	if (map[pos.y][pos.x] == ROAD)
	{
		pos.dist++;
	}
	else if (map[pos.y][pos.x] == CITY)
	{
		Pair p;
		p.edge = pos.dist;
		int i = 0;
		while (i < numOfCities)
		{
			if (cities[i].x == pos.x && cities[i].y == pos.y)
			{
				p.id = i;
				break;
			}
			i++;
		}
		g.addEdge(city.id, p);
	}
}

void bfs(Graph& g, City city, char **map, int h, int w, int numOfCities, City* cities)
{
	int x, y;
	bool** visited = new bool* [h];
	for (y = 0; y < h; y++)
	{
		visited[y] = new bool[w];
		for (x = 0; x < w; x++)
		{
			visited[y][x] = false;
		}
	}
	Queue q;
	Point s;
	s.x = city.x;
	s.y = city.y;
	s.dist = 0;
	visited[s.y][s.x] = true;
	q.push(s);

	while (!q.empty())
	{
		s = q.front->data;
		cout << s.x << ", " << s.y << endl;
		q.pop();
		if (isInMap(s.x + 1, s.y, h, w) && !visited[s.y][s.x + 1] && map[s.y][s.x + 1] != EMPTY) {
			s.x++;
			checkPos(s, map, numOfCities, cities, g, city);
			visited[s.y][s.x] = true;
			if (map[s.y][s.x] == CITY) return;
			q.push(s);
			s.x--;
		}
		if (isInMap(s.x - 1, s.y, h, w) && !visited[s.y][s.x - 1] && map[s.y][s.x - 1] != EMPTY) {
			s.x--;
			checkPos(s, map, numOfCities, cities, g, city);
			visited[s.y][s.x] = true;
			if (map[s.y][s.x] == CITY) return;
			q.push(s);
			s.x++;
		}
		if (isInMap(s.x, s.y + 1, h, w) && !visited[s.y + 1][s.x] && map[s.y + 1][s.x] != EMPTY) {
			s.y++;
			checkPos(s, map, numOfCities, cities, g, city);
			visited[s.y][s.x] = true;
			if (map[s.y][s.x] == CITY) return;
			q.push(s);
			s.y--;
		}
		if (isInMap(s.x, s.y - 1, h, w) && !visited[s.y - 1][s.x] && map[s.y - 1][s.x] != EMPTY) {
			s.y--;
			checkPos(s, map, numOfCities, cities, g, city);
			visited[s.y][s.x] = true;
			if (map[s.y][s.x] == CITY) return;
			q.push(s);
			s.y++;
		}
	}

}

void makeGraph(Graph& g, City*& cities, int numOfCities, char** map, int h, int w )
{
	int y, x, i = 0;
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			if (map[y][x] == CITY)
			{
				if (i < numOfCities)
				{
					bfs(g, cities[i], map, h, w, numOfCities, cities);
					i++;
				}
			}
		}
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
		cities[cityIndex] = { x, y, cityName, cityIndex };
		//cout << cities[cityIndex].name;
		cityIndex++;
	}
}

void addFlightsToGraph(Flight* flights, int k, City* cities, int numOfCities, Graph& g)
{
	for (int i = 0; i < k; i++)
	{
		int id1 = -1, id2 = -1;
		for (int j = 0; j < numOfCities; j++)
		{
			if (flights[i].src == cities[j].name)
			{
				id1 = j;
			}
			if (flights[i].dest == cities[j].name)
			{
				id2 = j;
			}
		}
		if (id1 != -1 && id2 != -1)
		{
			Pair p;
			p.id = id2;
			p.edge = flights[i].time;
			g.addEdge(id1, p);
		}
	}
}

void dijkstra(Graph g, int src, int dest, int type)
{

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

	Graph g(numOfCities);
	makeGraph(g, cities, numOfCities, map, h, w);
	addFlightsToGraph(flights, k, cities, numOfCities, g);
	g.print();

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
	cout << endl;
	for (int i = 0; i < numOfCities; i++)
	{
		cout << "City " << i << " have cords (" << cities[i].x << ", " << cities[i].y << ") is: " << cities[i].name << endl;
	}

	// output
	for (int i = 0; i < q; i++)
	{
		int src = -1, dest = -1;
		for (int j = 0; j < numOfCities; j++)
		{
			if (cities[j].name == queries[i].src)
			{
				src = cities[j].id;
			}
			if (cities[j].name == queries[i].dest)
			{
				dest = cities[j].id;
			}
		}
		if(src != -1 && dest != -1)
			dijkstra(g, src, dest, queries[i].type);
	}
	
}