//#ifndef STAN_MATH_REV_FUN_ELT_MULTIPLY_HPP
//#define STAN_MATH_REV_FUN_ELT_MULTIPLY_HPP

#include <stan/math/prim/fun/Eigen.hpp>
#include <iostream>
#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/err.hpp>
#include <stan/math/prim/fun/eval.hpp>
#include <stan/math/rev/core.hpp>
#include <stan/math/rev/fun/multiply.hpp>

//namespace stan {
//namespace math {

/**
 * Return the elementwise multiplication of the specified
 * matrices.
 *
 * @tparam Mat1 type of the first matrix or expression
 * @tparam Mat2 type of the second matrix or expression
 *
 * @param m1 First matrix or expression
 * @param m2 Second matrix or expression
 * @return Elementwise product of matrices.
 */
template <typename Mat1, typename Mat2,
          require_all_matrix_t<Mat1, Mat2>* = nullptr> /*,
          require_any_rev_matrix_t<Mat1, Mat2>* = nullptr> */
auto elt_multiply2(const Mat1& m1, const Mat2& m2) {
  // check_matching_dims("elt_multiply", "m1", m1, "m2", m2);
	return m1.cwiseProduct(m2);
}

//}  // namespace math
//}  // namespace stan

//#endif

int main() {
	Eigen::Matrix<double, 2, 2> M1;
	Eigen::Matrix<double, 2, 2> M2;
	M1 << 2, 3, 4, 5;
	M2 << 3, 3, 1, 1;
	std::cout << M1 << std::endl << std::endl;
	std::cout << M2 << std::endl << std::endl;
	Eigen::Matrix<double, 2, 2> M3;
	M3 = elt_multiply2(M1, M2);
	std::cout << M3 << std::endl;
	return (0);
}