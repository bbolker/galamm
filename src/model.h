#ifndef MODEL_H
#define MODEL_H

#include <RcppEigen.h>
#include <unsupported/Eigen/SpecialFunctions>
#include <autodiff/forward/dual.hpp>
#include <autodiff/forward/dual/eigen.hpp>


namespace GALAMM {

  struct Model{

    // Constructor, converting objects to autodiff
    Model(
      const Eigen::VectorXd& y0,
      const Eigen::VectorXd& trials0,
      const Eigen::MatrixXd& X0,
      const Eigen::MappedSparseMatrix<double>& Zt0,
      const Eigen::MappedSparseMatrix<double>& Lambdat0,
      const Eigen::VectorXd& beta0,
      const Eigen::VectorXd& theta0,
      const Eigen::VectorXi& theta_mapping0,
      const Eigen::VectorXd& lambda0,
      const Eigen::VectorXi& lambda_mapping_X0,
      const Eigen::VectorXi& lambda_mapping_Zt0,
      const int maxit_conditional_modes0
    );

    // Compute posterior modes of random effects
    void get_conditional_modes(
        Eigen::SimplicialLLT<Eigen::SparseMatrix<autodiff::dual1st> >& solver
    );
    int maxit_conditional_modes;

    // Exponent in the Laplace approximation
    autodiff::dual1st exponent_g();

    // Hessian matrix used in penalized iteratively reweighted least squares
    void update_inner_hessian();
    Eigen::SparseMatrix<autodiff::dual1st>& get_inner_hessian();
    bool inner_hessian_needs_update{true};
    Eigen::SparseMatrix<autodiff::dual1st> inner_hessian;

    // Lower Cholesky factor of scaled covariance matrix
    void update_Lambdat();
    Eigen::SparseMatrix<autodiff::dual1st>& get_Lambdat();
    bool Lambdat_needs_update{true};
    Eigen::SparseMatrix<autodiff::dual1st> Lambdat;

    // Scale parameter
    virtual void update_phi() = 0;
    autodiff::dual1st phi;
    autodiff::dual1st& get_phi();
    bool phi_needs_update{true};

    // Diagonal variance matrix, common parts
    virtual void update_V() = 0;
    Eigen::DiagonalMatrix<autodiff::dual1st, Eigen::Dynamic> V;
    Eigen::DiagonalMatrix<autodiff::dual1st, Eigen::Dynamic>& get_V();
    bool V_needs_update{true};

    // Linear predictor
    virtual void update_linpred() = 0;
    autodiff::VectorXdual1st& get_linpred();
    bool linpred_needs_update{true};
    autodiff::VectorXdual1st linpred;

    // GLM functions defined in derived classes
    virtual autodiff::dual1st cumulant() = 0;
    virtual autodiff::dual1st constfun() = 0;
    virtual autodiff::VectorXdual1st meanfun() = 0;

    // Regression coefficients
    void update_u(const autodiff::VectorXdual1st& delta_u, double alpha_bar);

    Eigen::VectorXd y;
    autodiff::MatrixXdual1st X;
    Eigen::SparseMatrix<autodiff::dual1st> Zt;

    const Eigen::VectorXi theta_mapping;
    autodiff::VectorXdual1st theta;
    autodiff::VectorXdual1st beta;
    autodiff::VectorXdual1st u;
    Eigen::VectorXd trials;
    autodiff::VectorXdual1st lambda;
    const Eigen::VectorXi lambda_mapping_X;
    const Eigen::VectorXi lambda_mapping_Zt;

    int n;
    int p;
    int q;

  };

  struct Gaussian : Model {

    // Inherit base class constructor
    using Model::Model;

    autodiff::dual1st cumulant() override;
    autodiff::dual1st constfun() override;
    autodiff::VectorXdual1st meanfun() override;
    void update_linpred() override;

    // How to update diagonal variance matrix is model dependent
    void update_V() override;
    void update_phi() override;

  };

  struct Binomial : Model {

    // Inherit base class constructor
    using Model::Model;

    autodiff::dual1st cumulant() override;
    autodiff::dual1st constfun() override;
    autodiff::VectorXdual1st meanfun() override;
    void update_linpred() override;

    // How to update diagonal variance matrix is model dependent
    void update_V() override;
    void update_phi() override;

  };


  struct Poisson : Model {

    // Inherit base class constructor
    using Model::Model;

    autodiff::dual1st cumulant() override;
    autodiff::dual1st constfun() override;
    autodiff::VectorXdual1st meanfun() override;
    void update_linpred() override;

    // How to update diagonal variance matrix is model dependent
    void update_V() override;
    void update_phi() override;

  };
}

#endif
