//
// Created by Owner on 15/6/2020.
//

#ifndef HESTON_PRICING_ANALYTICAL_HESTON_HPP
#define HESTON_PRICING_ANALYTICAL_HESTON_HPP
#include <iostream>
#include <cmath>
#include <complex>
#include <algorithm>
#include <string>

double Heston_integrand(std::complex<double> K, double X, double V0,
                        double tau, double thet, double kappa, double SigmaV,
                        double rho, double gamma);

double HestonPrice(double S, double K, double r, double delta,
                   double V0, double tau,
                   double thet, double kappa, double SigmaV, double rho,
                   double gamma, std::string optType);

double HestonDelta(double S, double K, double r, double delta,
                   double V0, double tau,
                   double thet, double kappa, double SigmaV, double rho,
                   double gamma, std::string optType);

double HestonGamma(double S, double K, double r, double delta,
                   double V0, double tau,
                   double thet, double kappa, double SigmaV, double rho,
                   double gamma, std::string optType);

double HestonRho(double S, double K, double r, double delta,
                 double V0, double tau,
                 double thet, double kappa, double SigmaV, double rho,
                 double gamma, std::string optType);

double HestonVega(double S, double K, double r, double delta,
                  double V0, double tau,
                  double thet, double kappa, double SigmaV, double rho,
                  double gamma, std::string optType);

double HestonTheta(double S, double K, double r, double delta,
                   double V0, double tau,
                   double thet, double kappa, double SigmaV, double rho,
                   double gamma, std::string optType);


#endif //HESTON_PRICING_ANALYTICAL_HESTON_HPP
