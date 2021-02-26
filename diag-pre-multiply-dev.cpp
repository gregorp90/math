#include <cmath>
#include <stan/math.hpp>
#include <iostream>

int main() {
	Eigen::Matrix<double, 1, 2> V1;
	Eigen::Matrix<double, 2, 2> M2;
	V1 << 2, 3;
	M2 << 3, 3, 1, 1;
	std::cout << V1 << std::endl << std::endl;
	std::cout << M2 << std::endl << std::endl;
	Eigen::Matrix<double, 2, 2> M3;
	M3 = stan::math::diag_pre_multiply(V1, M2);
	std::cout << M3 << std::endl;
	Eigen::Matrix<double, 2, 2> M4;
	M4 = V1.asDiagonal();
	std::cout << M4 << std::endl;
	Eigen::Matrix<double, 2, 2> M5;
	M5 = V1.asDiagonal() * M2;
	std::cout << M5 << std::endl;
	
	Eigen::Matrix<stan::math::var, 1, 2> V2;
	Eigen::Matrix<stan::math::var, 2, 2> M_var;
	V2 << 2, 3;
	M_var = stan::math::diag_pre_multiply(V2, M2);
	
	stan::math::var lp2 = 0;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			lp2 += M_var(i,j);
		}
	}
	lp2.grad();
	std::cout << V2.adj() << std::endl;
	
	
	/*Eigen::Matrix<double, 2, 2> M4;
	M4 = stan::math::elt_multiply_temp(M1, M2);
	std::cout << M4 << std::endl << std::endl;
	
	Eigen::Matrix<stan::math::var, 2, 2> M5;
	Eigen::Matrix<stan::math::var, 2, 2> M6;
	M5 << 1, 4, 2, 1;
	// M6 = stan::math::elt_multiply_(M1, 4);
	M6 = stan::math::elt_multiply_temp(M1, M5);
	std::cout << M6 << std::endl << std::endl;*/
	
	return 0;
}