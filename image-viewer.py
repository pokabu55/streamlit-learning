import streamlit as st
from PIL import Image
import os

# File uploader
uploaded_file = st.file_uploader("Upload an image", type=["jpg", "jpeg", "png"])

if uploaded_file is not None:
    # Save the file temporarily
    with open("temp_img", "wb") as f:
        f.write(uploaded_file.getbuffer())

# If the file exists, read it
if os.path.exists("temp_img"):
    image = Image.open("temp_img")

    # Slider for zoom level
    zoom_level = st.slider("Zoom Level", min_value=0.5, max_value=2.0, value=1.0)

    # Calculate new image size and resize
    new_size = (int(image.size[0] * zoom_level), int(image.size[1] * zoom_level))
    image = image.resize(new_size)

    # Display the image
    st.image(image, caption="Uploaded Image")

"""
Streamlitでは、スライダーの値が変更されると、全体のスクリプトが再実行されます。しかし、ファイルアップローダーからのファイルは再実行時には保持されません。そのため、スライダーを動かすと、アップロードされたファイルがなくなり、画像が更新されないという問題が発生します。

この問題を解決するためには、アップロードされたファイルを一時的に保存し、再実行時にその保存されたファイルを読み込むようにする必要があります。

以下にそのためのコードを示します。

このコードでは、アップロードされたファイルを一時的に"temp_img"という名前で保存します。そして、そのファイルが存在する場合には、それを読み込み、画像の拡大縮小と表示を行います。これにより、スライダーを動かしても画像が更新されるようになります。



"""
