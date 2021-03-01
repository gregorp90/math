#include <cmath>
#include <stan/math.hpp>
#include <iostream>

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
	Eigen::Matrix<stan::math::var, 2, 2> M7;

	M5 << 1, 4, 2, 1;
	// M6 = stan::math::elt_multiply_(M1, 4);
	M6 = stan::math::elt_multiply_temp(M1, M5);
	M7 = stan::math::elt_multiply(M1, M5);
	std::cout << M6 << std::endl << std::endl;
	
	// stan::math::var lp;
	// lp = M6(1,1);
	// lp.grad();
	// std::cout << M5.adj() << std::endl;
	
	stan::math::var lp2 = 0;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			lp2 += M6(i,j);
		}
	}
	lp2.grad();
	std::cout << M5.adj() << std::endl;
	// std::cout << M5.adj().coeffRef() << std::endl;
	
	/* stan::math::var lp3 = 0;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			lp3 += M2(i,j);
		}
	}
	lp3.grad();
	std::cout << M2.adj() << std::endl; */ // To ne gre, ker M2 ni tipa var.

	return 0;
}