#include "MainFrame.h"
#include "Source.h"	
#include "SVM.h"
#include <wx/wx.h>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <string>
#include <opencv4/opencv2/opencv.hpp>
#include <vector>
wxIMPLEMENT_APP(Source); //Start


bool Source::OnInit() {
    MainFrame* mainFrame = new MainFrame("Autentification");
    mainFrame->SetClientSize(800, 600);
    mainFrame->Show();
    return true;
}   
////include <wx/wx.h>
//dlib::full_object_detection faceLandmarkglobal;
//cv::Mat image3(254, 254, CV_8UC3, cv::Scalar(255, 255, 255));
//std::vector<std::vector<double>> intVectorArray;
//std::vector<long double> ratioPoint;
//std::vector<std::vector<double>> intVectorArray2;
//std::vector<double> ratioPoint2;
//
//double points( int x, int y)
//{
//    dlib::point pt;
//    dlib::point et;
//    pt = faceLandmarkglobal.part(x);
//
//    et = faceLandmarkglobal.part(y);
//    double distance = cv::norm(cv::Point(pt.x(), pt.y()) - cv::Point(et.x(), et.y()));
//    cv::line(image3, cv::Point(pt.x(), pt.y()), cv::Point(et.x(), et.y()), cv::Scalar(255, 0, 0), 2);
//    return distance;
//}
//    
//    
//
//int main() {
//    setlocale(LC_ALL, "ukr"); 
//    // ������������ ��������� �������
//    cv::Mat image1 = cv::imread("2\\aligned_detect_2.540.jpg"); //2\\aligned_detect_2.560.jpg//5\\aligned_detect_5.100.jpg
//    cv::Mat image2 = cv::imread("2\\aligned_detect_2.501.jpg");
//
//    // ������������� ��������� � ������ Dlib
    //dlib::cv_image<dlib::bgr_pixel> dlibImage1(image1);
    //dlib::cv_image<dlib::bgr_pixel> dlibImage2(image2);

    //// ��������� ������i �� ����������� (� ������������� ��������� Dlib)
    //dlib::frontal_face_detector faceDetector = dlib::get_frontal_face_detector();
    //dlib::shape_predictor shapePredictor;
    //dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> shapePredictor;

    //std::vector<dlib::rectangle> faceRects1 = faceDetector(dlibImage1);
    //std::vector<dlib::rectangle> faceRects2 = faceDetector(dlibImage2);

    //// ���� ������� �������
    //dlib::full_object_detection shape1 = shapePredictor(dlibImage1, faceRects1[0]);
    //dlib::full_object_detection shape2 = shapePredictor(dlibImage2, faceRects2[0]);

    //// ���� ����� � �������� ����� Dlib
    //std::vector<cv::Point2f> points1, points2;
    //for (int i = 0; i < shape1.num_parts(); i++) {
    //    points1.push_back(cv::Point2f(shape1.part(i).x(), shape1.part(i).y()));
    //    points2.push_back(cv::Point2f(shape2.part(i).x(), shape2.part(i).y()));
    //}

    //// ������ ������� ����������
    //cv::Mat homography = cv::findHomography(points1, points2, cv::RANSAC);

    //// ����������� ����������
    //cv::Mat aligned_image;
    //cv::warpPerspective(image1, aligned_image, homography, image2.size());

    //// ³���������� ����������
    //dlib::cv_image<dlib::bgr_pixel> dlibImage3(image2);
    //dlib::cv_image<dlib::bgr_pixel> dlibImage4(aligned_image);
    //std::vector<dlib::rectangle> faceRects3 = faceDetector(dlibImage3);
    //std::vector<dlib::rectangle> faceRects4 = faceDetector(dlibImage4);
    //dlib::full_object_detection faceLandmarks = shapePredictor(dlibImage3, faceRects3[0]);
    //dlib::point pt;
    //dlib::point et;
    //
    //    // ³���������� �������� ����� �� ����������
    //    for (unsigned int i = 0; i < faceLandmarks.num_parts(); ++i) {
    //        pt = faceLandmarks.part(i);
    //        cv::circle(image2, cv::Point(pt.x(), pt.y()), 1, cv::Scalar(0, 255, 0), -1);
    //      // cv::putText(image2, std::to_string(i   ), cv::Point(pt.x() + 5, pt.y() + 5), cv::FONT_HERSHEY_SIMPLEX, 0.2, cv::Scalar(255, 255, 255), 1);
    //    }
    //    faceLandmarkglobal = faceLandmarks;
    //    
    //    intVectorArray.push_back({ 39,42,points(39,42) }); intVectorArray.push_back({ 27,8,points(27,8) }); 
    //    intVectorArray.push_back({ 21,22,points(21,22) });intVectorArray.push_back({ 51,62,points(51,62) }); 
    //    intVectorArray.push_back({ 36,39,points(36,39) });intVectorArray.push_back({ 37,41,points(37,41) }); 
    //    intVectorArray.push_back({ 42,45,points(42,45) }); intVectorArray.push_back({ 43,47,points(43,47) }); 
    //    intVectorArray.push_back({ 48,54,points(48,54) }); intVectorArray.push_back({ 27,30,points(27,30) });
    //    int ai = 0;
    //   std::ofstream outputFile("D:\\cmake\\build\\x64\\Release\\output.txt");
    //    for (int k=0 ; k < intVectorArray.size();k+=2)
    //    {
    //            ratioPoint.push_back(intVectorArray[k][2] / intVectorArray[k + 1][2]);
    //        
    //       //outputFile << "distance(" << intVectorArray[k][0] << "," << intVectorArray[k][1] << ")=" << intVectorArray[k][2]  << ", distance(" << intVectorArray[k+1][0] << "," << intVectorArray[k+1][1] << ")=" << intVectorArray[k+1][2] << " ratio=" << ratioPoint[ai] << std::endl;
    //       outputFile << ratioPoint[ai] << std::endl;
    //       ai++;
    //    }
    //    outputFile << std::endl;
    //    cv::imshow("Vectors", image3);
    //    cv::waitKey(0);
    //    faceLandmarks = shapePredictor(dlibImage4, faceRects4[0]);

    //    // ³���������� �������� ����� �� ����������
    //    for (unsigned int i = 0; i < faceLandmarks.num_parts(); ++i) {
    //        pt = faceLandmarks.part(i);
    //        cv::circle(aligned_image, cv::Point(pt.x(), pt.y()), 1, cv::Scalar(0, 255, 0), -1);
    //        //cv::putText(aligned_image, std::to_string(i), cv::Point(pt.x() + 5, pt.y() + 5), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 255, 255), 1);
    //    }
    //    faceLandmarkglobal = faceLandmarks;
    //    intVectorArray2.push_back({ 39,42,points(39,42) }); intVectorArray2.push_back({ 27,8,points(27,8) });
    //    intVectorArray2.push_back({ 21,22,points(21,22) }); intVectorArray2.push_back({ 51,62,points(51,62) });
    //    intVectorArray2.push_back({ 36,39,points(36,39) }); intVectorArray2.push_back({ 37,41,points(37,41) });
    //    intVectorArray2.push_back({ 42,45,points(42,45) }); intVectorArray2.push_back({ 43,47,points(43,47) });
    //    intVectorArray2.push_back({ 48,54,points(48,54) }); intVectorArray2.push_back({ 27,30,points(27,30) });
    //    int ai2 = 0;
    //    std::ofstream outputFile2("D:\\cmake\\build\\x64\\Release\\output2.txt");
    //    for (int k = 0; k < intVectorArray2.size(); k += 2)
    //    {
    //        ratioPoint2.push_back(intVectorArray2[k][2] / intVectorArray2[k + 1][2]);

    //        //outputFile << "distance(" << intVectorArray[k][0] << "," << intVectorArray[k][1] << ")=" << intVectorArray[k][2]  << ", distance(" << intVectorArray[k+1][0] << "," << intVectorArray[k+1][1] << ")=" << intVectorArray[k+1][2] << " ratio=" << ratioPoint[ai] << std::endl;
    //        outputFile2 << ratioPoint2[ai2] << std::endl;
    //        ai2++;
    //    }
    //    outputFile2 << std::endl;
    //cv::imshow("Original Image", image2);
    //cv::imshow("Aligned Image", aligned_image);
    //cv::waitKey(0);
    //    //for (int k = 0; k < intVectorArray2.size(); k++)
    //    //{
    //    //    ratioPoint2.push_back(intVectorArray2[23][2] / intVectorArray2[k][2]);
    //    //    outputFile2 << "distance(" << intVectorArray2[k][0] << "," << intVectorArray2[k][1] << ")=" << intVectorArray2[k][2] << " ratio=" << ratioPoint2[k] << std::endl;
    //    //    //outputFile2 << ratioPoint2[k]<<std::endl;
    //    //}

    //    // ����²��� �� ²���²�Ͳ���
    //int count = 0;
    //    if (ratioPoint2[0] >= ratioPoint[0] * 0.9 && ratioPoint2[0] <= ratioPoint[0] * 1.1)
    //    {
    //        count++;
    //    }
    //    if (ratioPoint2[1] >= ratioPoint[1] * 0.7 && ratioPoint2[1] <= ratioPoint[1] * 1.3)
    //    {
    //        count++;
    //    }
    //    if (ratioPoint2[2] >= ratioPoint[2] * 0.85 && ratioPoint2[2] <= ratioPoint[2] * 1.15)
    //    {
    //        count++;
    //    }
    //    if (ratioPoint2[3] >= ratioPoint[3] * 0.85 && ratioPoint2[3] <= ratioPoint[3] * 1.15)
    //    {
    //        count++;
    //    }
    //    if (ratioPoint2[4] >= ratioPoint[4] * 0.9 && ratioPoint2[4] <= ratioPoint[4] * 1.1)
    //    {
    //        count++;
    //    }
    //if (count >= 4)
    //{
    //    std::cout << "�� ������� ��������i���i�" << std::endl;
    //}
    //else
    //    std::cout << "������ ��������i���i� �� ��������" << std::endl;
    //system("pause");
   /* cv::Mat image3(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::line(image3, start_point, end_point, color, 2);*/
    //    return 0;
    //}
