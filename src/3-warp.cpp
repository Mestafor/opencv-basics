#include <iostream>
#include <string>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {

    // Warp perspective

    float w = 250;
    float h = w * 1.4f;

    // IMAGES from path
    std::string path = "Resources/cards.jpg";
    cv::Mat img = cv::imread(path);
    
    cv::Point2f mineSrc[4] = { {738, 383}, {1028, 436}, {644, 709}, {971, 783} };
    cv::Point2f dest[4] = { {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };

    cv::Point2f kingSrc[4] = { {529, 142}, {771, 190}, {405, 395}, {674, 457} };
    cv::Mat kingMatrix = cv::getPerspectiveTransform(kingSrc, dest);
    cv::Mat imgKing;
    cv::warpPerspective(img, imgKing, kingMatrix, cv::Point(w, h));
    
    cv::Point2f queenSrc[4] = { {61, 322}, {341, 278}, {96, 634}, {405, 574} };
    cv::Mat queenMatrix = cv::getPerspectiveTransform(queenSrc, dest);
    cv::Mat queenKing;
    cv::warpPerspective(img, queenKing, queenMatrix, cv::Point(w, h));

    cv::Point2f jalletSrc[4] = { {774, 105}, {1021, 82}, {841, 360}, {1117, 333} };
    cv::Mat jalletMatrix = cv::getPerspectiveTransform(jalletSrc, dest);
    cv::Mat jalletKing;
    cv::warpPerspective(img, jalletKing, jalletMatrix, cv::Point(w, h));

    cv::Point2f nineSrc[4] = { {738, 383}, {1028, 436}, {644, 709}, {971, 783} };
    cv::Mat nineMatrix = cv::getPerspectiveTransform(nineSrc, dest);
    cv::Mat nineKing;
    cv::warpPerspective(img, nineKing, nineMatrix, cv::Point(w, h));

    cv::imshow("Image", img);
    cv::imshow("Image King", imgKing);
    cv::imshow("Image Queen", queenKing);
    cv::imshow("Image Jallet", jalletKing);
    cv::imshow("Image Nine", nineKing);
    cv::waitKey(0);

    return 0;
}