// ファイル名: json_parser.cpp
// 作成者: Yuya Wakita
// 作成日: 2024-06-17
// 説明: mapboxのDirections APIから取得したJSONファイルから、各データを取り出す為の関数を定義
////////////////////////////////////////////////////////////////////////////////////
// 更新日: 2024-07-04
// 更新者: Yuya Wakita
// コメント: のちの処理に備えspeeds、distances、durationsの先頭に0.0を追加
////////////////////////////////////////////////////////////////////////////////////
#include "json_parser.hpp"

// 説明: JSONファイルから車速プロファイルを取り出す
// 引数: JSONオブジェクト
// 戻り値: 車速プロファイル[m/s]
std::vector<double> getVSP(const nlohmann::json& jsonObj) {
    std::vector<double> speeds;
    speeds.push_back(0.0); // 後の処理に備え先頭に0を追加

    if (jsonObj.contains("routes")) {
        for (const auto& route : jsonObj["routes"]) {
            if (route.contains("legs")) {
                for (const auto& leg : route["legs"]) {
                    if (leg.contains("annotation") && leg["annotation"].contains("speed")) {
                        for (const auto& speed : leg["annotation"]["speed"]) {
                            speeds.push_back(speed.get<double>());
                        }
                    }
                }
            }
        }
    }
    return speeds;
}

// 説明: JSONファイルから距離を取り出す
// 引数: JSONオブジェクト
// 戻り値: 座標間の距離[sec]
std::vector<double> getDistance(const nlohmann::json& jsonObj) {
    std::vector<double> distances;
    distances.push_back(0.0); // 後の処理で勾配を計算する都合上先頭に0を追加

    if (jsonObj.contains("routes")) {
        for (const auto& route : jsonObj["routes"]) {
            if (route.contains("legs")) {
                for (const auto& leg : route["legs"]) {
                    if (leg.contains("annotation") && leg["annotation"].contains("distance")) {
                        for (const auto& distance : leg["annotation"]["distance"]) {
                            distances.push_back(distance.get<double>());
                        }
                    }
                }
            }
        }
    }
    return distances;
}

// 説明: JSONファイルから移動時間を取り出す
// 引数: JSONオブジェクト
// 戻り値: 座標間の移動時間[meter]
std::vector<double> getDuration(const nlohmann::json& jsonObj) {
    std::vector<double> durations;
    durations.push_back(0.0); // 後の処理に備え先頭に0を追加

    if (jsonObj.contains("routes")) {
        for (const auto& route : jsonObj["routes"]) {
            if (route.contains("legs")) {
                for (const auto& leg : route["legs"]) {
                    if (leg.contains("annotation") && leg["annotation"].contains("duration")) {
                        for (const auto& duration : leg["annotation"]["duration"]) {
                            durations.push_back(duration.get<double>());
                        }
                    }
                }
            }
        }
    }
    return durations;
}

// 説明: JSONファイルから経度(longitude)を取り出す
// 引数: JSONオブジェクト
// 戻り値: 経度[ddd.dddddd](十進法度単位)
std::vector<double> getLong(const nlohmann::json& jsonObj) {
    std::vector<double> lon;
   if (jsonObj.contains("routes")) {
        for (const auto& route : jsonObj["routes"]) {
            if (route.contains("geometry") && route["geometry"].contains("coordinates")) {
                for (const auto& coordinates : route["geometry"]["coordinates"]) {
                    lon.push_back(coordinates[0].get<double>());
                }
            }
        }
   }
   return lon;
}

// 説明: JSONファイルから緯度(latitude)を取り出す
// 引数: JSONオブジェクト
// 戻り値: 緯度[ddd.dddddd](十進法度単位)
std::vector<double> getLat(const nlohmann::json& jsonObj) {
    std::vector<double> lat;
   if (jsonObj.contains("routes")) {
        for (const auto& route : jsonObj["routes"]) {
            if (route.contains("geometry") && route["geometry"].contains("coordinates")) {
                for (const auto& coordinates : route["geometry"]["coordinates"]) {
                    lat.push_back(coordinates[1].get<double>());
                }
            }
        }
   }
   return lat;
}
