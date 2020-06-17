cmake_minimum_required(VERSION 3.15)
project(Heston_Pricing_Analytical)

set(CMAKE_CXX_STANDARD 14)

add_executable(Heston_Pricing_Analytical main.cpp trapezoidalMethod.cpp trapezoidalMethod.hpp Heston.cpp Heston.hpp Data.cpp Data.hpp)