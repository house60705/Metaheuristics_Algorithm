#include <iostream>
#include <random>
#include <vector>
#include <math.h>
#include<algorithm>
using namespace std;
typedef vector<int> Solution;
/*----set random number device-----*/
random_device rd;
mt19937 generator(rd());
uniform_int_distribution<> unif(0, 1);
uniform_real_distribution<double> r(0, 1);
/*---------------------------------*/

class Chromo
	//set a class involved solution and its fitness value
{
public:
	Solution sol;
	int value;
};

bool valueCmp(Chromo& a, Chromo& b);
void Evaluate(vector<Chromo>& a, int psize, int& eva);
void Initialization(vector<Chromo>& now, Solution& roundbestm, int& roundnum, int bit, int psize);
void Selection(vector<Chromo>& population, int psize, int bits);
void Crossover(vector<Chromo>& now,int bits, int psize);
void Mutation(vector<Chromo>& now, int psize, int bits, double muProb);
Chromo Findbest(vector<Chromo> now);

int main(int argc, char* argv[])
{
	int runs = atoi(argv[1]), iters = atoi(argv[2]), bits = atoi(argv[3]), round = 1;
	int eva = 0;
	int psize = atoi(argv[4]);
	//population size
	double muProb = atoi(argv[5]);
	//mutation probability

	vector<Chromo> Population;
	Chromo Bestsol, Roundbest;
	Bestsol.value = 0;
	uniform_real_distribution<> unifr(0, (bits - 1));

	while (runs--)
		//number of runs
	{
		//cout << "round : " << round << endl;
		iters = atoi(argv[2]);

		Initialization(Population, Roundbest.sol, Roundbest.value, bits, psize);
		//Initializing the value at first of a run

		/*for (int i = 0; i < psize; i++) {
			for (auto j = Population[i].sol.begin(); j != Population[i].sol.end(); ++j) {
				cout << *j;
			}
			cout << endl;
		}
		cout << endl;*/
		Evaluate(Population,psize,eva);
		//compute fitness
		//sort descend

		while (Roundbest.value!=100)
			//number of iterations
		{

			Selection(Population, psize, bits);


			Crossover(Population,bits, psize);

			Mutation(Population, psize,bits,muProb);
			Evaluate(Population,psize,eva);

			/*cout << "value" << endl;
			for (int i = 0; i < psize; i++) {
				cout << Population[i].value << " ";
			}
			cout << endl;*/
			Chromo Nowbest = Findbest(Population);

			if (Nowbest.value >= Roundbest.value)
				Roundbest = Nowbest;
		}
		if (Roundbest.value >= Bestsol.value)
			Bestsol = Roundbest;
			//updating the best solution this round
		round++;
		cout << eva << endl;
	}
	cout << "The best solution is : ";
	for (auto i = Bestsol.sol.begin(); i != Bestsol.sol.end(); i++) { cout << *i; }
	cout << " , the value is	: " << Bestsol.value << endl;
	//output
}

void Initialization(vector<Chromo>& now, Solution& roundbest, int& roundNum, int bits, int psize)
{
	Solution init(bits, 0);
	now.resize(psize);
	for (int i = 0; i < psize; i++) {
		now[i].sol = init;
		now[i].value = 0;
		for (auto j = now[i].sol.begin(); j != now[i].sol.end(); ++j) {
			*j = unif(generator);
		}
	}
	//begin with random solution
	roundbest.resize(bits);
	roundNum = 0;
}

void Evaluate(vector<Chromo> &a,int psize,int &eva)
//the summary of 1 
{
	for (int i = 0; i < psize; i++)
	{
		int sum = 0;
		for (auto j = a[i].sol.begin(); j!=a[i].sol.end(); ++j) {
			sum += *j;
		}
		a[i].value = sum;
	}
	eva++;
}

void Selection(vector<Chromo> &population,int psize,int bits)
{
	uniform_real_distribution<> unifr(0, (psize - 1));
	vector<Chromo> selects;
	for (int i = 0; i < psize; i++)
	{
		int r1 = unifr(generator), r2 = unifr(generator);
		if (population[r1].value > population[r2].value)
			selects.push_back(population[r1]);
		else
			selects.push_back(population[r2]);
	}
	population = selects;
}

void Crossover(vector<Chromo>& now, int bits, int psize) 
{
	uniform_real_distribution<> unifr(0, (bits- 1));
	for (int i = 0; i < psize; i += 2)
	{
		int random = unifr(generator);
		for (int j = 0; j < random; j++)
			swap(now[i].sol[j], now[i+1].sol[j]);
		//crossover
	}
}

void Mutation(vector<Chromo>& now,int psize,int bits, double muProb)
{
	uniform_real_distribution<> unifr(0, (bits - 1));
	for (int i = 0; i < psize; i++)
	{
		int random = unifr(generator);
		double muRate = r(generator);
		if (muRate > muProb)
		{
			now[i].sol[random] = !now[i].sol[random];
		}
	}
	
}
Chromo Findbest(vector<Chromo> now)
{
	Chromo best;
	best.value = 0;
	for (int i = 0; i < now.size(); i++)
	{
		if (now[i].value > best.value)
			best = now[i];
	}
	return best;
}
bool valueCmp(Chromo& a, Chromo& b)
{
	return a.value > b.value;
}