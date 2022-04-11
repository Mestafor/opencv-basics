#include <iostream>
#include <string>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {

    // Color detection

    // IMAGES from path
    std::string path = "Resources/lambo.png";
    cv::Mat img = cv::imread(path);

    cv::Mat imgHSV;
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

    int hmin = 0;
    int smin = 10;
    int vmin = 123;

    int hmax = 19;
    int smax = 240;
    int vmax = 255;

    cv::Mat imgMask;

    cv::namedWindow("Trackbars", (640, 100));
    
    cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    cv::createTrackbar("Saturation Min", "Trackbars", &smin, 255);
    cv::createTrackbar("Value Min", "Trackbars", &vmin, 255);

    cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    cv::createTrackbar("Saturation Max", "Trackbars", &smax, 255);
    cv::createTrackbar("Value Max", "Trackbars", &vmax, 255);

    while(true) {
        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);
        cv::inRange(imgHSV, lower, upper, imgMask);

        cv::imshow("Image", img);
        cv::imshow("Image HSV", imgHSV);
        cv::imshow("Image Mask", imgMask);
        cv::waitKey(1);
    }

    return 0;
}