#include <iostream>
#include <string>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {

    // Draw shapes and text

    // Blank image
    cv::Mat img(512, 512, CV_8UC3, cv::Scalar(255,255,255));

    // cv::circle(img, cv::Point(256, 256), 100, cv::Scalar(0,69,255), 10);
    cv::circle(img, cv::Point(256, 256), 155, cv::Scalar(0,69,255), cv::FILLED);

    // cv::rectangle(img, cv::Point(130, 226), cv::Point(382,286), cv::Scalar(255,255,255), 3);
    cv::rectangle(img, cv::Point(130, 226), cv::Point(382,286), cv::Scalar(255,255,255), cv::FILLED);

    cv::line(img, cv::Point(130, 296), cv::Point(382,296), cv::Scalar(255,255,255), 2);

    cv::putText(img, "Show text", cv::Point(137, 262), cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar(0,69,255), 2);

    cv::imshow("Image", img);
    cv::waitKey(0);

    return 0;
}