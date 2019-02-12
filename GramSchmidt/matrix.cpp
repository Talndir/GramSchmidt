#include "matrix.h"

#include <string>

Matrix::Matrix(int m, int n)
{
	this->m = m;
	this->n = n;
	this->matrix = std::vector<Vector>(m, Vector(n));
}

Matrix::Matrix(std::vector<Vector>& vs)
{
	n = vs.size();
	if (n)
		m = vs.at(0).getLength();
	else
	{
		matrix = std::vector<Vector>(0, Vector(0));
		m = 0;
	}

	for (int i = 0; i < n; ++i)
	{
		if (vs.at(i).getLength() != m)
		{
			matrix = std::vector<Vector>(0, Vector(0));
			m = n = 0;
			return;
		}

		matrix.push_back(vs.at(i));
	}
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
	if (m != vec.getLength())
		return Vector(0);

	Vector r(m);
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

Matrix Matrix::transpose() const
{
	std::vector<double> v;
	std::vector<Vector> vs;

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
			v.push_back((*this)[j][i]);
		vs.push_back(v);
		v.clear();
	}

	return Matrix(vs);
}

std::ostream& operator<<(std::ostream &out, const Matrix &mat)
{
	Matrix m = mat.transpose();
	for (int i = 0; i < m.getCols(); ++i)
		out << mat[i] << std::endl;
	return out;
}