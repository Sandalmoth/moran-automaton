#ifndef __MULTINOMIAL_H__
#define __MULTINOMIAL_H__


#include <random>
#include <cmath>
#include <vector>
#include <iostream>
#include <numeric>


/*
 * IMPORTANT: This class and function could fail to perform when normalized, as std::binomial_distribution fails in some implementations if p > 1. TODO: fix this if I need it... 
 *
 * This is basically a straight reimplementation of the gsl multinomial function.
 * For consistency I wanted a multinomial generator that used the std::random engines and std containers.
 */


template <typename ret, typename Eng>
std::vector<ret> multinomial(Eng &eng, int N, const std::vector<double> &p) {
	double norm  = std::accumulate(p.begin(), p.end(), 0.0);
	double sum_p = 0.0;
	int    sum_n = 0;

	int K = p.size();
	std::vector<ret> n(K, 0);

	for (int i = 0; i < K; ++i) {
		if (p[i] > 0.0) {
			n[i] = std::binomial_distribution<int>(N - sum_n, p[i] / (norm - sum_p))(eng);
		}
		sum_p += p[i];
		sum_n += n[i];
	}

	return n;
}


// This class behaves like a std::random distribution (lacking some functionality)
template <typename T>
class multinomial_distribution {
public:
	multinomial_distribution(int N, std::vector<double> p, bool normalize = true): N(N), p(p) {
		if (normalize) {
			norm  = std::accumulate(p.begin(), p.end(), 0.0);
		} else {
			norm = 1.0;
		}
	}

	template <typename E>
	std::vector<T> operator()(E e) {
		double sum_p = 0.0;
		int    sum_n = 0;

		int K = p.size();
		std::vector<T> n(K, 0);

		for (int i = 0; i < K; ++i) {
			if (p[i] > 0.0) {
				n[i] = std::binomial_distribution<int>(N - sum_n, p[i] / (norm - sum_p))(e);
			}
			sum_p += p[i];
			sum_n += n[i];
		}

		return n;
	}

	template <typename E>
	std::vector<T> operator()(int tN, E e) {
		double sum_p = 0.0;
		int    sum_n = 0;

		int K = p.size();
		std::vector<T> n(K, 0);

		for (int i = 0; i < K; ++i) {
			if (p[i] > 0.0) {
				n[i] = std::binomial_distribution<int>(tN - sum_n, p[i] / (norm - sum_p))(e);
				// std::cout << i << '\t' << tN - sum_n << '\t' << p[i] / (norm - sum_p) << std::endl;
			}
			sum_p += p[i];
			sum_n += n[i];
		}

		return n;
	}

	void print() {
		std::cout << "multinomial_distribution: " << N << ' ' << norm << "\n\t";
		for (auto x: p) {
			std::cout << x << ' ';
		}
		std::cout << "\n\t" << std::accumulate(p.begin(), p.end(), 0.0) << std::endl;
	}

private:
	int N;
	std::vector<double> p;
	double norm;

};


#endif