#include <iostream>
#include <string>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {

    // IMAGES from path
    std::string path = "Resources/test.jpg";
    cv::Mat img = cv::imread(path);

    // Basic functions
    cv::Mat grayImg; // gray
    cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);
    cv::Mat blurImg; // Blur
    cv::GaussianBlur(grayImg, blurImg, cv::Size(7, 7), 5, 0);
    cv::Mat cannyImg; // Canny
    cv::Canny(blurImg, cannyImg, 25, 75);

    cv::Mat dilateImg, erodeImg;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(cannyImg, dilateImg, kernel);
    cv::erode(dilateImg, erodeImg, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3)));

    // cv::imshow("Image", img);
    // cv::imshow("Grey Image", grayImg);
    // cv::imshow("Blur Image", blurImg);
    cv::imshow("Canny Image", cannyImg);
    cv::imshow("Dilate Image", dilateImg);
    cv::imshow("Erode Image", erodeImg);
    cv::waitKey(0);

    // Videos from path
    /*
    std::string videoPath = "Resources/test_video.mp4";
    cv::VideoCapture cap(videoPath);
    cv::Mat img;
    while(true) {
        cap.read(img);
        cv::imshow("Image", img);
        cv::waitKey(1);
    }
    */

    // WebCam
    // cv::VideoCapture cap(0);
    // cv::Mat img;
    // while(true) {
    //     cap.read(img);
    //     cv::imshow("Image", img);
    //     cv::waitKey(1);
    // }


    return 0;
}