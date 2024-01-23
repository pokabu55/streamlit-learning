import streamlit as st
from PIL import Image
import numpy as np
import cv2

import tempfile
from pathlib import Path

import subprocess


def image_processing(srcImagePIL, processName):
    # 画像処理のメイン関数的な

    # 処理画像をネイティブで処理できるようにファイル出力
    tmpSrcFileName = "./tmp/srcImg.ppm"  # png"
    tmpDstFileName = "./tmp/dstImg.ppm"  # png"

    # 何か処理してみるか
    # srcImageCV = pil2cv(srcImagePIL)
    srcImagePIL.save(tmpSrcFileName)
    # エラー処理は？

    # ネイティブアプリを呼び出す
    subprocess.call("./modules/sample/bin/sample")

    # 画像データを一旦取得してから表示する場合
    dstImagePIL = Image.open(tmpDstFileName)
    dstImageCV = pil2cv(dstImagePIL)

    # 出力画像作成
    dstImageCV = cv2.cvtColor(dstImageCV, cv2.COLOR_BGR2RGB)

    return dstImageCV


def pil2cv(image):
    """PIL型 -> OpenCV型"""
    new_image = np.array(image, dtype=np.uint8)
    if new_image.ndim == 2:  # モノクロ
        pass
    elif new_image.shape[2] == 3:  # カラー
        new_image = cv2.cvtColor(new_image, cv2.COLOR_RGB2BGR)
    elif new_image.shape[2] == 4:  # 透過
        new_image = cv2.cvtColor(new_image, cv2.COLOR_RGBA2BGRA)
    return new_image


def main():
    print("main-0")
    uploaded_image = st.file_uploader("画像ファイルアップロード", type=["png", "jpg", "bmp"])

    print("main-1")

    # 縦並びでレイアウト

    with st.sidebar:
        scale = st.slider("resize ratio", 0.5, 2.0, 1.0)
        st.write("resize ratio", scale)

        # ここに1．0倍にするボタンを置く
        if st.button("1.0倍にする"):
            scale = 1.0

    if uploaded_image is not None:
        print("uploaded_image is not None")

        # 画像ファイルを直接指定する場合
        # st.image(uploaded_image)
        # 画像データを一旦取得してから表示する場合
        originalImagePIL = Image.open(uploaded_image)

        # 画像サイズを取得する
        width, height = originalImagePIL.size
        # サイズの表示
        st.write(f"画像の幅: {width}px, 高さ: {height}px")

        # use_column_widh を False にすると、オリジナルのサイズで表示
        # これは、選択したいね
        # st.image(originalImagePIL, caption="original image", use_column_width=width)

        # 処理
        # image_processing(originalImagePIL, "threthold")

        # 結果表示
        # dstImagePIL = Image.open("./tmp/dstImg.ppm")

        # 2個めの画像を開けば勝手に縦並びになっとる
        # st.image(dstImagePIL, caption="processed image", use_column_width=True)

        # 画像の拡大縮小ボタン
        # scale = st.slider("画像の拡大縮小", min_value=0.1, max_value=2.0, value=1.0, step=0.1)
        # if st.button("拡大縮小を適用"):
        # print("拡大縮小を適用")

        # 画像の拡大縮小
        new_size = (int(width * scale), int(height * scale))
        resized_image = originalImagePIL.resize(new_size)

        # 拡大縮小後の画像を表示
        st.image(resized_image, caption="resized image", use_column_width=False)


if __name__ == "__main__":
    main()

# https://shunyaueta.com/posts/2021-07-08/
