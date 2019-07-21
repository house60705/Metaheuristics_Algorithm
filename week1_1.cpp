#include <iostream>
#include <vector>

using namespace std;
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

int numOf1(vector<int> a) {
	int sum = 0;
	for (auto i = a.begin(); i != a.end(); ++i) {
		sum += *i;
	}
	return sum;
}

int main()
{
	int BestSolutionNum = 0, NowSolutionNum;
	vector<int> BestSolution(32, 0);
	vector<int> NowSolution(32, 0);
	while (BestSolutionNum != 32) {
		NowSolution = BinaryAdd(NowSolution, 32);
		NowSolutionNum = numOf1(NowSolution);
		if (NowSolutionNum > BestSolutionNum) {
			BestSolutionNum = NowSolutionNum;
			BestSolution = NowSolution;
		}
	}
	cout << "最佳解為 : ";
	for (auto i = BestSolution.begin(); i != BestSolution.end(); ++i) {
		cout << *i;
	}
	cout << " , 共有" << BestSolutionNum << "個1\n";

	return 0;
}*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

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

int numOf1(vector<int> a) {
	int sum = 0;
	for (auto i = a.begin(); i != a.end(); ++i) {
		sum += *i;
	}
	return sum;
}

int main(int argc, char* argv[])
{
	int runs=atoi(argv[1]),Iteration=atoi(argv[2]),bits=atoi(argv[3]);
	int BestSolutionNum = 0,NowSolutionNum;
	vector<int> BestSolution(bits, 0);
	vector<int> NowSolution(bits, 0);
	while (Iteration--) {
		NowSolution = BinaryAdd(NowSolution, bits);
		NowSolutionNum = numOf1(NowSolution);
		if (NowSolutionNum > BestSolutionNum) {
			BestSolutionNum = NowSolutionNum;
			BestSolution = NowSolution;
		}
	}
	cout << "The best solution is : ";
	for (auto i = BestSolution.begin(); i != BestSolution.end(); ++i) {
		cout << *i;
	}
	cout << " , The number of 1 is " << BestSolutionNum << endl;

	return 0;
}
