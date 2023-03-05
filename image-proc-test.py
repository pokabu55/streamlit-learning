import streamlit as st
from PIL import Image
import numpy as np
import cv2

import tempfile
from pathlib import Path

def pil2cv(image):
    ''' PIL型 -> OpenCV型 '''
    new_image = np.array(image, dtype=np.uint8)
    if new_image.ndim == 2:  # モノクロ
        pass
    elif new_image.shape[2] == 3:  # カラー
        new_image = cv2.cvtColor(new_image, cv2.COLOR_RGB2BGR)
    elif new_image.shape[2] == 4:  # 透過
        new_image = cv2.cvtColor(new_image, cv2.COLOR_RGBA2BGRA)
    return new_image

def main():
    uploaded_image = st.file_uploader("画像ファイルアップロード",type=['png', 'jpg', 'bmp'])

    # 縦並びでレイアウト
    
    if uploaded_image is not None:
        # 画像ファイルを直接指定する場合
        #st.image(uploaded_image)
        # 画像データを一旦取得してから表示する場合
        originalImage = Image.open(uploaded_image)

        # use_column_widh を False にすると、オリジナルのサイズで表示
        # これは、選択したいね
        st.image(originalImage, caption="original image", use_column_width=True)

        # 何か処理してみるか
        procImageCV = pil2cv(originalImage)

        # 処理

        # 表示用に戻す
        dispImage = cv2.cvtColor(procImageCV, cv2.COLOR_BGR2RGB)

        # 2個めの画像を開けば勝手に縦並びになっとる
        st.image(dispImage, caption="processed image", use_column_width=True)

if __name__ == "__main__":
    main()

# https://shunyaueta.com/posts/2021-07-08/