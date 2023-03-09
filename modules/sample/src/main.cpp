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
    std::string srcFileName = "./tmp/srcImg.png";
    std::string dstFileName = "./tmp/dstImg.png";

    std::cout << "srcFileName = " << srcFileName << std::endl;
    std::cout << "dstFileName = " << dstFileName << std::endl;

    // load image
    cv::Mat src = cv::imread(srcFileName, 0);

    // 処理データをどうやって用意しようか
    // Mat形式から、PNM形式に変換する処理が欲しい

    // そしてなにか処理したら、PNMからMatに戻す処理が欲しい
    // Matに戻した上で、pngで保存する流れ

    // error
    if (src.empty()) {
        std::cout << "empty image." << std::endl;
        return -1;
    }

    // threshold
    cv::Mat dst;
    cv::threshold(src, dst, 0, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);

    // 保存
    cv::imwrite(dstFileName, dst);

    return 0;
}
