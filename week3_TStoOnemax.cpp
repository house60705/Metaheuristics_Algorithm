#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int Evaluate(vector<int> a) {
	int sum = 0;
	for (auto i = a.begin(); i != a.end(); ++i) {
		sum += *i;
	}
	return sum;
}
vector<int> NeighborNode(vector<int> a,vector<string> &TabuList, int random)
//TabuList pass by ref.
{
	vector<int> b = a;
	b[random] = abs(b[random] - 1);
	/*converting vector<int> to string*/
	stringstream ss;
	for (auto i = 0; i < b.size(); i++) {	
			ss << b[i];
	}
	string str = ss.str();
	/*-------------------------------*/
	for (auto i = TabuList.begin(); i != TabuList.end(); ++i) {
		if (str.compare(*i)==0) {     
		//comparing all of TabuList elements to the solution. if one of them is the same , it will return 0
			return a;
		}
	}
	if (TabuList.size() >= 30) {
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
	random_device rd;
	mt19937_64 generator(rd());
	uniform_int_distribution<> unif(0, 1);
	uniform_real_distribution<> unifr(0, bits-1);
	vector<int> BestSolution(bits, 0);
	int BestSolutionNum = 0;
	/*for (auto i = NowSolution.begin(); i != NowSolution.end(); ++i) {
	cout << *i;
	}*/
	while (runs--)
	{
		times = atoi(argv[2]);
		vector<int> NowSolution(bits, 0);
		vector<int> RoundBestSolution(bits, 0);
		vector<int> NeightborSolution(bits, 0);
		vector<string> TabuList;
		int NowSolutionNum, RoundBestSolutionNum = 0,NeightborSolutionNum = 0;
		cout << "round : " << round << endl;
		for (auto i = NowSolution.begin(); i != NowSolution.end(); ++i) {
			*i = unif(generator);
		}
		if (Evaluate(NowSolution) > RoundBestSolutionNum)
		{
			RoundBestSolutionNum = Evaluate(NowSolution);
			RoundBestSolution = NowSolution;
		}

		while (times--)
		{
			NeightborSolution = NeighborNode(NowSolution,TabuList, unifr(generator));
			NeightborSolutionNum = Evaluate(NeightborSolution);
			NowSolutionNum = Evaluate(NowSolution);
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
	cout << " , the number of 1 is : " << BestSolutionNum << endl;
	system("pause");
}