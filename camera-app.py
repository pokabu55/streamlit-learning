import streamlit as st
from streamlit_webrtc import webrtc_streamer
import cv2
import av #strealing video library

st.title('Streamlit App Test')
st.write('Hello world')

def callback(frame):
    img = frame.to_ndarray(format="bgr24")

    img = cv2.cvtColor(cv2.Canny(img, 100, 200), cv2.COLOR_GRAY2BGR)

    return av.VideoFrame.from_ndarray(img, format="bgr24")

webrtc_streamer(key='example', video_frame_callback=callback)
