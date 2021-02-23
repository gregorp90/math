#include <cmath>
#include <stan/math.hpp>
// #include <iostream>

int main() {
	Eigen::Matrix<double, 2, 2> M1;
	Eigen::Matrix<double, 2, 2> M2;
	M1 << 2, 3, 4, 5;
	M2 << 3, 3, 1, 1;
	std::cout << M1 << std::endl << std::endl;
	std::cout << M2 << std::endl << std::endl;
	Eigen::Matrix<double, 2, 2> M3;
	M3 = stan::math::elt_multiply(M1, M2);
	std::cout << M3 << std::endl;
	Eigen::Matrix<double, 2, 2> M4;
	M4 = stan::math::elt_multiply_temp(M1, M2);
	std::cout << M4 << std::endl << std::endl;
	
	Eigen::Matrix<stan::math::var, 2, 2> M5;
	Eigen::Matrix<stan::math::var, 2, 2> M6;
	M5 << 1, 4, 2, 1;
	// M6 = stan::math::elt_multiply_(M1, 4);
	M6 = stan::math::elt_multiply_temp(M1, M5);
	std::cout << M6 << std::endl << std::endl;

	return 0;
}