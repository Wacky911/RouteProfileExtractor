// ファイル名: mapbox_request.cpp
// 作成者: Yuya Wakita
// 作成日: 2024-06-18
// 説明: Raster Tiles APIへリクエストを送信し、レスポンスを解析し標高を算出する。
////////////////////////////////////////////////////////////////////////////////////
#define STB_IMAGE_IMPLEMENTATION
#include "mapbox_request.hpp"

// 説明: HTTPレスポンスで受信したデータを処理するためのコールバック関数
//      受信したデータはベクター(unsigned char)に追加される。
// 引数: contents 受信したデータへのポインタ
//      size データの各要素のサイズ
//      nmemb データ要素の数
//      userp ユーザー定義のデータ構造へのポインタ
// 戻り値: 受信したデータのサイズ
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::vector<unsigned char>*)userp)->insert(
        ((std::vector<unsigned char>*)userp)->end(),
        (unsigned char*)contents,
        (unsigned char*)contents + size * nmemb
    );
    return size * nmemb;
}

// 説明: Raster Tiles APIから取得したPNGのピクセルから標高を算出する。
// 引数: r ピクセル値 Red
//      g ピクセル値 Green
//      b ピクセル値 Blue
// 戻り値: 標高[meter]
double calculateHeight(unsigned char r, unsigned char g, unsigned char b) {
    return -10000 + ((r * 256 * 256 + g * 256 + b) * 0.1f);
}

// 説明: Raster Tiles APIへリクエストを送信し、レスポンスとして得た画像から標高を算出する。
// 引数: tilex 経度から算出したタイルのX座標。※タイルとは地図データを小さな正方形の画像に分割したもの
//      tiley 緯度から算出したタイルのY座標
//      z     地図のzoom値。通常は最大の18を指定する
// 戻り値: 標高[meter]
std::vector<double> mapbox_request(const std::vector<int>& tilex, const std::vector<int>& tiley, int zoom) {
    CURL* curl;
    CURLcode res;
    std::vector<unsigned char> imageData;
    std::vector<double> elevations;

    // .envファイル読み込み
    dotenv::init();
    const char* apiKey = std::getenv("API_KEY");
    if (apiKey) {
        std::cout << "API Key: " << apiKey << std::endl;
    } else {
        std::cerr << "API_KEY environment variable not found!" << std::endl;
    }

    // libcurlの初期化
    curl_global_init(CURL_GLOBAL_DEFAULT);

    for (size_t i = 0; i < tilex.size(); ++i) {
        curl = curl_easy_init();

        if(curl) {
            // リクエストURLを設定
            std::ostringstream urlStream;
            urlStream << "https://api.mapbox.com/v4/mapbox.terrain-rgb/" << zoom << "/" << tilex[i] << "/" << tiley[i] << ".pngraw?access_token=" << apiKey;
            std::string url = urlStream.str();

            // リクエストオプションを設定
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &imageData);

            // リクエストを実行
            res = curl_easy_perform(curl);
            if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }

            // リソースを解放
            curl_easy_cleanup(curl);

            // 画像データを読み込み
            int width, height, channels;
            unsigned char* img = stbi_load_from_memory(imageData.data(), imageData.size(), &width, &height, &channels, 3);

            if (img) {
                std::cout << "Image loaded: " << width << "x" << height << " with " << channels << " channels" << std::endl;

                // 画像の中心ピクセルから標高を算出
                int centerX = width / 2;
                int centerY = height / 2;
                int index = (centerY * width + centerX) * 3;
                unsigned char r = img[index];
                unsigned char g = img[index + 1];
                unsigned char b = img[index + 2];
                double heightValue = calculateHeight(r, g, b);
                std::cout << "Height at center of tile (" << tilex[i] << ", " << tiley[i] << "): " << heightValue << " meters" << std::endl;
                elevations.push_back(heightValue);

                // 画像メモリを解放
                stbi_image_free(img);
            } else {
                std::cerr << "Failed to load image for tile (" << tilex[i] << ", " << tiley[i] << ")" << std::endl;
            }

            imageData.clear(); // 次のタイルのためにimageDataをクリア
        }
    }

    // libcurlのクリーンアップ
    curl_global_cleanup();

    return elevations;
}
