#include <iostream>
#include <string>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {

    // Resize

    // IMAGES from path
    std::string path = "Resources/test.jpg";
    cv::Mat img = cv::imread(path);

    std::cout << img.size() << std::endl;

    // Resizing
    cv::Mat resizedImg;
    cv::resize(img, resizedImg, cv::Size(img.size().width / 2, img.size().height / 2));
    cv::Mat scaledImg;
    cv::resize(img, scaledImg, cv::Size(), .3, .3);

    // Croping
    cv::Mat cropImg;
    cv::Rect roi(100, 100, 300, 250);
    cropImg = img(roi);

    cv::imshow("Resized Image", resizedImg);
    cv::imshow("Scaled Image", scaledImg);
    cv::imshow("Croped Image", cropImg);
    cv::waitKey(0);

    return 0;
}