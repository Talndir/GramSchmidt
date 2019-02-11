#include <iostream>

#include "vector.h"
#include "matrix.h"

std::vector<Vector> cgs(std::vector<Vector>& as);
std::vector<Vector> mgs(std::vector<Vector>& as);

void printVecs(std::vector<Vector>& vs);

int main()
{
	std::cout.precision(17);

	Vector v1(std::vector<double>{3, 1});
	Vector v2(std::vector<double>{2, 2});
	std::vector<Vector> t = { v1, v2 };

	std::vector<Vector> vs = cgs(t);
	std::vector<Vector> qs = mgs(t);
	printVecs(vs);
	std::cout << std::endl;
	printVecs(qs);

	std::cin.ignore();

	return 0;
}

void printVecs(std::vector<Vector>& vs)
{
	for (int i = 0; i < vs.size(); ++i)
		std::cout << vs.at(i) << std::endl;
}

std::vector<Vector> cgs(std::vector<Vector>& as)
{
	int n = as.size();
	if (!n)
		return std::vector<Vector>(0, Vector(0));

	int m = as.at(0).getLength();

	std::vector<Vector> qs;

	for (int i = 0; i < n; ++i)
	{
		Vector t = as.at(i);
		for (int j = 0; j < i; ++j)
			t -= qs.at(j) * (as.at(i) * qs.at(j));
		qs.push_back(t.norm());
	}
	
	return qs;
}

std::vector<Vector> mgs(std::vector<Vector>& as)
{
	int n = as.size();
	if (!n)
		return std::vector<Vector>(0, Vector(0));

	std::vector<Vector> vs(as);
	std::vector<Vector> qs;

	for (int i = 0; i < n; ++i)
	{
		qs.push_back(vs.at(i).norm());

		for (int j = i + 1; j < n; ++j)
			vs.at(j) -= qs.at(i) * (vs.at(j) * qs.at(i));
	}

	return qs;
}