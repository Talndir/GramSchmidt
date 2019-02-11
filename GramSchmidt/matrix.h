#pragma once

#include <vector>

template <typename T>
class Matrix
{
public:
	Matrix(int x, int y);
	T& operator[](const int index);

private:
	std::vector<std::vector<T>> matrix;
};

template<typename T>
inline Matrix<T>::Matrix(int x, int y)
{
}

template<typename T>
inline T & Matrix<T>::operator[](const int index)
{
	return matrix.at(index);
}
