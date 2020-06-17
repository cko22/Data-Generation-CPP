//
// Created by Owner on 15/6/2020.
//

#ifndef HESTON_PRICING_ANALYTICAL_DATA_HPP
#define HESTON_PRICING_ANALYTICAL_DATA_HPP
#include <vector>

// Data size 5,000,000
#define SIZE 1

struct InputData{
    std::vector<double> spot_price;
    std::vector<double> strike_price;
    std::vector<double> risk_free_rate;
    std::vector<double> dividend_yield;
    std::vector<double> initial_vol;
    std::vector<double> maturity_time;
    std::vector<double> long_term_vol;
    std::vector<double> mean_reversion_rate;
    std::vector<double> vol_vol;
    std::vector<double> price_vol_corr;
    std::vector<double> risk_aversion;
};

struct OutputData{
    std::vector<double> option_price;
};

void vector_random_filler(std::vector<double> &parameter, double lower_bound, double upper_bound);

void generate_input_data (InputData &data);

void generate_output_data (InputData &data, OutputData &data1);

void data_print(InputData &data, OutputData &data1);

#endif //HESTON_PRICING_ANALYTICAL_DATA_HPP
