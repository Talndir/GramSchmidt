#pragma once

#include <vector>

class Vector
{
public:
	Vector(int m);
	Vector(std::vector<double> v);
	double operator[](const int k) const;
	double& operator[](const int k);
	double operator*(const Vector& v);
	Vector operator-(const Vector& v);
	Vector& operator-=(const Vector& v);
	Vector operator*(const double& c);
	int getLength() const;
	Vector norm();

	friend std::ostream& operator<<(std::ostream &out, const Vector &vec);

private:
	int m;
	std::vector<double> vector;
};