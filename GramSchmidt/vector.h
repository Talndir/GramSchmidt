#pragma once

#include <vector>

class Vector
{
public:
	Vector(int m);
	Vector(std::vector<double> v);
	double operator[](const int k) const;
	double& operator[](const int k);
	double operator*(const Vector& v) const;
	Vector operator-(const Vector& v) const;
	Vector& operator-=(const Vector& v);
	Vector operator*(const double& c) const;
	Vector operator/(const double& c) const;
	int getLength() const;
	double norm() const;
	Vector normalise() const;

	friend std::ostream& operator<<(std::ostream &out, const Vector &vec);

private:
	int m;
	std::vector<double> vector;
};