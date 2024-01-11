import streamlit as st
from PIL import Image
import os

# Set page title
st.title("Image Viewer")

# Allow user to upload image file
uploaded_file = st.file_uploader("Upload an image", type=["jpg", "jpeg", "png"])

# Check if an image file was uploaded
if uploaded_file is not None:
    # Open the image
    image = Image.open(uploaded_file)

    # Add a slider to select zoom level
    if "zoom_level" not in st.session_state:
        st.session_state["zoom_level"] = 1.0

    zoom_level = st.slider("Select zoom level", min_value=0.1, max_value=2.0, value=st.session_state["zoom_level"])

    # If the zoom level has changed, resize the image and save it
    if st.session_state["zoom_level"] != zoom_level:
        st.session_state["zoom_level"] = zoom_level
        new_size = (int(image.size[0] * zoom_level), int(image.size[1] * zoom_level))
        image = image.resize(new_size, Image.ANTIALIAS)
        image.save("resized_image.png", "PNG")

    # Display the image
    if os.path.exists("resized_image.png"):
        st.image("resized_image.png", caption="Uploaded Image", use_column_width=True)
else:
    st.write("Please upload an image file.")
