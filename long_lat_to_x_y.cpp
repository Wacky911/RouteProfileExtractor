// ファイル名: lat_lon_to_x_y.cpp
// 作成者: Yuya Wakita
// 作成日: 2024-06-18
// 説明: 経度、緯度からAPIリクエスト用の地図タイル座標X値、Y値を算出する
////////////////////////////////////////////////////////////////////////////////////
// 更新日: 2024-07-03
// 更新者: Yuya Wakita
// コメント: long2X()とlat2Y()の引数をCSVではなく変数から受け取るように変更
////////////////////////////////////////////////////////////////////////////////////
#include "long_lat_to_x_y.hpp"

// 説明: Raster Tiles APIリクエスト用の値Xを算出する。
// 引数: long 経度
//      z ズーム値。通常は最大値の18を選択
// 戻り値: X 地図タイルのX座標
int long2tilex(double lon, int z) { 
	return (int)(floor((lon + 180.0) / 360.0 * (1 << z))); 
}

// 説明: Raster Tiles APIリクエスト用の値Yを算出する。
// 引数: lat 緯度
//      z ズーム値。通常は最大値の18を選択
// 戻り値: Y 地図タイルのY座標
int lat2tiley(double lat, int z) { 
    double latrad = lat * M_PI/180.0;
	return (int)(floor((1.0 - asinh(tan(latrad)) / M_PI) / 2.0 * (1 << z))); 
}

// 説明: 緯度からAPIリクエスト用の値Xを算出する。
// 引数: lon 経度
// 戻り値: tilexValues 経度から算出した地図タイルのX座標
std::vector<int> long2X(const std::vector<double>& lon) {
    std::vector<int> tilexValues;
    int zoom = 18;

    for (const double& longitude : lon) {
        int tilex = long2tilex(longitude, zoom);
        tilexValues.push_back(tilex);
    }

    return tilexValues;
}

// 説明: 緯度からAPIリクエスト用の値Yを算出する。
// 引数: lon 緯度
// 戻り値: tileyValues 緯度から算出したタイルのY座標
std::vector<int> lat2Y(const std::vector<double>& lat) {
    std::vector<int> tileyValues;
    int zoom = 18;

    for (const double& latitude : lat) {
        int tiley = lat2tiley(latitude, zoom);
        tileyValues.push_back(tiley);
    }

    return tileyValues;
}
