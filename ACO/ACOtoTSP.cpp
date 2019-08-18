#include <iostream>
#include <random>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;
typedef vector<int> Solution;
typedef vector<Solution> Ant;

/*----set random number device-----*/
random_device rd;
mt19937 generator(rd());
uniform_int_distribution<> unif(0, 1);
uniform_real_distribution<double> r(0, 1);
/*---------------------------------*/

class pheromone
{
public:
	double phe;
	double dist;
};

class city
{
public:
	int temp;
	int x;
	int y;
};
void Initialization(vector<vector<pheromone>>& table, vector<city>& cities, int citynum, int antnum);
void Random(Ant& ants,int citynum, int antnum);
int main(int argc, char* argv[])
{
	int runs = atoi(argv[1]), iters = atoi(argv[2]), citynum = atoi(argv[3]), antnum = atoi(argv[4]), round = 1;
	vector<vector<pheromone>> table;
	vector<city> cities;
	Ant ants;
	uniform_real_distribution<> unifr(0, (citynum - 1));

	while (runs--)
		//number of runs
	{
		//cout << "round : " << round << endl;
		iters = atoi(argv[2]);
		Initialization(table, cities, citynum, antnum);
		Random(ants,citynum,antnum);
		//updating the best solution this round
		while (iters--)
		{

		}
	}
	/*cout << "The best solution is : ";
	for (auto i = Bestsol.sol.begin(); i != Bestsol.sol.end(); i++) { cout << *i; }
	cout << " , the value is	: " << Bestsol.value << endl;*/
	//output
	system("pause");
}

void Initialization(vector<vector<pheromone>>& table, vector<city>& cities, int citynum, int antnum)
{
	int  input;
	city city;
	//Solution ant(citynum, 0);
	pheromone pher;
	pher.dist = 0;
	pher.phe = 0;
	vector<vector<pheromone>> init(citynum, vector<pheromone>(citynum, pher));
	ifstream infileWeight("tsp51.txt");
	while (infileWeight >> input) {
		city.temp = input;
		infileWeight >> input;
		city.x = input;
		infileWeight >> input;
		city.y = input;
		cities.push_back(city);
	}
	/*for (size_t i = 0; i < antnum; i++)
		ants.push_back(ant);*/
	table = init;
	for (int i = 0; i < citynum; i++)
	{
		for (int j = 0; j < citynum; j++)
		{
			double num = sqrt(pow(cities[i].x - cities[j].x,2) + pow(cities[i].y - cities[j].y,2));
			table[i][j].dist = num;
		}
	}
}

void Random(Ant& ants, int citynum,int antnum)
{
	uniform_real_distribution<> unifr(0, (citynum));
	for (int i = 0; i < antnum; i++)
	{
		int count = 0;
		vector<bool> isSelect(citynum, false);
		Solution ant;
		while(count!=citynum)
		{
			int ran = unifr(generator);
			if (!isSelect[ran])
			{
				ant.push_back(ran);
				isSelect[ran] = true;
				count++;
			}
		}
		ants.push_back(ant);
	}
	/*for (int j = 0; j < antnum; j++)
	{
		for (auto i = ants[j].begin(); i != ants[j].end(); i++)
		{ cout << *i << " "; }
		cout << endl;
	}*/
}

void PherUpdate(Ant& ants, vector<vector<pheromone>>& table,int citynum,int Q,double p)
{
	for (int i = 0; i < citynum; i++)
		for (int j = 0; j < citynum; j++)
			table[i][j].phe *= 0.95;

	for (int i = 0; i < ants.size(); i++)
	{
		double totalDist = PathDist(ants[i],table);
		for (int j = 0; j < citynum - 1; j++)
		{
			table[ants[i][j]][ants[i][j + 1]].phe += Q / totalDist;
			table[ants[i][j + 1]][ants[i][j]].phe += Q / totalDist;
		}
	}
}

double PathDist(Solution ant, vector<vector<pheromone>>& table)
{
	double dist = 0;
	for (int i = 0; i < ant.size()-1; i++)
		dist += table[ant[i]][ant[i + 1]].dist;
	return dist;
}