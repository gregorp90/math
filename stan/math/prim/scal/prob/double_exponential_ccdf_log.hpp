#ifndef STAN_MATH_PRIM_SCAL_PROB_DOUBLE_EXPONENTIAL_CCDF_LOG_HPP
#define STAN_MATH_PRIM_SCAL_PROB_DOUBLE_EXPONENTIAL_CCDF_LOG_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/scal/prob/double_exponential_lccdf.hpp>

namespace stan {
namespace math {

/**
 * @deprecated use <code>double_exponential_lccdf</code>
 */
template <typename T_y, typename T_loc, typename T_scale>
inline auto double_exponential_ccdf_log(T_y&& y, T_loc&& mu,
                                        T_scale&& sigma) {
  return double_exponential_lccdf(y, mu, sigma);
}

}  // namespace math
}  // namespace stan
#endif
