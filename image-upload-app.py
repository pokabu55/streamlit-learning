import streamlit as st
from PIL import Image
import numpy as np
import cv2

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

with st.sidebar:
    th = st.slider('Threshold value', 0, 255, 125)
    st.write("Threshold value", th)

with st.sidebar:
    radio = st.radio(
        "Choose a binary method",
        ("Threshold", "Adaptive threshold mean","Adaptive threshold Gaussian",
        "Otsu' thresholding", "Otsu's thresholding + Gaussian fileter")
    )
    erosion=st.button("Erosion",key=1)
    dilation=st.button("Dilation",key=2)

uploaded_image = st.file_uploader("画像ファイルアップロード",type=['png', 'jpg', 'bmp'])

# 横並びの列としてレイアウトされたコンテナーを挿入する
col1, col2= st.columns(2)
#image_loc = st.empty()

col1.header("Original image")
col2.header("Binary image")

# 返されたコンテナー要素を追加するには with 表記の使用が推奨
with col1:
    if uploaded_image is not None:
        image=Image.open(uploaded_image,)
        img_array = np.array(image)
        st.image(img_array,caption = '元画像',use_column_width = None)
        img=pil2cv(image)

        gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
        ret,th1 = cv2.threshold(gray,th,255,cv2.THRESH_BINARY)
        th2 = cv2.adaptiveThreshold(gray,255,cv2.ADAPTIVE_THRESH_MEAN_C,\
        cv2.THRESH_BINARY,11,2)
        th3 = cv2.adaptiveThreshold(gray,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,\
        cv2.THRESH_BINARY,11,2)
        # image2 = Image.fromarray(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
        ret2,th4 = cv2.threshold(gray,0,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)
        blur = cv2.GaussianBlur(gray,(5,5),0)
        ret3,th5 = cv2.threshold(blur,0,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)

if radio=="Threshold" and uploaded_image is not None:
    col2.image(th1)
elif radio=="Adaptive threshold mean" and uploaded_image is not None:
    col2.image(th2)
elif radio=="Adaptive threshold Gaussian" and uploaded_image is not None:
    col2.image(th3)
elif radio=="Otsu' thresholding" and uploaded_image is not None:
    col2.image(th4)
elif radio=="Otsu's thresholding + Gaussian fileter" and uploaded_image is not None:
    col2.image(th5)

if erosion:
    kernel = np.ones((5,5),np.uint8)
    erodedimage = cv2.erode(th5,kernel,iterations = 1)
    col1.image(erodedimage)

'''
基本は、以下を参照
https://cafe-mickey.com/python/streamlit-6/

もうちょっと複雑なコードは
https://enjoy-life-fullest.com/2022/04/07/%E3%80%90python%E3%80%91opencv%E3%81%A8streamlit%E3%82%92%E4%BD%BF%E7%94%A8%E3%81%97%E3%81%A6%E7%B2%92%E5%AD%90%E3%81%AE%E7%94%BB%E5%83%8F%E5%87%A6%E7%90%86%E3%82%92%E8%A1%8C%E3%81%86/

'''