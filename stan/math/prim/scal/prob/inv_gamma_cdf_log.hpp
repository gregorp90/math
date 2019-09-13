#ifndef STAN_MATH_PRIM_SCAL_PROB_INV_GAMMA_CDF_LOG_HPP
#define STAN_MATH_PRIM_SCAL_PROB_INV_GAMMA_CDF_LOG_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/scal/prob/inv_gamma_lcdf.hpp>

namespace stan {
namespace math {

/**
 * @deprecated use <code>inv_gamma_lcdf</code>
 */
template <typename T_y, typename T_shape, typename T_scale>
inline auto inv_gamma_cdf_log(T_y&& y, T_shape&& alpha,
                              T_scale&& beta) {
  return inv_gamma_lcdf(y, alpha, beta);
}

}  // namespace math
}  // namespace stan
#endif
