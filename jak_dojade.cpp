#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
#define EMPTY '.'
#define ROAD '#'
#define CITY '*'
#define NUL '\0'

class str
{
public:
    static const size_t MAX_LENGTH = 127;
    char data[MAX_LENGTH + 1];
    str(const char* s = "")
    {
        size_t length = strlen(s);
        if (length > MAX_LENGTH)
        {
            length = MAX_LENGTH;
        }
        strncpy(data, s, length);
        data[length] = NUL;
    }
    str(const str& other)
    {
        strncpy(data, other.data, MAX_LENGTH);
        data[MAX_LENGTH] = NUL;
    }
    ~str() {}
    size_t length() const
    {
        return strlen(data);
    }
    str& operator=(const str& other)
    {
        if (this != &other)
        {
            strncpy(data, other.data, MAX_LENGTH);
            data[MAX_LENGTH] = NUL;
        }
        return *this;
    }
    str& operator=(const char* s)
    {
        size_t length = strlen(s);
        if (length > MAX_LENGTH)
        {
            length = MAX_LENGTH;
        }
        strncpy(data, s, length);
        data[length] = NUL;
        return *this;
    }
    str operator+(const str& other) const
    {
        str result(*this);
        result += other;
        return result;
    }
    str operator+(const char* s) const
    {
        str result(*this);
        result += s;
        return result;
    }
    str& operator+=(const str& other)
    {
        size_t currentLength = strlen(data);
        size_t maxLength = MAX_LENGTH - currentLength;
        size_t otherLength = strlen(other.data);
        if (otherLength > maxLength)
        {
            otherLength = maxLength;
            cerr << "Error: str too long!" << endl;
        }
        strncat(data, other.data, otherLength);
        return *this;
    }
    str& operator+=(const char* s)
    {
        size_t currentLength = strlen(data);
        size_t maxLength = MAX_LENGTH - currentLength;
        size_t sLength = strlen(s);
        if (sLength > maxLength)
        {
            sLength = maxLength;
        }
        strncat(data, s, sLength);
        return *this;
    }
    str& operator+=(char c)
    {
        size_t length = strlen(data);
        if (length < MAX_LENGTH - 1)
        {
            data[length] = c;
            data[length + 1] = NUL;
        }
        return *this;
    }
    bool operator==(const str& other) const
    {
        return strcmp(data, other.data) == 0;
    }
    bool operator==(const char* s) const
    {
        return strcmp(data, s) == 0;
    }
    bool operator!=(const str& other) const
    {
        return !(*this == other);
    }
    bool operator!=(const char* s) const
    {
        return !(*this == s);
    }
    char& operator[](size_t index)
    {
        if (index >= strlen(data))
        {
            static char dummy = NUL;
            return dummy;
        }
        return data[index];
    }
    friend ostream& operator<<(ostream& os, const str& s)
    {
        int i = 0;
        while (s.data[i] != NUL)
        {
            os << s.data[i];
            i++;
        }
        //os << s.data;
        return os;
    }
    friend istream& operator>>(std::istream& is, str& s)
    {
        char temp[MAX_LENGTH + 1];
        char c = getchar();
        while (c == ' ' || c == '\n')
        {
            c = getchar();
        }
        int i = 0;
        while (c != ' ' && c != '\n')
        {
            temp[i] = c;
            i++;
            c = getchar();
        }
        temp[i] = NUL;
        s = temp;
        return is;
    }
};

class Graph
{
public:
    int size;
    int adj_matrix[100][100];
    Graph(int n)
    {
        size = n;
        for (int y = 0; y < n; y++)
        {
            for (int x = 0; x < n; x++)
            {
                adj_matrix[y][x] = INT_MAX;
            }
            if (adj_matrix[y][y] == INT_MAX)
            {
                adj_matrix[y][y] = 0;
            }
        }
    }
    void addEdge(int x, int y, int weigth, bool isFlight)
    {
        if (x >= size || y >= size || x < 0 || y < 0)
        {
            return;
        }

        if (x == y)
        {
            return;
        }

        if (adj_matrix[x][y] < weigth)
            return;

        adj_matrix[x][y] = weigth;
        if (!isFlight)
            adj_matrix[y][x] = weigth;
    }
    void print()
    {
        for (int y = 0; y < size; y++)
        {
            for (int x = 0; x < size; x++)
            {
                cout << adj_matrix[y][x] << " ";
            }
            cout << endl;
        }
    }
};

struct City
{
    int x, y;
    str name;
    int id;
};

struct Flight
{
    str src, dest;
    int time;
};

