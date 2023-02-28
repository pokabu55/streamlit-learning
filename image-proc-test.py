import streamlit as st
from PIL import Image
import numpy as np
import cv2

import tempfile
from pathlib import Path

def main():
    uploaded_image = st.file_uploader("画像ファイルアップロード",type=['png', 'jpg', 'bmp'])

    if uploaded_image is not None:
        print(uploaded_image.name)

    print(uploaded_image)

    # Make temp file path from uploaded file
    with tempfile.NamedTemporaryFile(delete=False) as tmp_file:
        #st.markdown("## Original PDF file")
        fp = Path(tmp_file.name)
        print(fp)
        #fp.write_bytes(uploaded_image.getvalue())
        #st.write(show_pdf(tmp_file.name))

        #imgs = convert_from_path(tmp_file.name)

        #st.markdown(f"Converted images from PDF")
        #st.image(imgs)



if __name__ == "__main__":
    main()
# https://shunyaueta.com/posts/2021-07-08/