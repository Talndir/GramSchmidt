#pragma once

#include "vector.h"

class Matrix
{
public:
	Matrix(int m, int n);
	Matrix(std::vector<Vector> vs);
	Matrix(std::vector<std::vector<double>> vs);
	Vector operator[](const int k) const;
	Vector& operator[](const int k);
	Vector operator*(Vector& vec);
	int getRows() const;
	int getCols() const;

	friend std::ostream& operator<<(std::ostream &out, const Matrix &mat);

private:
	int m, n;
	std::vector<Vector> matrix;
};