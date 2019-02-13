#include "vector.h"

#include <string>
#include <iomanip>
#include <sstream>

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

double Vector::operator*(const Vector& v) const
{
	if (v.getLength() != m)
		return 0.0;

	double r = 0.0;
	for (int i = 0; i < m; ++i)
		r += (*this)[i] * v[i];

	return r;
}

Vector Vector::operator-(const Vector & v) const
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

Vector Vector::operator*(const double & c) const
{
	Vector r(m);
	for (int i = 0; i < m; ++i)
		r[i] = (*this)[i] * c;

	return r;
}

Vector Vector::operator/(const double & c) const
{
	Vector r(m);
	for (int i = 0; i < m; ++i)
		r[i] = (*this)[i] / c;

	return r;
}

int Vector::getLength() const
{
	return m;
}

double Vector::norm() const
{
	return sqrt((*this) * (*this));
}

Vector Vector::normalise() const
{
	Vector v(m);
	double t = norm();

	for (int i = 0; i < vector.size(); ++i)
		v[i] = (*this)[i] / t;

	return v;
}

std::string dtos(double d, int b, int a)
{
	std::string s = "", p, q, x;
	std::ostringstream str;
	if (d < 0)
	{
		s += "-";
		d *= -1;
	}
	else
		s += " ";

	str << std::setprecision(a + 2) << std::fixed << d;

	x = str.str();
	str.str("");

	size_t t = x.find('.');
	if (t == std::string::npos)
	{
		x += ".0";
		t = x.length() - 2;
	}

	p = x.substr(0, t);
	q = x.substr(t, std::string::npos);
	// For some reason, VS2017 doesn't compile this correctly unless
	// b - t is precomputed into a variable (!?)
	int k = b - t;
	if (k > 0)
		str << std::string(k, '0');
	str << p << q << std::string(a, '0');
	s += str.str();
	return s.substr(0, a + b + 2);

}

std::ostream& operator<<(std::ostream & out, const Vector& vec)
{
	for (int i = 0; i < vec.getLength(); ++i)
		out << dtos(vec[i], 3, 17) << " ";

	return out;
}