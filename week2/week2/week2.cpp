#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;

random_device rd;
mt19937 generator(rd());
uniform_int_distribution<int> unif(0, 1);


int Evaluate(vector<int> a, vector<int> weight, vector<int> value, int Bagweight) {
	int sumWeight = 0, sumValue = 0;
	for (int i = 0; i < a.size(); i++) {

		if (a[i]) {
			sumWeight += weight[i];
			sumValue += value[i];
		}
	}
	if (sumWeight > Bagweight) { return 0; }
	else { return sumValue; }
}

vector<int> NeighborNode(vector<int> a, vector<int> weight, vector<int> value, int Bagweight, int random1, int random2)
{
	vector<int> b = a;
	if (random1>random2) {
		for (int i = random2; i <= random1; i++)
			b[i] = unif(generator);
	}
	else {
		for (int i = random1; i <= random2; i++)
			b[i] = abs(b[i] - 1);
	}
	return b;
}
int main(int argc, char* argv[])
{
	int  runs = atoi(argv[1]), times = atoi(argv[2]), bits = atoi(argv[3]), round = 1;
	int  input, num = 1, BagWeight = 750;
	vector<int> weight, value;
	ifstream infileWeight("p07_w.txt");
	while (infileWeight >> input) {
		weight.push_back(input);
		num++;
	}
	ifstream infileValue("p07_v.txt");
	while (infileValue >> input) {
		value.push_back(input);
	}
	uniform_real_distribution<> unifr(0, (bits - 1));
	vector<int> BestSolution(bits, 0);
	int BestSolutionNum = 0;
	/*for (auto i = NowSolution.begin(); i != NowSolution.end(); ++i) {
	cout << *i;
	}*/
	while (BestSolutionNum!=1458)
	{
		//cout << "round : " << round << endl;
		times = atoi(argv[2]);
		vector<int> NowSolution(bits, 0);
		vector<int> NeightborSolution(bits, 0);
		vector<int> RoundBestSolution(bits, 0);
		int NowSolutionNum, RoundBestSolutionNum = 0, NeightborSolutionNum = 0;
		for (auto i = NowSolution.begin(); i != NowSolution.end(); ++i) {
			*i = unif(generator);
		}
		if (Evaluate(NowSolution, weight, value, BagWeight) > RoundBestSolutionNum)
		{
			RoundBestSolutionNum = Evaluate(NowSolution, weight, value, BagWeight);
			RoundBestSolution = NowSolution;
		}

		while (times--)
		{
			
			NeightborSolution = NeighborNode(NowSolution, weight, value, BagWeight, unifr(generator), unifr(generator));
			NeightborSolutionNum = Evaluate(NeightborSolution, weight, value, BagWeight);
			NowSolutionNum = Evaluate(NowSolution, weight, value, BagWeight);

			if (NeightborSolutionNum > NowSolutionNum) {
				RoundBestSolutionNum = NeightborSolutionNum;
				RoundBestSolution = NeightborSolution;
				NowSolution = NeightborSolution;
				NowSolutionNum = NeightborSolutionNum;
			}
		}
		if (RoundBestSolutionNum > BestSolutionNum)
		{
			BestSolutionNum = RoundBestSolutionNum;
			BestSolution = RoundBestSolution;
		}
		round++;
	}
	cout << "The best solution is : ";
	for (auto i = BestSolution.begin(); i != BestSolution.end(); i++) { cout << *i; }
	cout << " , the number of 1 is	: " << BestSolutionNum << endl;
	system("pause");
}
