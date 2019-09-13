#ifndef STAN_MATH_PRIM_SCAL_PROB_NEG_BINOMIAL_2_LOG_LPMF_HPP
#define STAN_MATH_PRIM_SCAL_PROB_NEG_BINOMIAL_2_LOG_LPMF_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/scal/err/check_consistent_sizes.hpp>
#include <stan/math/prim/scal/err/check_positive_finite.hpp>
#include <stan/math/prim/scal/err/check_nonnegative.hpp>
#include <stan/math/prim/scal/fun/size_zero.hpp>
#include <stan/math/prim/scal/fun/multiply_log.hpp>
#include <stan/math/prim/scal/fun/digamma.hpp>
#include <stan/math/prim/scal/fun/lgamma.hpp>
#include <stan/math/prim/scal/fun/log_sum_exp.hpp>
#include <stan/math/prim/scal/fun/value_of.hpp>
#include <cmath>

namespace stan {
namespace math {

// NegBinomial(n|eta, phi)  [phi > 0;  n >= 0]
template <bool propto, typename T_n, typename T_log_location,
          typename T_precision>
inline auto neg_binomial_2_log_lpmf(T_n&& n, T_log_location&& eta,
                                    T_precision&& phi) {
  using T_partials = partials_return_t<T_n, T_log_location, T_precision>;
  T_partials logp(0.0);

  using std::exp;
  using std::log;

  static const char* function = "neg_binomial_2_log_lpmf";
  check_nonnegative(function, "Failures variable", n);
  check_finite(function, "Log location parameter", eta);
  check_positive_finite(function, "Precision parameter", phi);
  check_consistent_sizes(function, "Failures variable", n,
                         "Log location parameter", eta, "Precision parameter",
                         phi);

  const scalar_seq_view<T_n> n_vec(n);
  const scalar_seq_view<T_log_location> eta_vec(eta);
  const scalar_seq_view<T_precision> phi_vec(phi);
  const size_t size = max_size(n, eta, phi);
  const size_t len_ep = max_size(eta, phi);
  const size_t len_np = max_size(n, phi);

  operands_and_partials<T_log_location, T_precision> ops_partials(eta, phi);
  if (!include_summand<propto, T_log_location, T_precision>::value) {
    return ops_partials.build(logp);
  } else if (size_zero(n, eta, phi)) {
    return ops_partials.build(logp);
  }

  VectorBuilder<true, T_partials, T_log_location> eta__(length(eta));
  for (size_t i = 0, size = length(eta); i < size; ++i) {
    eta__[i] = value_of(eta_vec[i]);
  }

  VectorBuilder<true, T_partials, T_precision> phi__(length(phi));
  for (size_t i = 0, size = length(phi); i < size; ++i) {
    phi__[i] = value_of(phi_vec[i]);
  }

  VectorBuilder<true, T_partials, T_precision> log_phi(length(phi));
  for (size_t i = 0, size = length(phi); i < size; ++i) {
    log_phi[i] = log(phi__[i]);
  }

  VectorBuilder<true, T_partials, T_log_location, T_precision>
      logsumexp_eta_logphi(len_ep);
  for (size_t i = 0; i < len_ep; ++i) {
    logsumexp_eta_logphi[i] = log_sum_exp(eta__[i], log_phi[i]);
  }

  VectorBuilder<true, T_partials, T_n, T_precision> n_plus_phi(len_np);
  for (size_t i = 0; i < len_np; ++i) {
    n_plus_phi[i] = n_vec[i] + phi__[i];
  }

  for (size_t i = 0; i < size; i++) {
    if (include_summand<propto>::value) {
      logp -= lgamma(n_vec[i] + 1.0);
    }
    if (include_summand<propto, T_precision>::value) {
      logp += multiply_log(phi__[i], phi__[i]) - lgamma(phi__[i]);
    }
    if (include_summand<propto, T_log_location, T_precision>::value) {
      logp -= (n_plus_phi[i]) * logsumexp_eta_logphi[i];
    }
    if (include_summand<propto, T_log_location>::value) {
      logp += n_vec[i] * eta__[i];
    }
    if (include_summand<propto, T_precision>::value) {
      logp += lgamma(n_plus_phi[i]);
    }

    if (!is_constant_all<T_log_location>::value) {
      ops_partials.edge1_.partials_[i]
          += n_vec[i] - n_plus_phi[i] / (phi__[i] / exp(eta__[i]) + 1.0);
    }
    if (!is_constant_all<T_precision>::value) {
      ops_partials.edge2_.partials_[i]
          += 1.0 - n_plus_phi[i] / (exp(eta__[i]) + phi__[i]) + log_phi[i]
             - logsumexp_eta_logphi[i] - digamma(phi__[i])
             + digamma(n_plus_phi[i]);
    }
  }
  return ops_partials.build(logp);
}

template <typename T_n, typename T_log_location, typename T_precision>
inline auto neg_binomial_2_log_lpmf(T_n&& n, T_log_location&& eta,
                                    T_precision&& phi) {
  return neg_binomial_2_log_lpmf<false>(n, eta, phi);
}
}  // namespace math
}  // namespace stan
#endif
