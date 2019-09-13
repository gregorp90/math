#ifndef STAN_MATH_PRIM_SCAL_PROB_INV_CHI_SQUARE_CDF_LOG_HPP
#define STAN_MATH_PRIM_SCAL_PROB_INV_CHI_SQUARE_CDF_LOG_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/scal/prob/inv_chi_square_lcdf.hpp>

namespace stan {
namespace math {

/**
 * @deprecated use <code>inv_chi_square_lcdf</code>
 */
template <typename T_y, typename T_dof>
inline auto inv_chi_square_cdf_log(T_y&& y, T_dof&& nu) {
  return inv_chi_square_lcdf(y, nu);
}

}  // namespace math
}  // namespace stan
#endif
