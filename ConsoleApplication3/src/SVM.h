#pragma once
//                  Header
#include "MainFrame.h"
#include "Source.h"	


//                  WX_Widget
#include <wx/notebook.h>
#include <wx/wx.h>
#include <wx/grid.h>

//                  Dlib
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>

//                  Open_CV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

//                  System
#include <string>
#include <vector>
#include <filesystem>


class Svm_hog
{
public:
    Svm_hog(std::string path_model_def="G:\\vs_aplication\\ConsoleApplication3\\ConsoleApplication3\\train_foto\\model\\svm_model.xml")
    {
        //svm->setType(cv::ml::SVM::C_SVC);        // Тип класифікації
        //svm->setKernel(cv::ml::SVM::LINEAR);     // Лінійне ядро
       // svm->create();
        svm->load(path_model_def);
    }
    void svm_hog_training(std::string path_true, std::string path_false);
    cv::Mat img_face;
    cv::Mat img_nonface;
    cv::HOGDescriptor* hog = new cv::HOGDescriptor();
    std::string path_mod;
    cv::Mat hog_face;
    cv::Mat hog_nonface;
    cv::Ptr<cv::ml::SVM> svm;
    cv::Mat labels;
    std::vector<float> descriptors;
    std::vector<float> extractHOGFeatures(const cv::Mat& img) {
        //cv::HOGDescriptor hog(
        //    cv::Size(50, 50), // Розмір вікна
        //    cv::Size(25, 25),  // Блок
        //    cv::Size(5, 5),    // Крок блоку
        //    cv::Size(5, 5),    // Крок комірки
        //    9                  // Кількість бінів
       // );
        cv::Mat resizedImg;
        cv::Mat grayImg;
        cv::resize(img, resizedImg, cv::Size(250, 250));
        cv::cvtColor(resizedImg, grayImg, cv::COLOR_BGR2GRAY);
   
        if (grayImg.type() != CV_8U) {
            grayImg.convertTo(grayImg, CV_8U);
        }

        hog->compute(grayImg, descriptors);
        return descriptors;
    }   
    void svm_hog_predict(std::string path_foto,std::string path_model_xml="");
    void svm_hog_find_face(std::string path_foto);
    ~Svm_hog()
    {
        delete hog;
        std::cout << "Бляха, а де SVM?";
    }
};
