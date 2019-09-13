#ifndef STAN_MATH_PRIM_SCAL_PROB_LOGISTIC_LCDF_HPP
#define STAN_MATH_PRIM_SCAL_PROB_LOGISTIC_LCDF_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/scal/err/check_consistent_sizes.hpp>
#include <stan/math/prim/scal/err/check_finite.hpp>
#include <stan/math/prim/scal/err/check_not_nan.hpp>
#include <stan/math/prim/scal/err/check_positive_finite.hpp>
#include <stan/math/prim/scal/fun/size_zero.hpp>
#include <stan/math/prim/scal/fun/value_of.hpp>
#include <stan/math/prim/scal/prob/logistic_log.hpp>
#include <cmath>
#include <limits>

namespace stan {
namespace math {

template <typename T_y, typename T_loc, typename T_scale>
inline auto logistic_lcdf(T_y&& y, T_loc&& mu, T_scale&& sigma) {
  using T_partials = partials_return_t<T_y, T_loc, T_scale>;
  T_partials P(0.0);

  using std::exp;
  using std::log;

  static const char* function = "logistic_lcdf";
  check_not_nan(function, "Random variable", y);
  check_finite(function, "Location parameter", mu);
  check_positive_finite(function, "Scale parameter", sigma);
  check_consistent_sizes(function, "Random variable", y, "Location parameter",
                         mu, "Scale parameter", sigma);

  const scalar_seq_view<T_y> y_vec(y);
  const scalar_seq_view<T_loc> mu_vec(mu);
  const scalar_seq_view<T_scale> sigma_vec(sigma);
  const size_t N = max_size(y, mu, sigma);

  operands_and_partials<T_y, T_loc, T_scale> ops_partials(y, mu, sigma);
  if (size_zero(y, mu, sigma)) {
    return ops_partials.build(P);
  }

  // Explicit return for extreme values
  // The gradients are technically ill-defined, but treated as zero
  for (size_t i = 0; i < stan::length(y); i++) {
    if (value_of(y_vec[i]) == -std::numeric_limits<double>::infinity()) {
      return ops_partials.build(-std::numeric_limits<double>::infinity());
    }
  }

  for (size_t n = 0; n < N; n++) {
    // Explicit results for extreme values
    // The gradients are technically ill-defined, but treated as zero
    if (value_of(y_vec[n]) == std::numeric_limits<double>::infinity()) {
      continue;
    }

    const T_partials y_dbl = value_of(y_vec[n]);
    const T_partials mu_dbl = value_of(mu_vec[n]);
    const T_partials sigma_dbl = value_of(sigma_vec[n]);
    const T_partials sigma_inv_vec = 1.0 / value_of(sigma_vec[n]);

    const T_partials Pn = 1.0 / (1.0 + exp(-(y_dbl - mu_dbl) * sigma_inv_vec));
    P += log(Pn);

    if (!is_constant_all<T_y>::value) {
      ops_partials.edge1_.partials_[n]
          += exp(logistic_log(y_dbl, mu_dbl, sigma_dbl)) / Pn;
    }
    if (!is_constant_all<T_loc>::value) {
      ops_partials.edge2_.partials_[n]
          += -exp(logistic_log(y_dbl, mu_dbl, sigma_dbl)) / Pn;
    }
    if (!is_constant_all<T_scale>::value) {
      ops_partials.edge3_.partials_[n]
          += -(y_dbl - mu_dbl) * sigma_inv_vec
             * exp(logistic_log(y_dbl, mu_dbl, sigma_dbl)) / Pn;
    }
  }
  return ops_partials.build(P);
}

}  // namespace math
}  // namespace stan
#endif
