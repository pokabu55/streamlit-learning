# streamlit-learning
streamlitを勉強してみる

# 自分で調べたリンク集
* [ブラウザで動くリアルタイム画像/音声処理アプリをStreamlitでサクッと作る](https://zenn.dev/whitphx/articles/streamlit-realtime-cv-app)
* [Python だけで作る Web アプリケーション(フロントエンド編)](https://zenn.dev/alivelimb/books/python-web-frontend)
* [Web カメラで得た画像を Streamlit 上で表示する](https://qiita.com/SatoshiTerasaki/items/f1724d68deecdc14103f)
* [StreamlitでWebアプリ開発！インストールからデプロイまで徹底解説](https://camp.trainocate.co.jp/magazine/streamlit-web/) 


# PYTHON 環境構築
* Ubuntuなので、Python3は入ってる。 3.10.6 だった。
* pip のインストール `sudo apt install python3-pip`
* streamlit のインストール `pip install streamlit`
* `streamlit hello` で、サンプルのサイトが起動するらしいがエラー
* エラーは `ImportError: cannot import name 'builder' from 'google.protobuf.internal'`
* ぐぐると、[こんな](https://discuss.streamlit.io/t/streamlit-1-16-error-when-running-app-with-local-tunnel-possibly-related-to-incorrect-protobuf-version/35094) QAが見つかったか、如何に…。

## Workaround
* streamlit と protobuf を特定のバージョンにすることで回避できた
* `pip install protobuf==3.19 streamlit==1.13` このバージョンの場合のみ、実行できた
* protobuf 最初に入ってたのは、3.12.4 だったかな？
* streamlit は、1.1.6.0 だった。
* pip で、このバージョンにセットすることで無事に起動成功。
* 初回起動時のみ、メールアドレスを聞かれるが、無視してエンターを押すとブラウザから初期画面が表示された。

### 参考サイト
* [ここ](https://community.deepnote.com/c/ask-anything/install-streamlit-in-deepnote)を参考にした。他には…
* [ここ](https://discuss.streamlit.io/t/streamlit-1-16-error-when-running-app-with-local-tunnel-possibly-related-to-incorrect-protobuf-version/35094)など
