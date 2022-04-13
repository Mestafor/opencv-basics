#include <iostream>
#include <string>
#include <vector>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

int main(int argc, char** argv) {

    // Face detection

    cv::CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_default.xml");

    if (faceCascade.empty()) {
        std::cout << "XML file not loaded" << std::endl;
        return 1;
    }

    // // IMAGES from path
    // std::string path = "Resources/test.jpg";
    // cv::Mat img = cv::imread(path);
    // std::vector<cv::Rect> faces;
    // faceCascade.detectMultiScale(img, faces, 1.1, 4);
    // for(auto face: faces) {
    //     cv::rectangle(img, {face.tl(), face.br()}, cv::Scalar(255, 0, 255), 2);
    // }
    // cv::imshow("Image", img);
    // cv::waitKey(0);

    // WebCam
    cv::VideoCapture cap(0);
    cv::Mat img;
    while(true) {
        cap.read(img);

        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(img, faces, 1.1, 4);
        for(auto face: faces) {
            cv::rectangle(img, {face.tl(), face.br()}, cv::Scalar(255, 0, 255), 2);
        }

        cv::imshow("Image", img);
        cv::waitKey(1);
    }

    return 0;
}