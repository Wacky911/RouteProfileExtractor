// ファイル名: main.cpp
// 作成者: Yuya Wakita
// 作成日: 2024-07-03
// 説明: mapboxのDirections APIから取得したJSONを基に、車速と勾配プロファイルを作成し出力する。
/////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <vector>
#include "nlohmann/json.hpp"
#include "json_parser.hpp"
#include "long_lat_to_x_y.hpp"
#include "mapbox_request.hpp"
#include "gradient_calc.hpp"
#include "csv_generator.hpp"

using json = nlohmann::json;

int main() {
    // JSONファイルを開く
    std::ifstream file("input.json");
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open JSON file. Please check the filename and try again." << std::endl;
        return 1;
    }

    // JSONファイル読み込み
    json jsonObj;
    file >> jsonObj;

    // JSONからデータ取得
    std::vector<double> speed = getVSP(jsonObj);
    std::vector<double> distance = getDistance(jsonObj);
    std::vector<double> duration = getDuration(jsonObj);
    std::vector<double> lon = getLong(jsonObj);
    std::vector<double> lat = getLat(jsonObj);

    // 標高のリクエストに必要な値を用意
    std::vector<int> tilex = long2X(lon);
    std::vector<int> tiley = lat2Y(lat);

    // Raster Tiles APIから標高を取得
    std::vector<double> elevation = mapbox_request(tilex, tiley, 18);

    // 勾配プロファイル
    std::vector<double> gradient = gradientCalc(elevation, distance);

    // CSV出力
    writeCSVrouteprofile("input.csv", duration, speed, gradient);

    return 0;
}
