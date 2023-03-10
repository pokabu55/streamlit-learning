#include <stdio.h>
#include <string>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include "../../common/include/imagePNM.hpp"

int main (int argc, char *argv[])
{
    std::string srcFileName = "./tmp/srcImg.ppm";//png";
    std::string dstFileName = "./tmp/dstImg.ppm";//png";

    std::cout << "srcFileName = " << srcFileName << std::endl;
    std::cout << "dstFileName = " << dstFileName << std::endl;

    // load image
    cv::Mat src = cv::imread(srcFileName, 0);

    // error
    if (src.empty()) {
        std::cout << "empty image." << std::endl;
        return -1;
    }

    // 処理データをどうやって用意しようか
    // Mat形式から、PNM形式に変換する処理が欲しい
    // TODO: grayscale 変換する？
    CImagePNM srcImg;
    if (!srcImg.loadPPM(srcFileName, true)) return -1;

    std::cout << "depth = " << srcImg.m_iDepth << std::endl;

    // 例えば、二値化
    CImagePNM proc;
    if (!srcImg.createClone8(proc)) return -1;

    int TH = 128;

    for (int i=0; i<srcImg.m_imgW*srcImg.m_imgH; i++) {
        if (proc.m_imgData[i]>TH)
            proc.m_imgData[i] = 255;
        else
            proc.m_imgData[i]=0;
    }

    // そしてなにか処理したら、PNMからMatに戻す処理が欲しい
    // Matに戻した上で、pngで保存する流れ
    //threshold(srcImg);

    // threshold
    //cv::Mat dst;
    //cv::threshold(src, dst, 0, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);

    // 保存
    //cv::imwrite(dstFileName, dst);
    if (!proc.savePPM(dstFileName)) return -1;

    return 0;
}
