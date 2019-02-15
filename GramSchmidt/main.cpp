#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "vector.h"
#include "matrix.h"

bool cgs(std::vector<Vector>& as, Matrix& q, Matrix& r);
bool mgs(std::vector<Vector>& as, Matrix& q, Matrix& r);
bool solve(Matrix& a, Vector& b, Vector& xc, Vector& xm);

Matrix identity(int n);

void run(double k, std::ostream& out);

int main()
{
	std::ofstream outfile;
	outfile.open("out.txt", std::ofstream::out | std::ofstream::trunc);

	run(0.1, outfile);
	run(0.00001, outfile);
	run(0.0000000001, outfile);

	return 0;
}

void run(double k, std::ostream& out)
{
	out.precision(17);
	out << std::fixed;

	out <<
		std::string(91, '=') << std::endl <<
		"k = " << k << std::endl <<
		std::string(91, '=') << std::endl << std::endl;

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
		out << "CGS failure" << std::endl;
	if (!m)
		out << "MGS failure" << std::endl;

	out <<
		"A" << std::endl << a << std::endl << std::endl <<
		"CGS: Q, R, Q*QT - I:" << std::endl <<
		q1 << std::endl << 
		r1 << std::endl << 
		q1 * q1.transpose() - id << std::endl << std::endl <<
		"MGS: Q, R, Q*QT - I:" << std::endl <<
		q2 << std::endl << 
		r2 << std::endl <<
		q2 * q2.transpose() - id << std::endl;

	Vector xc(0), xm(0), b({1.0, 1.0, 1.0, 1.0});
	bool s = solve(a, b, xc, xm);

	if (!s)
		out << "Solve failure" << std::endl;

	out <<
		"A" << std::endl << a << std::endl <<
		"b" << std::endl << b << std::endl << std::endl <<
		"x (CGS)" << std::endl << xc << std::endl << std::endl <<
		"x (MGS)" << std::endl << xm << std::endl << std::endl <<
		"r (CGS) = " << (b - a * xc).norm() << std::endl <<
		"r (MGS) = " << (b - a * xm).norm() << std::endl << std::endl;
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

	q = r = Matrix(m, n);
	Vector v(m), t(m);

	double s;

	for (int i = 0; i < n; ++i)
	{
		t = as.at(i);
		for (int j = 0; j < i; ++j)
		{
			s = as.at(i) * q[j];
			v[j] = s;
			t -= q[j] * s;
		}
		v[i] = t.norm();
		q[i] = t.normalise();
		r[i] = v;
		v = Vector(m);
	}
	
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

	Matrix vs(as);
	q = Matrix(as);
	r = Matrix(m, n);

	double s;

	for (int i = 0; i < n; ++i)
	{
		s = vs[i].norm();
		r[i][i] = s;
		q[i] = vs[i] / s;

		for (int j = i + 1; j < n; ++j)
		{
			s = vs[j] * q[i];
			r[j][i] = s;
			vs[j] -= q[i] * s;
		}
	}

	return true;
}

bool solve(Matrix& a, Vector& b, Vector& xc, Vector& xm)
{
	int n = a.getCols();
	int m = a.getRows();
	if (m != b.getLength())
		return false;	// Incombatible dimensions

	Matrix qc(0, 0), rc(0, 0), qm(0, 0), rm(0, 0);
	std::vector<Vector> as = a.asVectors();
	cgs(as, qc, rc);
	mgs(as, qm, rm);
	Vector vc = qc.transpose() * b;
	Vector vm = qm.transpose() * b;

	xc = xm = Vector(n);
	for (int i = n - 1; i >= 0; --i)
	{
		double s = vc[i];
		for (int j = n - 1; j > i; --j)
			s -= rc[j][i] * xc[j];
		xc[i] = s / rc[i][i];

		s = vm[i];
		for (int j = n - 1; j > i; --j)
			s -= rm[j][i] * xm[j];
		xm[i] = s / rm[i][i];
	}

	return true;
}