#ifndef CSV_GENERATOR_HPP
#define CSV_GENERATOR_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> 

void writeCSVrouteprofile(const std::string& filename, const std::vector<double>& duration, 
                            const std::vector<double>& speed, const std::vector<double>& gradient);

#endif // CSV_GENERATOR_HPP
