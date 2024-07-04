#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <vector>
#include "nlohmann/json.hpp"

std::vector<double> getVSP(const nlohmann::json& jsonObj);
std::vector<double> getDistance(const nlohmann::json& jsonObj);
std::vector<double> getDuration(const nlohmann::json& jsonObj);
std::vector<double> getLong(const nlohmann::json& jsonObj);
std::vector<double> getLat(const nlohmann::json& jsonObj);

#endif // JSON_PARSER_HPP
