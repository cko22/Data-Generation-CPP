//
// Created by Owner on 15/6/2020.
//

#include "Heston.hpp"
#include "trapezoidalMethod.hpp"
//This function computes the value of a European option using the
//Heston model for stochastic volatility.
//S: Spot price
//K: Strike price
//r: Risk-free interest rate
//delta: Dividend yield
//V0: Initial volatility
//tau: Time to maturity (years)
//thet: Long-run volatility
//kappa: Mean-reversion rate for volatility
//SigmaV: Volatility of volatility
//rho: Price-volatility correlation
//gamma: Risk-aversion parameter
//optType: Option type (call or put)
#include <iostream>
#include <cmath>
#include <complex>
#include <algorithm>
#include <string>
#include <vector>
double PI = 3.14159265358979323846264338327950288;

//creates the function that will be integrated in the
//computation of the option price.
double Heston_integrand(std::complex<double> K, double X, double V0,
                        double tau, double thet, double kappa, double SigmaV,
                        double rho, double gamma) {

    std::complex<double> thetaadj;
    double omega = kappa*thet;
    double ksi = SigmaV;
    double theta = kappa;
    std::complex<double> t((ksi*ksi)*tau/2.0, 0.0);
    std::complex<double> a((2.0*omega) / (ksi*ksi), 0.0);
    if (gamma == 1.0) {
        thetaadj = std::complex<double>(theta, 0.0);
    } else {
        thetaadj = std::complex<double>((1.0 - gamma) * rho * ksi
                                        + sqrt(theta * theta - gamma * (1.0 - gamma) * ksi * ksi), 0.0);
    }
    std::complex<double> im(0.0, 1.0);
    std::complex<double> re(1.0, 0.0);
    std::complex<double> b = (2.0/(ksi*ksi))*(thetaadj);
    std::complex<double> c = (K*K-im*K)/(ksi*ksi);
    std::complex<double> d = sqrt(b*b + 4.0*c);
    std::complex<double> g = (b+d)/2.0;
    std::complex<double> h = (b+d)/(b-d);
    std::complex<double> f1 = a*(t*g - log((1.0-h*exp(t*d))/(1.0-h)));
    std::complex<double> f2 = g*((1.0-exp(t*d))/(1.0-h*exp(t*d)));
    std::complex<double> H = exp(f1 + f2*V0);
    //function to be integrated
    std::complex<double> integrand = exp(-im*K*X)*(H/(K*K-im*K));
    return real(integrand);
}
double HestonPrice(double S, double K, double r, double delta,
                   double V0, double tau,
                   double thet, double kappa, double SigmaV, double rho,
                   double gamma, std::string optType) {
    double ki = 0.5;
    double price;
    std::complex<double> pass_phi;
    double omega = kappa*thet;
    double ksi = SigmaV;
    double theta = kappa;
    int kmax = ceil(std::max(1000.0, 10.0/sqrt(V0*tau)));
    std::vector<double> int_x(kmax*5);
    std::vector<double> int_y(kmax*5);
    double X = log(S/K) + (r - delta) * tau;
    int count = 0;
//setting up the numerical integration
    for (double phi = 0.000001; phi<kmax; phi += 0.2)
    {
        int_x[count] = phi;
        pass_phi = std::complex<double> (phi, ki);
        int_y[count] = Heston_integrand(pass_phi, X, V0,
                                        tau, thet, kappa, SigmaV, rho, gamma);
        count += 1;
    }
//computing the price
    double callPrice = S*exp(-delta*tau)-(1.0/(PI))*K*
                                         exp(-r*tau)*trapezoidalMethod(int_x, int_y);
    double putPrice = callPrice + K*exp(-r*tau) -
                      S*exp(-delta*tau);
    if (optType == "Call" || optType == "call")
        price = callPrice;
    else
        price = putPrice;
    return price;
}

//Greeks for the Heston model using finite differences
double HestonDelta(double S, double K, double r, double delta,
                   double V0, double tau,
                   double thet, double kappa, double SigmaV, double rho,
                   double gamma, std::string optType) {
    double alpha = 0.0001;
    return (HestonPrice(S+alpha,K,r,delta,V0,tau,thet,kappa,
                        SigmaV,rho,gamma,optType)-HestonPrice(S,K,r,delta,V0,
                                                              tau,thet,kappa,SigmaV,rho,gamma,optType))/alpha;
}

double HestonGamma(double S, double K, double r, double delta,
                   double V0, double tau,
                   double thet, double kappa, double SigmaV, double rho,
                   double gamma, std::string optType) {
    double alpha = 0.0001;
    return (HestonPrice(S+alpha,K,r,delta,V0,tau,thet,kappa,
                        SigmaV,rho,gamma,optType)-2.0*HestonPrice(S,K,r,delta,V0,
                                                                  tau,thet,kappa,SigmaV,rho,gamma,optType)+
            HestonPrice(S-alpha,K,r,delta,V0,tau,thet,kappa,SigmaV,rho,gamma,optType))/(alpha*alpha);
}

double HestonRho(double S, double K, double r, double delta,
                 double V0, double tau,
                 double thet, double kappa, double SigmaV, double rho,
                 double gamma, std::string optType) {
    double alpha = 0.0001;
    return (HestonPrice(S,K,r+alpha,delta,V0,tau,thet,kappa,
                        SigmaV,rho,gamma,optType)-HestonPrice(S,K,r,delta,V0,
                                                              tau,thet,kappa,SigmaV,rho,gamma,optType))/alpha;
}

double HestonVega(double S, double K, double r, double delta,
                  double V0, double tau,
                  double thet, double kappa, double SigmaV, double rho,
                  double gamma, std::string optType) {
    double alpha = 0.0001;
    return (HestonPrice(S,K,r,delta,V0+alpha,tau,thet,kappa,
                        SigmaV,rho,gamma,optType)-HestonPrice(S,K,r,delta,V0,
                                                              tau,thet,kappa,SigmaV,rho,gamma,optType))/alpha;
}

double HestonTheta(double S, double K, double r, double delta,
                   double V0, double tau,
                   double thet, double kappa, double SigmaV, double rho,
                   double gamma, std::string optType) {
    double alpha = 0.0001;
    return -(HestonPrice(S,K,r,delta,V0,tau+alpha,thet,kappa,
                         SigmaV,rho,gamma,optType)-HestonPrice(S,K,r,delta,V0,
                                                               tau,thet,kappa,SigmaV,rho,gamma,optType))/alpha;
}