#pragma once
//                  Header
#include "Source.h"	
#include "SVM.h"

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

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);
    void OnButtonClicked2(wxCommandEvent& evt);
    void OnButtonClicked3(wxCommandEvent& evt);
    void OnButtonClicked(wxCommandEvent& evt);
    void OnButtonClicked5(wxCommandEvent& evt);
    void UpdatePanel2();
    void UpdatePanel3();
    void UpdatePanel4();
    void UpdatePanel3_Text();
    double points(int x, int y, int c1, int c2, int c3);
    void UpdatePanel4_Text1(long double b, int g, int land1, int land2);
    void UpdatePanel4_Text2(long double b, int g);
    void UpdatePanel4_Text3(int g);
    void UpdatePanel4_CheckBox(int g,int g2, bool complite);
    void points11(int x, int y, int c1, int c2, int c3, int g);
    std::string image_to_matrix(std::string im_path, std::vector<std::vector<int>>& matrix_pixels, wxTextCtrl* text);
   // Svm_hog* svm_hog_p = &my_hog;
    wxStaticBitmap* staticBitmap;
    wxStaticBitmap* staticBitmap1;
    wxStaticBitmap* staticBitmap2;
    wxTextCtrl* textCtrl1;
    wxTextCtrl* textCtrl2;
    wxTextCtrl* textCtrl3;
    wxTextCtrl* textCtrl4;
    wxTextCtrl* textCtrl5;
    wxTextCtrl* textCtrl6;
    wxTextCtrl* textCtrl7;
    wxTextCtrl* textCtrl8;
    wxTextCtrl* textCtrl9;
    wxTextCtrl* textCtrl10;
    wxTextCtrl* textCtrl11;
    wxTextCtrl* textCtrl12;
    wxTextCtrl* textCtrl13;
    wxTextCtrl* textCtrl14;
    wxTextCtrl* textCtrl15;
    wxTextCtrl* textCtrl16;
    wxCheckBox* checkBox1;
    wxCheckBox* checkBox2;
    wxCheckBox* checkBox3;
    wxCheckBox* checkBox4;
    wxCheckBox* checkBox5;
    wxStaticText* Text7;
    wxStaticText* Text10;
    wxImage image;
    wxPanel* panel1;
    wxPanel* panel2;
    wxPanel* panel3;
    wxPanel* panel4;
    wxPanel* panel5;
    wxGrid* grid;
    wxGrid* grid2;
    cv::Mat image1;
    cv::Mat image2;
    cv::Mat image4;
    cv::Mat imageun;
    wxGridCellAttr* attrred;
    wxGridCellAttr* attrgreen;
    cv::Mat image5;
    cv::Mat image6;
    cv::Mat image7;
    wxString imagePath7;
    wxButton* button4;
    wxButton* button5;
    wxButton* button6;
    wxCheckBox* checkbox;
    wxCheckBox* checkbox1;
    wxCheckBox* checkbox2;
    wxCheckBox* checkbox3;
    wxCheckBox* checkbox4;
    wxCheckBox* checkbox5;
    wxCheckBox* checkbox6;
    wxCheckBox* checkbox7;
    wxCheckBox* checkbox8;
    wxCheckBox* checkbox9;
    wxCheckBox* checkbox10;
    wxCheckBox* checkbox11;
};
//class MyFaceDetector : public dlib::object_detector<dlib::scan_fhog_pyramid<dlib::pyramid_down<6>>>
//{
//public:
//    dlib::matrix<float> compute_descriptor(std::vector<std::vector<int>>& matrix_pixels) const
//    {
//        // Реалізація обчислення дескриптора на основі MI
//        sobel_filter(matrix_pixels);
//        return;
//    }
//};
