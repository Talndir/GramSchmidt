#include <iostream>
#include <iomanip>

#include "vector.h"
#include "matrix.h"

bool cgs(std::vector<Vector>& as, Matrix& q, Matrix& r);
bool mgs(std::vector<Vector>& as, Matrix& q, Matrix& r);
bool solve(Matrix& a, Vector& x, Vector& b);

void printVecs(std::vector<Vector>& vs);
Matrix identity(int n);

int main()
{
	std::cout.precision(20);
	std::cout << std::fixed;

	const double k = 0.1;
	std::vector<Vector> t =
	{	Vector({-2.0, k,   0.0, 0.0}),
		Vector({-1.0, 0.0, k,   0.0}),
		Vector({ 1.0, 0.0, 0.0,   k}),
		Vector({ 2.0, 0.0, 0.0, 0.0}) };

	Matrix a(t);
	Matrix id = identity(4);

	Matrix q1(0, 0), r1(0, 0), q2(0, 0), r2(0, 0);
	bool c = cgs(t, q1, r1);
	bool m = mgs(t, q2, r2);

	if (!c)
		std::cout << "CGS failure" << std::endl;
	if (!m)
		std::cout << "MGS failure" << std::endl;

	std::cout <<
		"A" << std::endl << a << std::endl << std::endl <<
		"CGS: Q, R, Q*QT - I:" << std::endl <<
		q1 << std::endl << 
		r1 << std::endl << 
		q1 * q1.transpose() - id << std::endl << std::endl <<
		"MGS: Q, R, Q*QT - I:" << std::endl <<
		q2 << std::endl << 
		r2 << std::endl <<
		q2 * q2.transpose() - id << std::endl;

	Vector x(0), b({1.0, 1.0, 1.0, 1.0});
	solve(a, x, b);
	std::cout << 
		"A" << std::endl << a << std::endl <<
		"x" << std::endl << x << std::endl <<
		"b" << std::endl << b << std::endl;

	std::cin.ignore();

	return 0;
}

void printVecs(std::vector<Vector>& vs)
{
	for (int i = 0; i < vs.size(); ++i)
		std::cout << vs.at(i) << std::endl;
}

Matrix identity(int n)
{
	Matrix m(n, n);
	for (int i = 0; i < n; ++i)
		m[i][i] = 1.0;

	return m;
}

bool cgs(std::vector<Vector>& as, Matrix& q, Matrix& r)
{
	int n = as.size();
	if (!n)
		return false;	// No vectors

	int m = as.at(0).getLength();
	if (m < n)
		return false;	// Cannot all be linearly independent

	std::vector<Vector> qs, rs;
	std::vector<double> v(m, 0.0);

	double s;

	for (int i = 0; i < n; ++i)
	{
		Vector t = as.at(i);
		for (int j = 0; j < i; ++j)
		{
			s = as.at(i) * qs.at(j);
			v.at(j) = s;
			t -= qs.at(j) * s;
		}
		v.at(i) = t.norm();
		qs.push_back(t.normalise());
		rs.push_back(v);
	}
	
	q = Matrix(qs);
	r = Matrix(rs);
	return true;
}

bool mgs(std::vector<Vector>& as, Matrix& q, Matrix& r)
{
	int n = as.size();
	if (!n)
		return false;	// No vectors
	
	int m = as.at(0).getLength();
	if (m < n)
		return false;	// Cannot all be linearly independent

	std::vector<Vector> vs(as), rs, qs;
	std::vector<double> v(m, 0.0);

	double s;

	for (int i = 0; i < n; ++i)
	{
		qs.push_back(vs.at(i).normalise());
		v.at(i) = vs.at(i).norm();

		for (int j = i + 1; j < n; ++j)
		{
			s = vs.at(j) * qs.at(i);
			v.at(j) = s;
			vs.at(j) -= qs.at(i) * s;
		}
		rs.push_back(v);
		v.assign(m, 0.0);
	}

	q = Matrix(qs);
	r = Matrix(rs).transpose();
	return true;
}

bool solve(Matrix& a, Vector& x, Vector& b)
{
	int n = a.getCols();
	int m = a.getRows();
	if (m != b.getLength())
		return false;	// Incombatible dimensions

	Matrix q(0, 0), r(0, 0);
	std::vector<Vector> as = a.asVectors();
	cgs(as, q, r);
	Vector v = q.transpose() * b;

	x = Vector(n);
	for (int i = n - 1; i >= 0; --i)
	{
		double s = v[i];
		for (int j = n - 1; j > i; --j)
			s -= r[j][i] * x[j];

		x[i] = s / r[i][i];
	}

	return true;
}