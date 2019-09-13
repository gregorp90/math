#ifndef STAN_MATH_PRIM_SCAL_PROB_LOGISTIC_LOG_HPP
#define STAN_MATH_PRIM_SCAL_PROB_LOGISTIC_LOG_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/scal/prob/logistic_lpdf.hpp>

namespace stan {
namespace math {

/**
 * @deprecated use <code>logistic_lpdf</code>
 */
template <bool propto, typename T_y, typename T_loc, typename T_scale>
inline auto logistic_log(T_y&& y, T_loc&& mu, T_scale&& sigma) {
  return logistic_lpdf<propto>(y, mu, sigma);
}

/**
 * @deprecated use <code>logistic_lpdf</code>
 */
template <typename T_y, typename T_loc, typename T_scale>
inline auto logistic_log(T_y&& y, T_loc&& mu, T_scale&& sigma) {
  return logistic_lpdf(y, mu, sigma);
}

}  // namespace math
}  // namespace stan
#endif
