#include <iostream>
#include <random>
#include <vector>
#include <math.h>
using namespace std;

typedef vector<int> Solution;
/*----set random number device-----*/
random_device rd;
mt19937 generator(rd());
uniform_int_distribution<> unif(0, 1);
/*---------------------------------*/
void Initialization(Solution& now, Solution& neighbor, Solution& roundbest, int& nownum, int& neighbornum, int& roundnum, int bit);
int Evaluate(Solution a);
Solution NeighborNode(Solution a, int random);

int main(int argc, char* argv[])
{
	int  times = atoi(argv[1]), iters = atoi(argv[2]), bits = atoi(argv[3]), round = 1;
	Solution Bestsol(bits, 0), Nowsol, Neighbor, Roundbest;
	int NowsolNum, RoundbestNum = 0, NeighborNum = 0;
	uniform_real_distribution<> unifr(0, (bits - 1));
	int BestsolNum = 0;
	while (times--)
		//number of runs
	{
		cout << "round : " << round << endl;
		iters = atoi(argv[2]);
		Initialization(Nowsol, Neighbor, Roundbest, NowsolNum, NeighborNum, RoundbestNum, bits);
		//Initializing the value at first of a run
		while (iters--)
			//number of iterations
		{
			Neighbor = NeighborNode(Nowsol, unifr(generator));
			//find the neighbor of this solution 

			NeighborNum = Evaluate(Neighbor);
			NowsolNum = Evaluate(Nowsol);
			//fitness function

			if (NeighborNum > NowsolNum)
				//neighnor is better fitness
			{
				RoundbestNum = NeighborNum;
				Roundbest = Neighbor;
				Nowsol = Neighbor;
				NowsolNum = NeighborNum;
			}
		}
		if (RoundbestNum > BestsolNum)
		{
			BestsolNum = RoundbestNum;
			Bestsol = Roundbest;
			////updating the best solution this round
		}
		round++;
	}
	cout << "The best solution is : ";
	for (auto i = Bestsol.begin(); i != Bestsol.end(); i++) { cout << *i; }
	cout << " , the number of 1 is	: " << BestsolNum << endl;
	//output
}

void Initialization(Solution& now, Solution& neighbor, Solution& roundbest, int& nowNum, int& neighborNum, int& roundNum, int bits) {
	now.resize(bits);
	neighbor.resize(bits);

	for (auto i = now.begin(); i != now.end(); ++i) {
		*i = unif(generator);
	}
	//begin with random solution

	roundbest = now;
	nowNum = Evaluate(now);
	neighborNum = 0;
	roundNum = nowNum;
}

int Evaluate(Solution a) {
	int sum = 0;
	for (auto i = a.begin(); i != a.end(); ++i) {
		sum += *i;
	}
	return sum;
}
Solution NeighborNode(Solution a, int random)
{
	a[random] = abs(a[random] - 1);
	return a;
}