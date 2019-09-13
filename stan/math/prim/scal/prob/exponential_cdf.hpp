#ifndef STAN_MATH_PRIM_SCAL_PROB_EXPONENTIAL_CDF_HPP
#define STAN_MATH_PRIM_SCAL_PROB_EXPONENTIAL_CDF_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/scal/err/check_nonnegative.hpp>
#include <stan/math/prim/scal/err/check_not_nan.hpp>
#include <stan/math/prim/scal/err/check_positive_finite.hpp>
#include <stan/math/prim/scal/fun/size_zero.hpp>
#include <stan/math/prim/scal/fun/value_of.hpp>
#include <cmath>

namespace stan {
namespace math {

/**
 * Calculates the exponential cumulative distribution function for
 * the given y and beta.
 *
 * Inverse scale parameter must be greater than 0.
 * y must be greater than or equal to 0.
 *
 * @param y A scalar variable.
 * @param beta Inverse scale parameter.
 * @tparam T_y Type of scalar.
 * @tparam T_inv_scale Type of inverse scale.
 */
template <typename T_y, typename T_inv_scale>
inline auto exponential_cdf(T_y&& y, T_inv_scale&& beta) {
  using T_partials = partials_return_t<T_y, T_inv_scale>;
  T_partials cdf(1.0);

  using std::exp;

  static const char* function = "exponential_cdf";
  check_not_nan(function, "Random variable", y);
  check_nonnegative(function, "Random variable", y);
  check_positive_finite(function, "Inverse scale parameter", beta);

  const scalar_seq_view<T_y> y_vec(y);
  const scalar_seq_view<T_inv_scale> beta_vec(beta);
  const size_t N = max_size(y, beta);
  operands_and_partials<T_y, T_inv_scale> ops_partials(y, beta);
  if (size_zero(y, beta)) {
    return ops_partials.build(T_partials(0.0));
  }

  for (size_t n = 0; n < N; n++) {
    const T_partials beta_dbl = value_of(beta_vec[n]);
    const T_partials y_dbl = value_of(y_vec[n]);
    const T_partials one_m_exp = 1.0 - exp(-beta_dbl * y_dbl);
    cdf *= one_m_exp;
  }

  for (size_t n = 0; n < N; n++) {
    const T_partials beta_dbl = value_of(beta_vec[n]);
    const T_partials y_dbl = value_of(y_vec[n]);
    const T_partials one_m_exp = 1.0 - exp(-beta_dbl * y_dbl);

    T_partials rep_deriv = exp(-beta_dbl * y_dbl) / one_m_exp;
    if (!is_constant_all<T_y>::value) {
      ops_partials.edge1_.partials_[n] += rep_deriv * beta_dbl * cdf;
    }
    if (!is_constant_all<T_inv_scale>::value) {
      ops_partials.edge2_.partials_[n] += rep_deriv * y_dbl * cdf;
    }
  }
  return ops_partials.build(cdf);
}

}  // namespace math
}  // namespace stan
#endif
