#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <math.h>
#include <string>
#include <sstream>
using namespace std;

random_device rd;
mt19937 generator(rd());
uniform_int_distribution<int> unif(0, 1);
int BagWeight = 6404180;

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

vector<int> NeighborNode(vector<int> a, vector<string>& TabuList, vector<int> weight, vector<int> value, int Bagweight, int random1, int random2,int &NeightborSolutionNum)
//TabuList pass by ref.
{
	vector<int> b = a;
	if (random1 > random2) {
		for (int i = random2; i <= random1; i++)
			b[i] = unif(generator);
	}
	else {
		for (int i = random1; i <= random2; i++)
			b[i] = unif(generator);
	}
	/*converting vector<int> to string*/
	stringstream ss;
	for (auto i = 0; i < b.size(); i++) {
		ss << b[i];
	}
	string str = ss.str();
	/*-------------------------------*/
	for (auto i = TabuList.begin(); i != TabuList.end(); ++i) {
		if (str.compare(*i) == 0) {
			//comparing all of TabuList elements to the solution. if one of them is the same , it will return 0
			return a;
		}
	}
	NeightborSolutionNum = Evaluate(b, weight, value, BagWeight);
	if (TabuList.size() >= 5) {
		//set TabuList's size
		TabuList.erase(TabuList.begin());
		//pop the element of list
	}
	TabuList.push_back(str);
	return b;
}
int main(int argc, char** argv)
{
	int  runs = atoi(argv[1]), times = atoi(argv[2]), bits = atoi(argv[3]), round = 1;
	int  input;
	vector<int> weight, value;
	ifstream infileWeight("p08_w.txt");
	while (infileWeight >> input) {
		weight.push_back(input);
	}
	ifstream infileValue("p08_v.txt");
	while (infileValue >> input) {
		value.push_back(input);
	}
	uniform_real_distribution<> unifr(0, bits - 1);
	vector<int> BestSolution(bits, 0);
	int BestSolutionNum = 0;
	/*for (auto i = NowSolution.begin(); i != NowSolution.end(); ++i) {
	cout << *i;
	}*/
	int sum = 0;
	while (runs--)
	{
		times = atoi(argv[2]);
		vector<int> NowSolution(bits, 0);
		vector<int> RoundBestSolution(bits, 0);
		vector<int> NeightborSolution(bits, 0);
		vector<string> TabuList;
		int NowSolutionNum, RoundBestSolutionNum = 0, NeightborSolutionNum = 0;
		//cout << "round : " << round << endl;
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
			NeightborSolution = NeighborNode(NowSolution, TabuList, weight, value, BagWeight, unifr(generator), unifr(generator),NeightborSolutionNum);
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
		sum += RoundBestSolutionNum;
		//round++;
	}
	cout << "The best solution is : ";
	for (auto i = BestSolution.begin(); i != BestSolution.end(); i++) { cout << *i; }
	cout << " , the value is : " << BestSolutionNum << endl;
	cout << sum/50 << endl;
}