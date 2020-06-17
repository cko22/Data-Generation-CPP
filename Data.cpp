//
// Created by Owner on 15/6/2020.
//
#include <iostream>
#include <random>
#include "Data.hpp"
#include "Heston.hpp"

void vector_random_filler(std::vector<double> &parameter, double lower_bound, double upper_bound){
    parameter.resize(SIZE);
    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    std::uniform_real_distribution<double> dist {lower_bound, upper_bound};

    auto gen = [&dist, &mersenne_engine](){
        return dist(mersenne_engine);
    };
    generate(parameter.begin(), parameter.end(), gen);
}

void generate_input_data (InputData &data){
    vector_random_filler(data.spot_price, 1,50);
    vector_random_filler(data.strike_price, 40,55);
    vector_random_filler(data.risk_free_rate, 0,1);
    vector_random_filler(data.dividend_yield, 0,1);
    vector_random_filler(data.initial_vol, 0,1);
    vector_random_filler(data.maturity_time, 0,1);
    vector_random_filler(data.long_term_vol, 0.2,1.0);
    vector_random_filler(data.mean_reversion_rate, 1,10);
    vector_random_filler(data.vol_vol, -0.95,-0.1);
    vector_random_filler(data.price_vol_corr, 0.0001,0.04);
    vector_random_filler(data.risk_aversion, 0,1);
}

void generate_output_data (InputData &data, OutputData &data1){
    data1.option_price.resize(SIZE);
    for (int i{0} ; data1.option_price.size() > i ; ++i){
        data1.option_price.at(i) = HestonPrice(data.spot_price.at(i),
                                               data.strike_price.at(i),
                                               data.risk_free_rate.at(i),
                                               data.dividend_yield.at(i),
                                               data.initial_vol.at(i),
                                               data.maturity_time.at(i),
                                               data.long_term_vol.at(i),
                                               data.mean_reversion_rate.at(i),
                                               data.vol_vol.at(i),
                                               data.price_vol_corr.at(i),
                                               data.risk_aversion.at(i),
                                               "call");
    }
}

void data_print(InputData &data, OutputData &data1){
    // Populate Input Data;
    generate_input_data(data);

    std::cout << "--------------------Input Data-------------------" << std::endl;
    std::cout << "Spot, Strike, Rate, Dividend, Init. Vol, Maturity, Long Term Vol, "
                 "M. Reversion, Vol of vol, S-Vol Corr, R. Aversion" << std::endl;
    for (int i{0} ; data.spot_price.size() > i ; ++i){
        std::cout << data.spot_price.at(i) << ", " << data.strike_price.at(i) << ", " << data.risk_free_rate.at(i) << ", "
        << data.dividend_yield.at(i) << ", " << data.initial_vol.at(i) << ", " << data.maturity_time.at(i) << ", "
        << data.long_term_vol.at(i)  << ", " << data.mean_reversion_rate.at(i) << ", " << data.vol_vol.at(i) << ", "
        << data.price_vol_corr.at(i) << ", " << data.risk_aversion.at(i) << std::endl;
    }

    // Populate;
    generate_output_data(data,data1);
    std::cout << "--------------------Output Data-------------------" << std::endl;
    std::cout << "Option Price" << std::endl;
    for (int i{0} ; data1.option_price.size() > i ; ++i) {
        std::cout << data1.option_price.at(i) << std::endl;
    }
}