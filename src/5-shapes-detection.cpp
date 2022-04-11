#include <iostream>
#include <string>
#include <vector>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

void getContours(cv::Mat dilImg, cv::Mat img) {

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(dilImg, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> filteredContours;
    std::copy_if(contours.begin(), contours.end(), std::back_inserter(filteredContours), [](auto contour) { 
        int area = cv::contourArea(contour);
        return area > 1000; 
    });
    // cv::drawContours(img, filteredContours, -1, cv::Scalar(255, 0, 255), 2);


    std::vector<std::vector<cv::Point>> conPoly{filteredContours.size()};
    std::vector<cv::Rect> boundRect{conPoly.size()};
    for(int i = 0; i < filteredContours.size(); i++) {
        auto contour = filteredContours[i];
        float peri = cv::arcLength(contour, true);
        cv::approxPolyDP(contour, conPoly[i], 0.02*peri, true);

        int area = cv::contourArea(contour);
        std::cout << area << std::endl;
        std::cout << conPoly[i].size() << std::endl;

        boundRect[i] = cv::boundingRect(conPoly[i]);
        std::cout << boundRect[i].size() << std::endl;
        cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 3);

        int objCor = (int)conPoly[i].size();
        std::string objType;
        if(objCor == 3) {
            objType = "Tri";
        } else if(objCor == 4) {
            float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
            if(aspRatio > 0.96 && aspRatio < 1.05) {
                objType = "Square";
            } else {
                objType = "Rect";
            }
        } else {
            objType = "Circle";
        }

        cv::putText(img, objType, { boundRect[i].x, boundRect[i].y - 5 }, cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar(0, 0, 255), 1, 1);
    }
    cv::drawContours(img, conPoly, -1, cv::Scalar(255, 0, 255), 2);
}

int main(int argc, char** argv) {

    // Shapes detection

    // IMAGES from path
    std::string path = "Resources/shapes.png";
    cv::Mat img = cv::imread(path);

    // Basic functions
    cv::Mat grayImg; // gray
    cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);
    cv::Mat blurImg; // Blur
    cv::GaussianBlur(grayImg, blurImg, cv::Size(3, 3), 5, 0);
    cv::Mat cannyImg; // Canny
    cv::Canny(blurImg, cannyImg, 15, 75);

    cv::Mat dilateImg;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(cannyImg, dilateImg, kernel);

    getContours(dilateImg, img);

    cv::imshow("Image", img);
    // cv::imshow("Grey Image", grayImg);
    // cv::imshow("Blur Image", blurImg);
    // cv::imshow("Canny Image", cannyImg);
    // cv::imshow("Dilate Image", dilateImg);
    cv::waitKey(0);

    return 0;
}