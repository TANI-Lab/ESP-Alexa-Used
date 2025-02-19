# 🚀 ESP32 + Alexa で LED & ステッピングモーターを制御 🎙️

このプロジェクトでは、**ESP32** を使用して **Alexa (Espalexaライブラリ経由)** で **LEDやステッピングモーターを制御** する方法を紹介します。ESP32 は WiFi に接続し、Alexa の音声コマンドに応答して LED の明るさを調整したり、モーターを動作させたりできます。

## 🌟 特徴
- 🎤 **Alexa 音声制御** (Espalexaライブラリを使用)
- 📡 **WiFi 接続**
- 💡 **LED の明るさを調整可能**
- 🔄 **ステッピングモーターのON/OFF制御**

## 🔧 必要なハードウェア
- ✅ **ESP32** 開発ボード
- ✅ **LED (GPIO 25, 26, 27 に接続)**
- ✅ **ステッピングモーター & ドライバ (GPIO 12, 14 に接続)**

## 🛠️ ピン設定
| コンポーネント        | ESP32 GPIO |
|-----------------|-----------|
| 🔵 青LED        | 25        |
| ⚪ 白LED       | 26        |
| 🔴 赤LED        | 27        |
| 🏁 ステッピングモータ DIR | 14        |
| 🔄 ステッピングモータ STEP | 12        |

## 📥 インストール
### 1️⃣ 必要なライブラリをインストール
Arduino IDE の **ライブラリマネージャー** から以下をインストールしてください:
- **WiFi.h** (ESP32用に標準搭載)
- **Espalexa** (Alexa 制御用)

### 2️⃣ リポジトリをクローン
```sh
git clone https://github.com/TANI-Lab/esp32-alexa-control.git
cd esp32-alexa-control
```

### 3️⃣ WiFi設定を更新
`main.cpp` の WiFi SSID とパスワードを修正してください:
```cpp
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
```

### 4️⃣ ESP32 にコードをアップロード
- `.ino` ファイルを **Arduino IDE** で開く。
- **ESP32 Dev Module** を選択。
- コンパイルして ESP32 に書き込み。

## 🎙️ 使い方
1. **ESP32 が WiFi に接続されていることを確認**
2. **Alexa でデバイスを検出**
   - Alexaアプリを開き、 **デバイス > 追加 > その他 > デバイスを検出**
   - `LED1`, `LED2`, `MT1` のデバイスが見つかる
3. **音声コマンドで制御**
   - 「Alexa、LED1をつけて」
   - 「Alexa、LED2の明るさを50%にして」
   - 「Alexa、MT1をオンにして」(ステッピングモーターが動作)

## 📜 コードの概要
### 📡 WiFi 接続
`connectWifi()` 関数でWiFi接続を確立します。

### 🔘 Alexa デバイス制御
デバイスは以下のように登録されます:
```cpp
espalexa.addDevice("LED1", firstLightChanged, 0);
espalexa.addDevice("LED2", SecondLightChanged);
espalexa.addDevice("MT1", MotorChanged);
```
各デバイスには、明るさの変更やトグルを処理する **コールバック関数** があります。

### 🔄 ステッピングモーター制御
- `loop()` 関数内で `MOT_RUN` が設定されていると、ステッピングモーターがトグル動作します。

## ⚠️ 注意点
- **Espalexaライブラリ** は **Alexa ハブなし** で動作可能。
- **ESP32とAlexaは同じネットワークに接続する必要あり**。
- **モーター制御は基本的なものなので、細かい動作調整が必要になる場合があります**。

## ⚠️ 動画
[![YouTube動画を見る](https://img.youtube.com/vi/fiy8IQm_EbE/hqdefault.jpg)](https://www.youtube.com/watch?v=fiy8IQm_EbE)

## 📜 ライセンス
このプロジェクトは **MIT License** のもとで提供されます。

## 👨‍💻 開発者
[TANI-Lab](https://github.com/TANI-Lab)
