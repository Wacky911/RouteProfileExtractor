// ファイル名: gradient_calc.cpp
// 作成者: Yuya Wakita
// 作成日: 2024-07-03
// 説明: 標高と距離から、勾配を算出する
////////////////////////////////////////////////////////////////////////////////////
#include "gradient_calc.hpp"

// 勾配を計算する関数
std::vector<double> gradientCalc(const std::vector<double>& elevation, const std::vector<double>& distance) {
    std::vector<double> gradient;
    gradient.push_back(0.0); // 後の処理に備え先頭に0を追加
    
    for (size_t i = 1; i < elevation.size(); ++i) {
        double deltaElevation = elevation[i] - elevation[i - 1];
        double deltaDistance = distance[i] - distance[i - 1];
        if (deltaDistance != 0) {
            double slope = deltaElevation / deltaDistance;// 傾きを算出
            double radian = std::atan(slope);// アークタンジェントを取ることでラジアン角を得る
            gradient.push_back(radian);
        } else {
            std::cerr << "deltaDistance is zero." << std::endl;
            gradient.push_back(0.0);
        }
    }
    
    return gradient;
}
