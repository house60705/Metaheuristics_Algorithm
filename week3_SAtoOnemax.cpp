#include <iostream>
#include <random>
#include <vector>
#include <math.h>
using namespace std;
int Evaluate(vector<int> a) {
	int sum = 0;
	for (auto i = a.begin(); i != a.end(); ++i) {
		sum += *i;
	}
	return sum;
}
vector<int> NeighborNode(vector<int> a, int random)
{
	a[random] = abs(a[random] - 1);
	return a;
}
int main(int argc, char* argv[])
{
	int  runs = atoi(argv[1]), times = atoi(argv[2]), bits = atoi(argv[3]), round = 1;
	int  input, num = 1;
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> unif(0, 1);
	uniform_real_distribution<> unifr(0, (bits - 1));
	uniform_real_distribution<double> r(0, 1);
	vector<int> BestSolution(bits, 0);
	int BestSolutionNum = 0;
	/*for (auto i = NowSolution.begin(); i != NowSolution.end(); ++i) {
	cout << *i;
	}*/
	while (runs--)														
	{
		cout << "round : " << round << endl;
		times = atoi(argv[2]);
		vector<int> NowSolution(bits, 0);
		vector<int> NeightborSolution(bits, 0);
		vector<int> RoundBestSolution(bits, 0);
		double NowSolutionNum, RoundBestSolutionNum = 0, NeightborSolutionNum = 0;
		double temp = 50000, ram = r(generator);						//r會嚴重影響結果
		for (auto i = NowSolution.begin(); i != NowSolution.end(); ++i) {
			*i = unif(generator);
		}
		if (Evaluate(NowSolution) > RoundBestSolutionNum)
		{
			RoundBestSolutionNum = Evaluate(NowSolution);
			RoundBestSolution = NowSolution;
		}
		cout << ram << endl;
		while (temp>1)													//溫度也是
		{
			NeightborSolution = NeighborNode(NowSolution, unifr(generator));
			NeightborSolutionNum = Evaluate(NeightborSolution);
			NowSolutionNum = Evaluate(NowSolution);
			double Pa = exp((NeightborSolutionNum - NowSolutionNum) / temp);
			if (Pa >= ram) {
				RoundBestSolutionNum = NeightborSolutionNum;
				RoundBestSolution = NeightborSolution;
				NowSolution = NeightborSolution;
				NowSolutionNum = NeightborSolutionNum;
			}
			temp *= 0.99;
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