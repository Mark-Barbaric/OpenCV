#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <ObjectDetection/Preprocessing.h>

//https://github.com/PacktPublishing/Building-Computer-Vision-Projects-with-OpenCV4-and-CPlusPlus/blob/master/Chapter05/main.cpp
constexpr auto imageFolder = "/Users/markbarbaric/Documents/Developer/CPP/OpenCV/CVProjectsWithOpenCV/Images/";

constexpr char* keys ={
                "{help h usage ? | | print this message}"
                "{@image || Image to process}"
                "{@lightPattern || Image light pattern to apply to image input}"
                "{lightMethod | 1 | Method to remove backgroun light, 0 differenec, 1 div, 2 no light removal' }"
                "{segMethod | 1 | Method to segment: 1 connected Components, 2 connectec components with stats, 3 find Contours }"
};

int main(int argc, char* argv[])
{
    cv::CommandLineParser parser(argc, argv, keys);
    cv::String imageFile;

    if(parser.has("help")){
        parser.printMessage();
        return 0;
    }

    imageFile = parser.get<cv::String>(0).empty() ? cv::String(imageFolder) + "lena.jpg" :
                parser.get<cv::String>(0);

    const auto image = cv::imread(imageFile, cv::IMREAD_GRAYSCALE);

    if(image.data == nullptr){
        std::cout << "Failed to load image.\n";
        return -1;
    }

    cv::imshow("Image Before" , image);

    const auto imageNoise = ObjectDetection::Preprocessing::removeNoise(imageFile);
    cv::imshow("Image Noise", imageNoise);

    cv::waitKey();

    return 0;
}