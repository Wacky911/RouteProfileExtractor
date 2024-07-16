// ファイル名: csv_generator.cpp
// 作成者: Yuya Wakita
// 作成日: 2024-06-28
// 説明: CSVを生成する
////////////////////////////////////////////////////////////////////////////////////
// 更新日: 2024-07-04
// 更新者: Yuya Wakita
// コメント: writeCSVrouteprofile()を追加
////////////////////////////////////////////////////////////////////////////////////
#include "csv_generator.hpp"

// 説明: long,latのCSVを生成する
// 引数: filename CSVファイル名
//      lon 経度
//      lat 緯度
// 戻り値: なし
void writeCSVlonglat(const std::string& filename, const std::vector<double>& lon, const std::vector<double>& lat) {
    // ファイル出力ストリームを開く
    std::ofstream file(filename);

    // 小数点以下の桁数を設定
    file << std::fixed << std::setprecision(6);

    // ヘッダー行を書き込む
    file << "long,lat\n";

    // データ行を書き込む
    for (size_t i = 0; i < lon.size(); ++i) {
        file << lon[i] << "," << lat[i] << "\n";
    }

    file.close();
}

// 説明: distanceのCSVを生成する
// 引数: filename CSVファイル名
//      distance 各座標点間の距離[meter]
// 戻り値: なし
void writeCSVdistance(const std::string& filename, const std::vector<double>& distance) {
    // ファイル出力ストリームを開く
    std::ofstream file(filename);

    // 小数点以下の桁数を設定
    file << std::fixed << std::setprecision(1);

    // ヘッダー行を書き込む
    file << "distance\n";
    // 最初の座標点では距離0
    file << "0.0\n";

    // データ行を書き込む
    for (size_t i = 0; i < distance.size(); ++i) {
        file << distance[i] << "\n";
    }

    file.close();
}

// 説明: EnergyEstimator用のCSVを生成する
// 引数: filename CSVファイル名
//      duration 座標間の移動時間[sec]
//      speed 車速[m/s]
//      gradient 勾配[rad]
// 戻り値: なし
void writeCSVrouteprofile(const std::string& filename, const std::vector<double>& duration, 
                            const std::vector<double>& speed, const std::vector<double>& gradient) {
    // ファイル出力ストリームを開く
    std::ofstream file(filename);

    // 1列目の時系列を用意
    std::vector<double> time(duration.size());
    
    double sum = 0.0;

    for (size_t i = 0; i < duration.size(); ++i) {
        sum += duration[i];
        time[i] = sum;
    }

    // ヘッダー行を書き込む
    file << "time,speed,gradient\n";

    // データ行を書き込む
    for (size_t i = 0; i < time.size(); ++i) {
        file << time[i] << "," << speed[i] << "," << gradient[i] <<"\n";
    }

    file.close();
}