struct Query
{
    str src, dest;
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

bool checkPositionAndAddName(int x, int y, int height, int width, char** map, str& cityName)
{
    if (!isInMap(x, y, height, width) || map[y][x] == EMPTY || map[y][x] == ROAD || map[y][x] == CITY)
        return false;
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
                if (!addName)
                    addName = true;
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

struct QNode
{
    Point data;
    QNode* next;
    QNode(const Point& p)
    {
        data = p;
        next = NULL;
    }
};

struct Queue
{
    QNode* front, * rear;
    Queue() { front = rear = NULL; }

    void push(Point p)
    {

        QNode* temp = new QNode(p);

        if (rear == NULL)
        {
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
    bool isEmpty()
    {
        if (front == NULL && rear == NULL) return true;
        return false;
    }
};

void checkPos(Point& pos, char** map, int numOfCities, City* cities, Graph& g, City city)
{
    if (map[pos.y][pos.x] == CITY)
    {
        int i = 0;
        while (i < numOfCities)
        {
            if (cities[i].x == pos.x && cities[i].y == pos.y)
            {
                break;
            }
            i++;
        }
        if (g.adj_matrix[i][city.id] > pos.dist)
            g.addEdge(city.id, i, pos.dist + 1, false);
    }
}

void bfs(Graph& g, City city, char** map, int h, int w, int numOfCities, City* cities)
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

    while (!q.isEmpty())
    {
        s = q.front->data;
        q.pop();
        if (isInMap(s.x + 1, s.y, h, w) && !visited[s.y][s.x + 1] && map[s.y][s.x + 1] != EMPTY)
        {
            s.x++;
            checkPos(s, map, numOfCities, cities, g, city);
            visited[s.y][s.x] = true;
            if (map[s.y][s.x] != CITY)
            {

                q.push({ s.x, s.y, s.dist + 1 });
            }
            s.x--;
        }
        if (isInMap(s.x - 1, s.y, h, w) && !visited[s.y][s.x - 1] && map[s.y][s.x - 1] != EMPTY)
        {
            s.x--;
            checkPos(s, map, numOfCities, cities, g, city);
            visited[s.y][s.x] = true;
            if (map[s.y][s.x] != CITY)
            {

                q.push({ s.x, s.y, s.dist + 1 });
            }
            s.x++;
        }
        if (isInMap(s.x, s.y + 1, h, w) && !visited[s.y + 1][s.x] && map[s.y + 1][s.x] != EMPTY)
        {
            s.y++;
            checkPos(s, map, numOfCities, cities, g, city);
            visited[s.y][s.x] = true;
            if (map[s.y][s.x] != CITY)
            {

                q.push({ s.x, s.y, s.dist + 1 });
            }
            s.y--;
        }
        if (isInMap(s.x, s.y - 1, h, w) && !visited[s.y - 1][s.x] && map[s.y - 1][s.x] != EMPTY)
        {
            s.y--;
            checkPos(s, map, numOfCities, cities, g, city);
            visited[s.y][s.x] = true;
            if (map[s.y][s.x] != CITY)
            {

                q.push({ s.x, s.y, s.dist + 1 });
            }
            s.y++;
        }
    }
    for (y = 0; y < h; y++)
    {
        delete[] visited[y];
    }
    delete[] visited;
}

void fillGraph(Graph& g, City*& cities, int numOfCities, char** map, int h, int w)
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
    str cityName = "";

    // it will check all positions around x y in search for city name and add it to variable
    if (checkPositionAndAddName(x + 1, y, height, width, map, cityName))
        gotName = true; // right
    if (!gotName && checkPositionAndAddName(x + 1, y + 1, height, width, map, cityName))
        gotName = true; // bottom right
    if (!gotName && checkPositionAndAddName(x, y + 1, height, width, map, cityName))
        gotName = true; // bottom
    if (!gotName && checkPositionAndAddName(x - 1, y + 1, height, width, map, cityName))
        gotName = true; // bottom left
    if (!gotName && checkPositionAndAddName(x - 1, y, height, width, map, cityName))
        gotName = true; // left
    if (!gotName && checkPositionAndAddName(x - 1, y - 1, height, width, map, cityName))
        gotName = true; // top left
    if (!gotName && checkPositionAndAddName(x, y - 1, height, width, map, cityName))
        gotName = true; // top
    if (!gotName && checkPositionAndAddName(x + 1, y - 1, height, width, map, cityName))
        gotName = true; // top right

    if (gotName)
    {
        // add city to an array
        cities[cityIndex] = { x, y, cityName, cityIndex };
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
            g.addEdge(id1, id2, flights[i].time, true);
        }
    }
}

int minDistance(int dist[], bool visited[], int V)
{
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void printSolution(int dist[], int parent[], int src, int dest, int type, int V, City* cities)
{
    cout << dist[dest];
    if (type == 1 && src != dest)
    {
        // print path
        int* path = new int[V];
        int j = dest;
        j = parent[j];
        int i;
        for (i = 0; parent[j] != -1; i++)
        {
            path[i] = j;
            j = parent[j];
        }
        for (i = i - 1; i >= 0; i--)
        {
            cout << " " << cities[path[i]].name;
        }
        delete[] path;
    }
    cout << endl;
}

void dijkstra(Graph& g, int src, int dest, int type, int numOfCities, City* cities)
{
    int V = g.size;
    int* dist = new int[V];
    int* parent = new int[V];
    bool* visited = new bool[V];

    for (int i = 0; i < V; i++)
    {
        parent[i] = -1;
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V; count++)
    {
        int u = minDistance(dist, visited, V);

        if (dist[u] == INT_MAX)
        {
            break;
        }

        for (int v = 0; v < V; v++)
        {

            if (g.adj_matrix[u][v] == INT_MAX)
            {
                continue;
            }
            if (!visited[v] && dist[u] + g.adj_matrix[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + g.adj_matrix[u][v];
            }
        }
        visited[u] = true;
    }

    printSolution(dist, parent, src, dest, type, V, cities);

    delete[] dist;
    delete[] parent;
    delete[] visited;
}

int main()
{
    int x, y, w, h, k, q;
    int numOfCities = 0;
    int cityIndex = 0;

    cin >> w >> h;
    char** map = new char* [h];
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
    fillGraph(g, cities, numOfCities, map, h, w);
    addFlightsToGraph(flights, k, cities, numOfCities, g);
    // g.print();

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
    // cout << endl;
    // for (int i = 0; i < numOfCities; i++)
    // {
    //     cout << "City " << i << " have cords (" << cities[i].x << ", " << cities[i].y << ") is: " << cities[i].name << endl;
    // }

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
        if (src != -1 && dest != -1)
            dijkstra(g, src, dest, queries[i].type, numOfCities, cities);
    }

    delete[] queries;
    delete[] flights;
    delete[] cities;
}