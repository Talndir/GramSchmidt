#include "matrix.h"

#include <string>

Matrix::Matrix(int m, int n)
{
	this->m = m;
	this->n = n;
	this->matrix = std::vector<Vector>(m, Vector(n));
}

Matrix::Matrix(std::vector<Vector> vs)
{
	n = 0;
	if (vs.size())
		n = vs.at(0).getLength();
	else
		matrix = std::vector<Vector>(0, Vector(0));

	for (int i = 0; i < vs.size(); ++i)
	{
		if (vs.at(i).getLength() != n)
		{
			matrix = std::vector<Vector>(0, Vector(0));
			n = m = 0;
			return;
		}

		matrix.push_back(vs.at(i));
	}

	m = vs.size();
}

Vector Matrix::operator[](const int k) const
{
	return matrix[k];
}

Vector& Matrix::operator[](const int k)
{
	return matrix[k];
}

Vector Matrix::operator*(Vector& vec)
{
	if (n != vec.getLength())
		return Vector(0);

	Vector r(n);
	for (int i = 0; i < n; ++i)
		r[i] = vec * matrix[i];

	return r;
}

int Matrix::getRows() const
{
	return m;
}

int Matrix::getCols() const
{
	return n;
}

std::ostream& operator<<(std::ostream &out, const Matrix &mat)
{
	for (int i = 0; i < mat.getRows(); ++i)
		out << mat[i] << std::endl;
	return out;
}