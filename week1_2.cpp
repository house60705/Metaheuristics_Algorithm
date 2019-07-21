#include <iostream>
#include <random>
#include <vector>

using namespace std;

int numOf1(vector<int> a) {
	int sum = 0;
	for (auto i = a.begin(); i != a.end(); ++i) {
		sum += *i;
	}
	return sum;
}
/*
vector<int> BinaryAdd(const vector<int>& a, int temp) {
	vector<int> b(temp, 0);
	b.back() = 1;
	vector<int> c(temp);
	int AddCarry = 0;

	for (int i = temp - 1; i >= 0; i--) {
		c[i] = ((a[i] ^ b[i]) ^ AddCarry);
		AddCarry = ((a[i] & b[i]) | (a[i] & AddCarry)) | (b[i] & AddCarry);
	}

	return c;
}

vector<int> BinarySub(const vector<int>& a, int temp) {
	vector<int> b(temp, 1);
	vector<int> c(temp);
	int AddCarry = 0;

	for (int i = temp - 1; i >= 0; i--) {
		c[i] = ((a[i] ^ b[i]) ^ AddCarry);
		AddCarry = ((a[i] & b[i]) | (a[i] & AddCarry)) | (b[i] & AddCarry);
	}
	return c;
}
*/
vector<int> NeighborNode(vector<int>& a, int random)
{
	vector<int> b = a;

	if (!b[random]) { b[random] = 1; }
	else { b[random] = 0; }
	if (numOf1(a) >= numOf1(b)) { return a; }
	return b;
	/*vector<int> nexts = BinaryAdd(a, a.size());
	vector<int> prev = BinarySub(a, a.size());
	if (numOf1(next) < numOf1(prev)) { a = prev; }
	else { a = next; }*/
}
int main(int argc, char** argv)
{
	int  runs = atoi(argv[1]), times = atoi(argv[2]), bits = atoi(argv[3]), round = 1;
	random_device rd;
	mt19937_64 generator(rd());
	uniform_int_distribution<> unif(0, 1);
	uniform_real_distribution<> unifr(0, 99);
	vector<int> BestSolution(100, 0);
	int BestSolutionNum = 0;
	/*for (auto i = NowSolution.begin(); i != NowSolution.end(); ++i) {
		cout << *i;
	}*/
	while (runs--)
	{
		times = atoi(argv[2]);
		vector<int> NowSolution(bits, 0);
		vector<int> RoundBestSolution(bits, 0);
		int NowSolutionNum, RoundBestSolutionNum = 0;
		cout << "round : " << round << endl;
		for (auto i = NowSolution.begin(); i != NowSolution.end(); ++i) {
			*i = unif(generator);
		}
		if (numOf1(NowSolution) > RoundBestSolutionNum)
		{
			RoundBestSolutionNum = numOf1(NowSolution);
			RoundBestSolution = NowSolution;
		}

		while (times--)
		{
			NowSolution = NeighborNode(NowSolution, unifr(generator));
			NowSolutionNum = numOf1(NowSolution);
			RoundBestSolutionNum = NowSolutionNum;
			RoundBestSolution = NowSolution;
			/*for (auto i = NowSolution.begin(); i != NowSolution.end(); ++i) {
				cout << *i;
			}
			cout << endl;*/
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
}
