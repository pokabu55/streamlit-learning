import streamlit as st
from PIL import Image
import numpy as np

uploaded_file = st.file_uploader("画像ファイルアップロード",type=['png', 'jpg', 'bmp'])
image = Image.open(uploaded_file)

img_array = np.array(image)
st.image(img_array, caption = 'サムネイル画像', use_column_width = True)

'''
基本は、以下を参照
https://cafe-mickey.com/python/streamlit-6/

もうちょっと複雑なコードは
https://enjoy-life-fullest.com/2022/04/07/%E3%80%90python%E3%80%91opencv%E3%81%A8streamlit%E3%82%92%E4%BD%BF%E7%94%A8%E3%81%97%E3%81%A6%E7%B2%92%E5%AD%90%E3%81%AE%E7%94%BB%E5%83%8F%E5%87%A6%E7%90%86%E3%82%92%E8%A1%8C%E3%81%86/

'''