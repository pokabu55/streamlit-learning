import streamlit as st

st.title("hello world!")

st.markdown("# Head1")
st.write("* write")
st.markdown("## Head2")
st.write("* descripstion.")

# サイドバー
inputString = st.sidebar.text_input("text_input:ここに書くと引数に内容を渡せる")
areaString = st.sidebar.text_area("text_area:何が違う？")
if st.sidebar.button("commit"):
    st.sidebar.write(inputString)
    st.sidebar.write(areaString)



check = st.checkbox("設定") # bool を返すんだって

if check:
    st.write("設定を隠したり")