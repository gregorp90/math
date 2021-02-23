#include <iostream>
#include <Eigen/Dense>
#include <stan-math>
#include <test/unit/math/test_ad.hpp>

 
using Eigen::MatrixXd;
 
int main()
{
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << m << std::endl;
	MatrixXd m2(2,2);
	m2(0,0) = 1;
	m2(1,0) = 2;
	m2(1,1) = 1;
	m2(0,1) = 0;
	std::cout << m2 << std::endl;
	MatrixXd m3(2,2);
	m3 << 1, 2, 4, 5;
	std::cout << m3 << std::endl;
	
	MatrixXd m4(4, 4);
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      m4(i, j) = (i + 2) * (j + 1);
	std::cout << m4 << std::endl;
	
	MatrixXd m_sym_ref(4,4);
	m_sym_ref << 2, 4, 6, 8,
							 4, 6, 9, 12,
							 6, 9, 12, 16,
							 8, 12, 16, 20;
	std::cout << m_sym_ref << std::endl;
	
	// stan::test::expect_ad();
}
