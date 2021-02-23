#include <cmath>
#include <stan/math.hpp>

#include <boost/math/tools/promotion.hpp>

template <typename T1, typename T2, typename T3>
inline typename boost::math::tools::promote_args<T1, T2, T3>::type normal_log2(const T1& y, const T2& mu, const T3& sigma) {
	using std::pow; using std::log;
	return -0.5 * pow((y - mu) / sigma, 2.0)
		- log(sigma)
		- 0.5 * log(2 * stan::math::pi());
}

int main() {
	using std::pow;
	double y = 1.3;
	stan::math::var mu = 0.5, sigma = 1.2;
	stan::math::var lp = 0;
	lp -= 0.5 * log(2 * stan::math::pi());
	lp -= log(sigma);
	lp -= 0.5 * pow((y - mu) / sigma, 2);
	std::cout << "f(mu, sigma) = " << lp.val() << std::endl;
	lp.grad();
	std::cout << " d.f / d.mu = " << mu.adj()
						<< " d.f / d.sigma = " << sigma.adj() << std::endl;
	stan::math::var lp2;
	lp2 = normal_log2(y, mu, sigma);
	std::cout << lp2.val() << std::endl;
	return 0;
}