# RouteProfileExtractor

Mapboxが提供しているDirections APIから取得したJSONファイルを基にinput.csvを生成します。任意のルートの車速、勾配プロファイルを得ることを目的としており、input.csvの構成は「時間,車速,勾配」となっています。

尚、このソフトを使用するには無料のMapboxアカウントを作成し、API access tokenを取得する必要があります。

<br>

## 概要

Directions APIはルート案内や経路計算を提供するサービスです。このソフトでは以下の手順でinput.csvを生成します。

<br>

1. Directions APIが返すJSONファイルを解析し以下のデータを抽出します。

| 項目        | 説明                       |
|------------|---------------------------|
| 車速       | input.csvのspeed列の値として使用します。 |
| 座標点間の距離 | 勾配の算出に使用します。　|
| 座標点間の移動時間 | 値を積算しinput.csvのtime列の値として使用します。|
| 座標点の経度 | Mapboxが提供しているRaster Tiles APIを使用してMapbox Terrain-RGBタイルセットを取得するために使用します。これにより標高を取得することができます。|
| 座標点の緯度 | Mapboxが提供しているRaster Tiles APIを使用してMapbox Terrain-RGBタイルセットを取得するために使用します。これにより標高を取得することができます。|

<div style="text-align: center;">
※ここでの座標点はルート上にプロットされた連続した座標点を指します。  
</div>
<br>
<br>

2. 1で取得した緯度経度情報を使用して、Raster Tiles APIへリクエストを送信します。レスポンスとして返される画像データを解析し、標高データを取得します。

<br>
<br>

3. 2で取得した標高データと1で取得した距離データを基に勾配を算出します。

<br>
<br>

4. ここまでに得たデータを基にinput.csvを生成します。

<br>
<br>

## 使用方法

### 事前準備

1. このソフトの実行にはMapboxのaccess tokenが必要です。Mapboxのアカウントを作成してください。  

* Mapboxアカウント作成ページ: <https://account.mapbox.com/auth/signup/>  

<br>


2. プロジェクトのルートに.envを作成し、以下を記述します。  
   "YOUR_API_KEY"はMapboxのaccess tokenに置き換えてください。
```
API_KEY=YOUR_API_KEY
```

<br>

### JSONファイルの取得

1. [Directions API Playground](https://docs.mapbox.com/playground/directions/)へアクセスします。

<br>

2. ページが表示されたらページ左側のパラメーター設定欄について以下のことを確認します。
   
* 「access token」に自分のAPIキーが設定されているか？
* 「routing profile」がdrivingになっているか？
* 「geometries」がgeojsonになっているか？
* 「overview」がfullになっているか？
* 「annotations」に "distance" "duration" "speed" の3つにチェックが入っているか？

<br>

3. 「coordinates」に出発地と到着地の座標情報 [経度,緯度] を入力します。  
※ 緯度,経度の順番ではないことに注意してください。

<br>

4. 地図画面を確認し、車速、勾配プロファイルを得たいルートが引けていることを確認してください。引けていない場合は「coordinates」に経由地を追加し調整します。

<br>

5. ページ右下にRequest URLが生成されています。URLをコピーし、ブラウザのアドレスバーに貼り付けEnterキーを押します。

<br>

6. Directions APIからResponseが返されます。"右クリック→別名で保存" もしくは "全選択してコピー→任意のテキストエディタに貼り付け" でinput.jsonとしてローカルに保存してください。

<br>

### プログラムの実行

1. 前項で用意したinput.jsonを実行ファイルと同じディレクトリに配置します。 

<br>

2. プログラムを実行します。プログラムはJSONを解析し座標点の数だけ標高データのリクエストを行うため、ルートが長ければ長いほど処理に時間がかかります。

<br>

3. 標高データの取得後、各データの処理が行われinput.csvが実行ファイルと同じディレクトリに生成されます。

<br>

## 注意事項

プログラムの実行にはネットワーク接続が必要です。

<br>

## 必要なライブラリ
* libcurl

<br>

Raster Tiles APIとのインターフェースに上記ライブラリを使用しています。  
ライブラリインストール後、使用しているPCに応じてCMakeLists.txtを書き換えてください。

<br>

## ビルドと実行

CMakeLists.txtを使用してビルドするには、以下のコマンドを実行します。

```
cd build
```

```
cmake ..
```

```
cmake --build .
```

<br>

プログラムを実行するには以下のコマンドを実行します。
```
./RouteProfileExtractor
```

<br>

## 使用言語とテスト環境

* OS: macOS 14.5
* プログラミング言語: C++  
* コンパイラ: clang++  
* 依存ライブラリ: libcurl
* CMakeバージョン: 3.30.0