#include <iostream>
#include <string>
#include <vector>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

int blurSize = 5;

int canny_threshold1 = 5;
int canny_threshold2 = 72;


int morph_rect_size = 25;
int min_size = 700;

void createTrackBar() {
    cv::namedWindow("Trackbars", (640, 100));
    
    cv::createTrackbar("Blur 1", "Trackbars", &blurSize, 100);
    
    cv::createTrackbar("canny1_threshold1", "Trackbars", &canny_threshold1, 100);
    cv::createTrackbar("canny1_threshold2", "Trackbars", &canny_threshold2, 200);

    cv::createTrackbar("morph_rect_size", "Trackbars", &morph_rect_size, 200);
    cv::createTrackbar("min_size", "Trackbars", &min_size, 20000);
}

int main(int argc, char** argv) {

    // motion detection
    createTrackBar();

    // cv::VideoCapture cap("Resources/motion.mp4");
    cv::VideoCapture cap(0);
    cv::Mat img1, img2;

    cap.read(img1);

    while(cap.isOpened() && cap.read(img2)) {

        cv::Mat diff;
        cv::absdiff(img2, img1, diff);

        cv::Mat gray;
        cv::cvtColor(diff, gray, cv::COLOR_BGR2GRAY);
        
        cv::Mat blur;
        int normilizer1 = blurSize % 2 == 0 ? 1 : 0;
        cv::GaussianBlur(gray, blur, cv::Size(blurSize + normilizer1, blurSize + normilizer1), 0, 0);

        cv::Mat canny;
        cv::Canny(blur, canny, canny_threshold1, canny_threshold2);

        cv::Mat dilate;
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(morph_rect_size + 1, morph_rect_size + 1));
        cv::dilate(canny, dilate, kernel);

        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(dilate, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);

        cv::Mat result = img2.clone();


        cv::drawContours(result, contours, -1, cv::Scalar(0,255,0), 1);
        // for(auto contour: contours) {
        //     auto rect = cv::boundingRect(contour);

        //     if(rect.area() < min_size) continue;

        //     cv::rectangle(result, rect, cv::Scalar(0, 255, 0), 1);
        // }

        // cv::imshow("Diff", diff);
        // cv::imshow("Gray", gray);
        // cv::imshow("Blur", blur);
        // cv::imshow("Canny", canny);
        cv::imshow("Result", result);

        img1 = img2.clone();

        if (cv::waitKey(30) == 27) {
            return 0;
        }
        
    }

    return 0;
}