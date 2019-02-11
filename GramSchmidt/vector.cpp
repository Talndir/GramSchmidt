#include "vector.h"

#include <string>

Vector::Vector(int m) : m(m)
{
	vector = std::vector<double>(m, 0.0);
}

Vector::Vector(std::vector<double> v)
{
	vector = std::vector<double>(v);
	m = v.size();
}

double Vector::operator[](const int k) const
{
	return vector.at(k);
}

double& Vector::operator[](const int k)
{
	return vector.at(k);
}

double Vector::operator*(const Vector& v)
{
	if (v.getLength() != m)
		return 0.0;

	double r = 0.0;
	for (int i = 0; i < m; ++i)
		r += (*this)[i] * v[i];

	return r;
}

Vector Vector::operator-(const Vector & v)
{
	if (v.getLength() != m)
		return Vector(0);

	Vector r(m);
	for (int i = 0; i < m; ++i)
		r[i] = (*this)[i] - v[i];

	return r;
}

Vector& Vector::operator-=(const Vector & v)
{
	if (v.getLength() != m)
	{
		m = 0;
		vector = std::vector<double>(0);
	}

	for (int i = 0; i < m; ++i)
		(*this)[i] -= v[i];

	return *this;
}

Vector Vector::operator*(const double & c)
{
	Vector r(m);
	for (int i = 0; i < m; ++i)
		r[i] = (*this)[i] * c;

	return r;
}

int Vector::getLength() const
{
	return m;
}

Vector Vector::norm()
{
	Vector v(m);
	double t = sqrt((*this) * (*this));

	for (int i = 0; i < vector.size(); ++i)
		v[i] = (*this)[i] / t;

	return v;
}

std::ostream& operator<<(std::ostream & out, const Vector& vec)
{
	for (int i = 0; i < vec.getLength(); ++i)
		out << vec[i] << " ";
	return out;
}