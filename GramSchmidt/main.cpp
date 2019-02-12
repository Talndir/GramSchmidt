#include <iostream>

#include "vector.h"
#include "matrix.h"

bool cgs(std::vector<Vector>& as, Matrix& q, Matrix& r);
bool mgs(std::vector<Vector>& as, Matrix& q, Matrix& r);

void printVecs(std::vector<Vector>& vs);

int main()
{
	std::cout.precision(17);

	Vector v1(std::vector<double>{3, 1});
	Vector v2(std::vector<double>{2, 2});
	std::vector<Vector> t = { v1, v2 };

	Matrix q1(0, 0), r1(0, 0), q2(0, 0), r2(0, 0);
	bool c = cgs(t, q1, r1);
	bool m = mgs(t, q2, r2);

	if (!c)
		std::cout << "CGS failure" << std::endl;
	if (!m)
		std::cout << "MGS failure" << std::endl;

	std::cout << q1 << std::endl << q2 << std::endl;
	std::cin.ignore();

	return 0;
}

void printVecs(std::vector<Vector>& vs)
{
	for (int i = 0; i < vs.size(); ++i)
		std::cout << vs.at(i) << std::endl;
}

bool cgs(std::vector<Vector>& as, Matrix& q, Matrix& r)
{
	int n = as.size();
	if (!n)
		return false;	// No vectors

	int m = as.at(0).getLength();
	if (m < n)
		return false;	// Cannot all be linearly independent

	std::vector<Vector> qs;

	for (int i = 0; i < n; ++i)
	{
		Vector t = as.at(i);
		for (int j = 0; j < i; ++j)
			t -= qs.at(j) * (as.at(i) * qs.at(j));
		qs.push_back(t.norm());
	}
	
	q = Matrix(qs);
	return true;
}

bool mgs(std::vector<Vector>& as, Matrix& q, Matrix& r)
{
	int n = as.size();
	if (!n)
		return false;	// No vectors
	
	if (as.at(0).getLength() < n)
		return false;	// Cannot all be linearly independent

	std::vector<Vector> vs(as);
	std::vector<Vector> qs;

	for (int i = 0; i < n; ++i)
	{
		qs.push_back(vs.at(i).norm());

		for (int j = i + 1; j < n; ++j)
			vs.at(j) -= qs.at(i) * (vs.at(j) * qs.at(i));
	}

	q = Matrix(qs);
	return true;
}