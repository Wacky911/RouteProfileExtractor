#ifndef MAPBOX_REQUEST_HPP
#define MAPBOX_REQUEST_HPP

#include <iostream>
#include <vector>
#include <curl/curl.h>
#include <sstream>
#include "stb_image/stb_image.h"
#include "cppdotenv/dotenv.h"

std::vector<double> mapbox_request(const std::vector<int>& tilex, const std::vector<int>& tiley, int zoom);

#endif // MAPBOX_REQUEST_HPP
