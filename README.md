# streamlit-learning
streamlitを勉強してみる

まずは、下記 #2 のサイトで、Streamlit をサクッと勉強してみる！

# 自分で事前に調べたリンク集
1. まずは、[公式](https://streamlit.io/)
2. [ブラウザで動くリアルタイム画像/音声処理アプリをStreamlitでサクッと作る](https://zenn.dev/whitphx/articles/streamlit-realtime-cv-app)
3. [Python だけで作る Web アプリケーション(フロントエンド編)](https://zenn.dev/alivelimb/books/python-web-frontend)
4. [Web カメラで得た画像を Streamlit 上で表示する](https://qiita.com/SatoshiTerasaki/items/f1724d68deecdc14103f)
5. [StreamlitでWebアプリ開発！インストールからデプロイまで徹底解説](https://camp.trainocate.co.jp/magazine/streamlit-web/)
6. [Streamlit入門 – ウィジェットの使い方(前編)](https://data-analytics.fun/2022/06/26/streamlit-widget-1/)
7. [OpenCVとStreamlitを使用して粒子の画像処理を行う](https://enjoy-life-fullest.com/2022/04/07/%E3%80%90python%E3%80%91opencv%E3%81%A8streamlit%E3%82%92%E4%BD%BF%E7%94%A8%E3%81%97%E3%81%A6%E7%B2%92%E5%AD%90%E3%81%AE%E7%94%BB%E5%83%8F%E5%87%A6%E7%90%86%E3%82%92%E8%A1%8C%E3%81%86/)

# PYTHON 環境構築
## 事前準備
* Ubuntuなので、Python3は入ってる。 3.10.6 だった。
* pip のインストール `sudo apt install python3-pip`
## streamlit インストール
* streamlit のインストール `pip install streamlit`
* `streamlit hello` で、サンプルのサイトが起動するらしいがエラー
* エラーは `ImportError: cannot import name 'builder' from 'google.protobuf.internal'`
* ぐぐると、[こんな](https://discuss.streamlit.io/t/streamlit-1-16-error-when-running-app-with-local-tunnel-possibly-related-to-incorrect-protobuf-version/35094) QAが見つかったか、如何に…。

## streamlit の Workaround
* streamlit と protobuf を特定のバージョンにすることで回避できた
* `pip install protobuf==3.19 streamlit==1.13` このバージョンの場合のみ、実行できた
* protobuf 最初に入ってたのは、3.12.4 だったかな？
* streamlit は、1.1.6.0 だった。
* pip で、このバージョンにセットすることで無事に起動成功。
* 初回起動時のみ、メールアドレスを聞かれる。が、無視してエンターを押すとブラウザから初期画面が表示された。
* インストール〜実行まで完了。
### 参考サイト
* [streamlitの起動時エラーの記事](https://community.deepnote.com/c/ask-anything/install-streamlit-in-deepnote)を参考にした。
* 他には…[ここ](https://discuss.streamlit.io/t/streamlit-1-16-error-when-running-app-with-local-tunnel-possibly-related-to-incorrect-protobuf-version/35094)など

## webカメラを使う場合
* opencv のインストール：`pip install opencv-python`
* streamlit-webrtc のインストール：`pip install streamlit-webrtc`

## OpenCVについて
* 下記のようにビルド版は4種類あるらしい。[出典。](https://a244.hateblo.jp/entry/2018/09/04/190000)
* ここでは、サーバー版の-headless 版でもよいのかな？

|packege name|explanation|
|:---:|---|
|opencv-python|通常版|
|opencv-python-headless|上記のGUI関連を無効にしたパッケージ。サーバー環境向け。|
|opencv-contrib-python|contributorによって寄贈された拡張モジュール群。比較的最新のアルゴリズム、試験的な機能を含む。|
|opencv-contrib-python-headless|上記のGUI関連を無効にしたパッケージ。サーバー環境向け|

### 参考サイト
* [streamlit-webrtcのサンプル記事](https://qiita.com/kotai2003/items/fe7dedd03ed049ac0265)まずはここ。
* [上の記事の参照元](https://zenn.dev/whitphx/articles/streamlit-realtime-cv-app#%E5%BF%85%E8%A6%81%E3%81%AA%E3%83%91%E3%83%83%E3%82%B1%E3%83%BC%E3%82%B8%E3%81%AE%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%88%E3%83%BC%E3%83%AB)
* [別の記事](https://qiita.com/SatoshiTerasaki/items/f1724d68deecdc14103f#%E5%BF%85%E8%A6%81%E3%81%AA%E3%83%A2%E3%82%B8%E3%83%A5%E3%83%BC%E3%83%AB%E3%82%92%E3%82%A4%E3%83%B3%E3%83%9D%E3%83%BC%E3%83%88)
* [pythonのOpenCVのサンプル](https://camp.trainocate.co.jp/magazine/python-opencv/)

## 画像ファイルの読み込み
* [ここ](https://cafe-mickey.com/python/streamlit-6/)

## VSCode での拡張機能
http://trelab.info/visual-studio-code/python-vscode%E3%81%A7autopep8%E3%82%92%E9%81%A9%E7%94%A8%E3%81%99%E3%82%8B/
https://qiita.com/firedfly/items/00c34018581c6cec9b84
https://qiita.com/momotar47279337/items/73157407ae824751afc4


# 実装と実行
* サンプルコード `app.py` を作成
    ```
    import streamlit as st

    st.title("hello world!")
    ```
* 実行方法
  * `$streamlit run app.py`
  * これで、ブラウザが自動起動して、hello world! と書かれたページを表示する。

# Webカメラによるリアルタイム画像処理
## 参考ソースコード
* 上記の参考リンクの#2を参考に実装してみる
* [ブラウザで動くリアルタイム画像/音声処理アプリをStreamlitでサクッと作る](https://zenn.dev/whitphx/articles/streamlit-realtime-cv-app)
* camera-app.py に実装する

# アップロード画像による画像処理
## 参考ソースコード
* 上記参考リンクの#7を参考に実装してみる
* [OpenCVとStreamlitを使用して粒子の画像処理を行う](https://enjoy-life-fullest.com/2022/04/07/%E3%80%90python%E3%80%91opencv%E3%81%A8streamlit%E3%82%92%E4%BD%BF%E7%94%A8%E3%81%97%E3%81%A6%E7%B2%92%E5%AD%90%E3%81%AE%E7%94%BB%E5%83%8F%E5%87%A6%E7%90%86%E3%82%92%E8%A1%8C%E3%81%86/)
* image-upload-app.py に実装する

### 以下も参考にしながら実装した
* [ファイルアップローダーを使う](https://cafe-mickey.com/python/streamlit-6/)
* [公式のsidebarの説明](https://docs.streamlit.io/library/api-reference/layout/st.sidebar)
* [ここも参考になりそうかも](https://blog.amedama.jp/entry/streamlit-tutorial)
* [with構文の説明](https://it-biz.online/python/with/)
