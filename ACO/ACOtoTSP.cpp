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

class probTable
{
public:
	double val;
	bool isSel;
};

class city
{
public:
	int temp;
	int x;
	int y;
};
void Initialization(vector<vector<pheromone>>& table, vector<city>& cities, int citynum, int antnum);
void Random(Ant& ants, int citynum, int antnum);
void SolutionCons(vector<vector<pheromone>> table, Ant& ants, int citynum, double alpha, double beta);
void PherUpdate(Ant ants, vector<vector<pheromone>>& table, int citynum, int Q, double p);
double totalPij(vector<vector<pheromone>> table, vector<probTable> pTable, int start, double alpha, double beta);
double PathDist(Solution ant, vector<vector<pheromone>>& table);

int main(int argc, char* argv[])
{
	int runs = atoi(argv[1]), iters = atoi(argv[2]), citynum = atoi(argv[3]), antnum = atoi(argv[4]), Q = atoi(argv[5]);
	double p = atoi(argv[6]), alpha = atoi(argv[7]), beta = atoi(argv[8]), round = 1;
	vector<vector<pheromone>> table;
	vector<city> cities;
	Ant ants;
	uniform_real_distribution<> unifr(0, (citynum - 1));
	cout << endl;
	while (runs--)
		//number of runs
	{
		//cout << "round : " << round << endl;
		iters = atoi(argv[2]);
		Initialization(table, cities, citynum, antnum);
		Random(ants, citynum, antnum);
		PherUpdate(ants, table, citynum, Q, p);
		//updating the best solution this round
		/*for (int i = 0; i < ants.size(); i++) {
			for (auto j = ants[i].begin(); j != ants[i].end(); ++j)
			{
				cout << *j << " ";
			}
			cout << endl;
		}
		cout << endl;*/
		while (iters--)
		{
			SolutionCons(table, ants, citynum, alpha, beta);

			PherUpdate(ants, table, citynum, Q, p);
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
			double num = sqrt(pow(cities[i].x - cities[j].x, 2) + pow(cities[i].y - cities[j].y, 2));
			table[i][j].dist = num;
		}
	}
}

void Random(Ant& ants, int citynum, int antnum)
{
	uniform_real_distribution<> unifr(0, (citynum));
	for (int i = 0; i < antnum; i++)
	{
		int count = 0;
		vector<bool> isSelect(citynum, false);
		Solution ant;
		while (count != citynum)
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

void SolutionCons(vector<vector<pheromone>> table, Ant& ants, int citynum, double alpha, double beta)
{
	probTable init;
	init.isSel = false;
	init.val = 0;
	uniform_real_distribution<> unifr(0, (citynum));
	for (int i = 0; i < ants.size(); i++)
	{
		int start = 0;
		vector<probTable> pTable(citynum, init);
		ants[i][0] = unifr(generator);
		pTable[ants[i][0]].isSel = true;
		for (int j = 1; j < citynum; j++)
		{
			double seleProb = r(generator);
			double temp = 0;
			double totalP = totalPij(table, pTable, start, alpha, beta);
			//cout << seleProb << endl;
			/*------------update pTable-----------*/
			for (int k = 0; k < pTable.size(); k++)
			{
				if (!pTable[k].isSel)
				{
					pTable[k].val = ((pow(table[start][k].phe, alpha) * pow(table[start][k].dist, beta)) / totalP) + temp;
					//cout << pow(table[start][k].phe, alpha) << " " << pow(table[start][k].dist, beta) << endl;
					temp = pTable[k].val;
					//cout << pTable[k].val << endl;
					if (seleProb - pTable[k].val < 0)
					{
						ants[i][j] = k;
						pTable[k].isSel = true;
					}
				}
			}
			/*for (auto k=ants[i].begin(); k != ants[i].end(); ++k)
				{
					cout << *k << " ";
				}
				cout << endl;*/
				/*for (auto k=0; k <= pTable.size(); k++)
					{
						cout << pTable[k].val << " ";
					}
					cout << endl;*/
					/*------------------------------------*/
			start++;
		}
	}

}


double totalPij(vector<vector<pheromone>> table, vector<probTable> pTable, int start, double alpha, double beta)
{
	double sum = 0;
	for (int i = 0; i < pTable.size(); i++)
	{
		if (!pTable[i].isSel)
			sum += pow(table[start][i].phe, alpha) * pow(table[start][i].dist, beta);
	}
	return sum;
}

void PherUpdate(Ant ants, vector<vector<pheromone>>& table, int citynum, int Q, double p)
{
	for (int i = 0; i < citynum; i++)
		for (int j = 0; j < citynum; j++)
			table[i][j].phe *= p;

	for (int i = 0; i < ants.size(); i++)
	{
		double totalDist = PathDist(ants[i], table);
		for (int j = 0; j < citynum - 1; j++)
		{
			table[ants[i][j]][ants[i][j + 1]].phe += Q / totalDist;
			table[ants[i][j + 1]][ants[i][j]].phe += Q / totalDist;
			cout << table[ants[i][j]][ants[i][j + 1]].phe << " ";
		}
	}
	/*for (int i = 0; i < citynum; i++)
	{
		for (int j = 0; j < citynum; j++)
		{
			cout << table[i][j].phe << " ";
		}
		cout << endl;
	}*/
}

double PathDist(Solution ant, vector<vector<pheromone>>& table)
{
	double dist = 0;
	for (int i = 0; i < ant.size() - 1; i++)
		dist += table[ant[i]][ant[i + 1]].dist;
	return dist;
}