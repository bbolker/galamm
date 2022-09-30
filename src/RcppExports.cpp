// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// marginal_likelihood
Rcpp::List marginal_likelihood(const Eigen::Map<Eigen::VectorXd> y, const Eigen::Map<Eigen::VectorXd> trials, const Eigen::Map<Eigen::MatrixXd> X, const Eigen::MappedSparseMatrix<double> Zt, const Eigen::MappedSparseMatrix<double> Lambdat, const Eigen::Map<Eigen::VectorXd> beta, const Eigen::Map<Eigen::VectorXd> theta, const Eigen::Map<Eigen::VectorXi> theta_mapping, const Eigen::Map<Eigen::VectorXd> lambda, const Eigen::Map<Eigen::VectorXi> lambda_mapping_X, const Eigen::Map<Eigen::VectorXi> lambda_mapping_Zt, const Eigen::Map<Eigen::VectorXd> weights, const Eigen::Map<Eigen::VectorXi> weights_mapping, const Rcpp::StringVector family, const Eigen::Map<Eigen::VectorXi> family_mapping, const int maxit_conditional_modes, const bool hessian, double epsilon_u);
RcppExport SEXP _galamm_marginal_likelihood(SEXP ySEXP, SEXP trialsSEXP, SEXP XSEXP, SEXP ZtSEXP, SEXP LambdatSEXP, SEXP betaSEXP, SEXP thetaSEXP, SEXP theta_mappingSEXP, SEXP lambdaSEXP, SEXP lambda_mapping_XSEXP, SEXP lambda_mapping_ZtSEXP, SEXP weightsSEXP, SEXP weights_mappingSEXP, SEXP familySEXP, SEXP family_mappingSEXP, SEXP maxit_conditional_modesSEXP, SEXP hessianSEXP, SEXP epsilon_uSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Eigen::Map<Eigen::VectorXd> >::type y(ySEXP);
    Rcpp::traits::input_parameter< const Eigen::Map<Eigen::VectorXd> >::type trials(trialsSEXP);
    Rcpp::traits::input_parameter< const Eigen::Map<Eigen::MatrixXd> >::type X(XSEXP);
    Rcpp::traits::input_parameter< const Eigen::MappedSparseMatrix<double> >::type Zt(ZtSEXP);
    Rcpp::traits::input_parameter< const Eigen::MappedSparseMatrix<double> >::type Lambdat(LambdatSEXP);
    Rcpp::traits::input_parameter< const Eigen::Map<Eigen::VectorXd> >::type beta(betaSEXP);
    Rcpp::traits::input_parameter< const Eigen::Map<Eigen::VectorXd> >::type theta(thetaSEXP);
    Rcpp::traits::input_parameter< const Eigen::Map<Eigen::VectorXi> >::type theta_mapping(theta_mappingSEXP);
    Rcpp::traits::input_parameter< const Eigen::Map<Eigen::VectorXd> >::type lambda(lambdaSEXP);
    Rcpp::traits::input_parameter< const Eigen::Map<Eigen::VectorXi> >::type lambda_mapping_X(lambda_mapping_XSEXP);
    Rcpp::traits::input_parameter< const Eigen::Map<Eigen::VectorXi> >::type lambda_mapping_Zt(lambda_mapping_ZtSEXP);
    Rcpp::traits::input_parameter< const Eigen::Map<Eigen::VectorXd> >::type weights(weightsSEXP);
    Rcpp::traits::input_parameter< const Eigen::Map<Eigen::VectorXi> >::type weights_mapping(weights_mappingSEXP);
    Rcpp::traits::input_parameter< const Rcpp::StringVector >::type family(familySEXP);
    Rcpp::traits::input_parameter< const Eigen::Map<Eigen::VectorXi> >::type family_mapping(family_mappingSEXP);
    Rcpp::traits::input_parameter< const int >::type maxit_conditional_modes(maxit_conditional_modesSEXP);
    Rcpp::traits::input_parameter< const bool >::type hessian(hessianSEXP);
    Rcpp::traits::input_parameter< double >::type epsilon_u(epsilon_uSEXP);
    rcpp_result_gen = Rcpp::wrap(marginal_likelihood(y, trials, X, Zt, Lambdat, beta, theta, theta_mapping, lambda, lambda_mapping_X, lambda_mapping_Zt, weights, weights_mapping, family, family_mapping, maxit_conditional_modes, hessian, epsilon_u));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_galamm_marginal_likelihood", (DL_FUNC) &_galamm_marginal_likelihood, 18},
    {NULL, NULL, 0}
};

RcppExport void R_init_galamm(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
