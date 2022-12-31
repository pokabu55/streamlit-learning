# streamlit-learning
streamlitを勉強してみる

# 自分で事前に調べたリンク集
* まずは、[公式](https://streamlit.io/)
* [ブラウザで動くリアルタイム画像/音声処理アプリをStreamlitでサクッと作る](https://zenn.dev/whitphx/articles/streamlit-realtime-cv-app)
* [Python だけで作る Web アプリケーション(フロントエンド編)](https://zenn.dev/alivelimb/books/python-web-frontend)
* [Web カメラで得た画像を Streamlit 上で表示する](https://qiita.com/SatoshiTerasaki/items/f1724d68deecdc14103f)
* [StreamlitでWebアプリ開発！インストールからデプロイまで徹底解説](https://camp.trainocate.co.jp/magazine/streamlit-web/) 


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

## VSCode での拡張機能


# 実装と実行
* サンプルコード `app.py` を作成
    ```
    import streamlit as st

    st.title("hello world!")
    ```
* 実行方法
  * `$streamlit run app.py`
  * これで、ブラウザが自動起動して、hello world! と書かれたページを表示する。