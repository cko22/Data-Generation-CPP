
#include "trapezoidalMethod.hpp"
#include "Heston.hpp"
#include "Data.hpp"


int main() {

//    std::string optType = "call"; //Option type (call or put)
//    double price_, delta_, gamma_, rho_, vega, theta_;
//    price_ = HestonPrice(S,K,r,delta,V0,tau,theta,kappa,SigmaV,rho,gamma,optType);
//    delta_ = HestonDelta(S,K,r,delta,V0,tau,theta,kappa,SigmaV,rho,gamma,optType);
//    gamma_ = HestonGamma(S,K,r,delta,V0,tau,theta,kappa,SigmaV,rho,gamma,optType);
//    rho_ = HestonRho(S,K,r,delta,V0,tau,theta,kappa,SigmaV,rho,gamma,optType);
//    vega = HestonVega(S,K,r,delta,V0,tau,theta,kappa,SigmaV,rho,gamma,optType);
//    theta_ = HestonTheta(S,K,r,delta,V0,tau,theta,kappa,SigmaV,rho,gamma,optType);
//    std::cout << "Option Price: " << price_ << std::endl;
//    std::cout << "Delta greek: " <<delta_ << std::endl;
//    std::cout << "Gamma greek: " <<gamma_ << std::endl;
//    std::cout << "Rho: " <<rho_ << std::endl;
//    std::cout << "Vega: " <<vega << std::endl;
//    std::cout << "Theta: " <<theta_ << std::endl;
    InputData data1;
    OutputData data2;
    data_print(data1, data2);
    return 0;

}