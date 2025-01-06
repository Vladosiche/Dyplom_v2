#pragma once
#include "MainFrame.h"
#include <wx/notebook.h>
#include "Source.h"	
#include <wx/wx.h>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <wx/grid.h>
#include <filesystem>
#include <string>
#include "SVM.h"




void Svm_hog::svm_hog_training(std::string path_true, std::string path_false)
{
    int j = 0;
    std::vector<cv::Mat> hogFeatures;
    std::vector<int> label;
    std::vector<float> liva_shtuka;
    std::string mat_path[2] = { path_true,path_false };
    for (std::string path : mat_path)
    {
        for (const auto& entry : std::filesystem::directory_iterator(path))
        {
           wxLogMessage("Це повідомлення для дебагу: %s", entry.path().string());
            img_face = cv::imread(entry.path().string());
            //entry.path().string()
            cv::imshow("Зображення", img_face);

            //  img_nonface = cv::imread("D:\\1\\DYPLOM_MAGA\\train_foto\\false" + std::to_string(j) + ".png");
            if (img_face.empty())
            {
                //std::cout << "Шось не так з зчитуванням фото";
                break;
            }
            /*hog_face =*/liva_shtuka=extractHOGFeatures(img_face);
            hog_face = cv::Mat(liva_shtuka).reshape(1,1);
            //  hog_nonface = extractHOGFeatures(img_nonface);
             // labels = (cv::Mat_<int>(2, 1) << 1, -1);
             // cv::Mat trainingData(2, static_cast<int>(hog_face.size()), CV_32F);

              //for (int i = 0; i < hog_face.size(); i++) {

              //    trainingData.at<float>(0, i) = hog_face[i];      // Позитивний зразок
              //    //trainingData.at<float>(1, i) = hog_nonface[i];   // Негативний зразок

              //}
            hogFeatures.push_back(hog_face);
            if (path == path_true)
            {
                label.push_back(1);// Позитивний зразок
            }
            else
                label.push_back(-1);// Негативний зразок

        }
    }
    cv::Mat trainingData(static_cast<int>(hogFeatures.size()), hogFeatures[0].cols, CV_32F);
    for (size_t i = 0; i < hogFeatures.size(); ++i) {
        trainingData.row(static_cast<int>(i)) = hogFeatures[i];
       // hogFeatures[i].copyTo(trainingData.row(static_cast<int>(i))); //туть не прокнуло
    }
   // cv::Mat labelsMat(label.size(), 1, CV_32S, label.data());


    cv::Mat labelsMat(label, true); // Перетворюємо вектор міток у матрицю
    svm->setType(cv::ml::SVM::C_SVC);
    svm->setKernel(cv::ml::SVM::LINEAR);
    svm->setC(1.0);
    svm->train(trainingData, cv::ml::ROW_SAMPLE, labelsMat);
    svm->save("G:\\vs_aplication\\ConsoleApplication3\\ConsoleApplication3\\train_foto\\model\\svm_model_tr.xml");
    /* cv::Mat test_img = cv::imread(path3, cv::IMREAD_GRAYSCALE);

     std::vector<float> hog_test = extractHOGFeatures(test_img);
     cv::Mat testMat(1, static_cast<int>(hog_test.size()), CV_32F);
     for (int i = 0; i < hog_test.size(); i++) {
         testMat.at<float>(0, i) = hog_test[i];
     }
     float prediction = svm->predict(testMat);
     if (prediction == 1) {
         wxMessageBox("Обличчя знайдено", "Заголовок вікна", wxOK | wxICON_INFORMATION);
     }
     else {
         wxMessageBox("Обличчя не знайдено", "Заголовок вікна", wxOK | wxICON_INFORMATION);
     }*/
    j++;
}
   void Svm_hog::svm_hog_predict(std::string path_foto, std::string path_model_xml)
   {
       if (path_model_xml !="")
       {
           svm->load(path_model_xml);
       }
       cv::Mat predict_img = cv::imread(path_foto);
       if (!predict_img.empty())
       {
           //std::cout << "Шось не так з зчитуванням фото";


           std::vector<float> hog_test = extractHOGFeatures(predict_img);
           cv::Mat testMat(1, static_cast<int>(hog_test.size()), CV_32F);
           for (int i = 0; i < hog_test.size(); i++) {
               testMat.at<float>(0, i) = hog_test[i];
           }
           float prediction = svm->predict(testMat);
           if (prediction == 1) {
               wxMessageBox("Обличчя знайдено", "Заголовок вікна", wxOK | wxICON_INFORMATION);
           }
           else {
               wxMessageBox("Обличчя не знайдено", "Заголовок вікна", wxOK | wxICON_INFORMATION);
           }
       }
   }
   void Svm_hog::svm_hog_find_face(std::string path_foto)
   {
       cv::Mat frame = cv::imread(path_foto);
       cv::CascadeClassifier face_cascade;
       face_cascade.load("G:\\vs_aplication\\ConsoleApplication3\\ConsoleApplication3\\train_foto\\haar_modelhaarcascade_frontalface_alt.xml");
       // Перетворення зображення в чорно-біле (опціонально для швидшої обробки)
       cv::Mat gray;
       cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

       // Знаходження облич у кадрі
       std::vector<cv::Rect> faces;
       face_cascade.detectMultiScale(
           gray,           // вхідне зображення
           faces,          // результат
           1.1,            // scaleFactor
           3,              // minNeighbors
           0,              // flags (deprecated)
           cv::Size(10, 10) // мінімальний розмір обличчя
       );

       cv::Mat croppedImage;
       // Малювання прямокутників навколо знайдених облич
       for (const auto& rect : faces) {
           cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
           if (faces.size() < 2)
           {
               croppedImage = frame(rect);
           }
       }


       // Відображення кадру
       cv::imshow("Детекція облич", croppedImage);
       cv::waitKey(0);
   }
   