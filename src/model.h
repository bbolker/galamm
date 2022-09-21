#ifndef MODEL_H
#define MODEL_H

#include <RcppEigen.h>
#include <autodiff/forward/dual.hpp>
#include <autodiff/forward/dual/eigen.hpp>

template <typename T>
using Vdual = Eigen::Matrix<T, Eigen::Dynamic, 1>;
template <typename T>
using Ddual = Eigen::DiagonalMatrix<T, Eigen::Dynamic>;

template <typename T>
struct Model {
  Model(int maxit_conditional_modes, double epsilon_u) :
  maxit_conditional_modes { maxit_conditional_modes },
  epsilon_u { epsilon_u }{}

  int maxit_conditional_modes;
  double epsilon_u;




  virtual T cumulant(const T& linpred, const T& trials) = 0;
  virtual T constfun(const T& y, const T& phi, const T k) = 0;

  virtual Vdual<T> meanfun(const Vdual<T>& linpred, const Vdual<T>& trials) = 0;

  virtual Vdual<T> get_V(const Vdual<T>& linpred, const Vdual<T>& trials) = 0;

  virtual T get_phi_component(const Vdual<T>& linpred, const Vdual<T>& u, const Vdual<T>& y) = 0;
};

template <typename T>
struct Binomial : Model<T> {

  using Model<T>::Model;

  T cumulant(const T& linpred, const T& trials) override {
    return log(1 + exp(linpred)) * trials;
  };
  T constfun(const T& y, const T& phi, const T k) override {
    return k;
  };

  Vdual<T> meanfun(const Vdual<T>& linpred,
                                   const Vdual<T>& trials) override {
    return linpred.array().exp() / (1 + linpred.array().exp()) * trials.array();
  };

  // Binomial variance function
  // meanfun() includes the number of trials, and hence returns the number of
  // expected successes, and not the expected proportion of successes.
  // Thus, mu(eta) = N * exp(eta) / (1 + exp(eta)) and
  // m'(eta) = d''(eta) = mu * (N - mu) / N.
  Vdual<T> get_V(
      const Vdual<T>& linpred,
      const Vdual<T>& trials) override {

        return meanfun(linpred, trials).array() / trials.array() *
            (trials.array() - meanfun(linpred, trials).array());
  };

  T get_phi_component(const Vdual<T>& linpred,
            const Vdual<T>& u,
            const Vdual<T>& y) override {
              return 1;
  };
};

template <typename T>
struct Gaussian : Model<T> {

  using Model<T>::Model;

  T cumulant(const T& linpred, const T& trials) override {
    return pow(linpred, 2) / 2;
  };
  T constfun(const T& y, const T& phi, const T k) override {
    return -.5 * (pow(y, 2) / phi + log(2 * M_PI * phi));
  };
  Vdual<T> meanfun(const Vdual<T>& linpred, const Vdual<T>& trials) override {
    return linpred;
  };

  // How to update diagonal variance matrix is model dependent
  Vdual<T> get_V(
      const Vdual<T>& linpred, const Vdual<T>& trials) override {
        int n = linpred.size();
        Vdual<T> ret;
        ret.setConstant(n, 1);
        return ret;

  };

  T get_phi_component(
      const Vdual<T>& linpred, const Vdual<T>& u, const Vdual<T>& y) override {
        int n = y.size();
        return ((y - linpred).squaredNorm() + u.squaredNorm()) / n;
  };

};

template <typename T>
struct Poisson : Model<T> {

  using Model<T>::Model;

  T cumulant(const T& linpred, const T& trials) override {
    return exp(linpred);
  };
  T constfun(const T& y, const T& phi, const T k) override {
    return k;
  };
  Vdual<T> meanfun(const Vdual<T>& linpred, const Vdual<T>& trials) override {
    return linpred.array().exp();
  };

  // How to update diagonal variance matrix is model dependent
  Vdual<T> get_V(
      const Vdual<T>& linpred,
      const Vdual<T>& trials) override {
        return meanfun(linpred, trials).array();
  };

  T get_phi_component(const Vdual<T>& linpred, const Vdual<T>& u, const Vdual<T>& y) override {
    return 1;
  };

};


#endif

