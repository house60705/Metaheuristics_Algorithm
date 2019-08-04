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
	/*Chromo();
	Chromo(Solution);
	Chromo(int);
	~Chromo();*/
	Solution sol;
	int value;
};
/*Chromo::Chromo()
{
	sol = new Solution;
	value = new int;
}
Chromo::Chromo(Solution x) 
{
	sol = new Solution;
	*sol = x;
}
Chromo::Chromo(int x) 
{
	value = new int;
	*value = x;
}
Chromo::~Chromo() {
	delete sol;
	delete value;
}*/
void Initialization(vector<Chromo>& now, Solution& roundbestm, int& roundnum, int bit, int psize);
void Crossover(vector<Chromo>& now,int cPoint,int psize);
void mutation(Solution &now, int random);
int Evaluate(Solution a);
bool valueCmp(Chromo &a, Chromo &b);

int main(int argc, char* argv[])
{
	int runs = atoi(argv[1]), iters = atoi(argv[2]), bits = atoi(argv[3]), round = 1;
	
	int psize = atoi(argv[4]);
	//population size
	double muProb = atoi(argv[5]);   
	//mutation probability

	Solution Bestsol(bits, 0), Roundbest;
	vector<Chromo> Population;
	int  RoundbestNum = 0, BestsolNum = 0;
	uniform_real_distribution<> unifr(0, (bits - 1));
	
	while (runs--)
	//number of runs
	{
		cout << "round : " << round << endl;
		iters = atoi(argv[2]);

		Initialization(Population, Roundbest, RoundbestNum, bits, psize);
		//Initializing the value at first of a run

		/*for (int i = 0; i < psize; i++) {
			for (auto j = Population[i].sol.begin(); j != Population[i].sol.end(); ++j) {
			cout << *j;
			}
		cout << endl;*/

		for (int i = 0; i < psize; i++) 
			Population[i].value = Evaluate(Population[i].sol);
		//compute fitness
		sort(Population.begin(), Population.end(), valueCmp);
		//sort descend

		while (iters--)
		//number of iterations
		{
			/*for (int i = 0; i < psize; i++) {
				cout << Population[i].value << endl;
			}*/
			Crossover(Population,unifr(generator),psize);
			//select,crossover and copy
			
			/*--mutation will occur from some of new offspring--*/
			for (int i = psize / 2; i < psize; i++)
			{
				double muRate = r(generator);
				if (muRate > muProb)
				{
					mutation(Population[i].sol,unifr(generator));
				}
			}
			/*--------------------------------------------------*/

			for (int i = 0; i < psize; i++)
				Population[i].value = Evaluate(Population[i].sol);

			sort(Population.begin(), Population.end(), valueCmp);

			if (Population[0].value > RoundbestNum)
			//after sorting,Population[0] will be the best solution of Population
			{
				RoundbestNum = Population[0].value;
				Roundbest = Population[0].sol;
			}
		}
		if (RoundbestNum > BestsolNum)
		{
			BestsolNum = RoundbestNum;
			Bestsol = Roundbest;
			//updating the best solution this round
		}
		round++;
	}
	cout << "The best solution is : ";
	for (auto i = Bestsol.begin(); i != Bestsol.end(); i++) { cout << *i; }
	cout << " , the number of 1 is	: " << BestsolNum << endl;
	//output
	system("pause");
}

void Initialization(vector<Chromo>& now, Solution& roundbest, int& roundNum, int bits, int psize) {
	Solution init(bits, 0);
	now.resize(psize);
	for (int i = 0; i < psize; i++) {
		now[i].sol = init;
		now[i].value = 0;
		for (auto j=now[i].sol.begin(); j != now[i].sol.end(); ++j) {
			*j = unif(generator);
		}
	}
	//begin with random solution
	roundbest.resize(bits);
	roundNum = 0;
}

int Evaluate(Solution a) 
//the summary of 1 
{
	int sum = 0;
	for (auto i = a.begin(); i != a.end(); ++i) {
		sum += *i;
	}
	return sum;
}
void Crossover(vector<Chromo> &now,int cPoint,int psize) {
	vector<Solution> Children;
	int n = 0;
	
	/*------select and crossover-------*/
	for (int i = 0; i < psize; i += 2)
	//if the size of population is 10,then will generate 5 offspring
	{
		Solution item1=now[i].sol,item2=now[i+1].sol;
		//copy the best and second best chromosome 

		for (int j = 0; j < cPoint; j++)
			swap(item1[j], item2[j]);
		//crossover
		
		Children.push_back(item1);
		Children.push_back(item2);
	}
	/*---------------------------------*/

	/*------cover bad chromosomes------*/
	for (int i = psize/2; i < psize; i++) 
	{
		now[i].sol = Children[n];
		n++;
	}
	/*---------------------------------*/
}

void mutation(Solution &now, int random)
{
	now[random] = abs(now[random] - 1);
}

bool valueCmp(Chromo &a, Chromo &b)
{
	return a.value > b.value;
}