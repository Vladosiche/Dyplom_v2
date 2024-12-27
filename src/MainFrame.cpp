#include "MainFrame.h"
#include <wx/notebook.h>
#include "Source.h"	
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
#include <wx/grid.h>
#include <string>
#include <wx/generic/statbmpg.h>
#include <math.h>
#include <filesystem>
#include "SVM.h"
enum {
    BUTTON_ID = 2,
    BUTTON_ID2 = 3,
    BUTTON_ID3 = 4,
    BUTTON_ID4 = 5,
    BUTTON_ID5 = 6
};
std::ofstream outputFile3("D:\\cmake\\build\\x64\\Release\\output3.txt");
dlib::full_object_detection faceLandmarkglobal;
cv::Mat image3(300, 414, CV_8UC3, cv::Scalar(255, 255, 255));
std::vector<std::vector<double>> intVectorArray;
std::vector<long double> ratioPoint;
std::vector<std::vector<double>> intVectorArray2;
std::vector<double> ratioPoint2;
Svm_hog my_hog;


double MainFrame::points(int x, int y, int c1, int c2, int c3)
{
    dlib::point pt;
    dlib::point et;
    pt = faceLandmarkglobal.part(x);

    et = faceLandmarkglobal.part(y);
    outputFile3 << pt << " " << et << std::endl;
    double distance = cv::norm(cv::Point(pt.x(), pt.y()) - cv::Point(et.x(), et.y()));
    //cv::line(image3, cv::Point(pt.x()/(image1.cols/300.f), pt.y() / (image1.rows / 300.f)), cv::Point(et.x() / (image1.cols / 300.f), et.y() / (image1.rows / 300.f)), cv::Scalar(c1, c2, c3), 2);
    return distance;
}
void MainFrame::points11(int x, int y, int c1, int c2, int c3, int g)
{
    dlib::point pt;
    dlib::point et;
    int col = 0;
    int row = 0;
    pt = faceLandmarkglobal.part(x);
    et = faceLandmarkglobal.part(y);
    switch (g)
    {
    case 1:
        cv::line(image4, cv::Point(pt.x() / (image1.cols / 150.f), pt.y() / (image1.rows / 150.f)), cv::Point(et.x() / (image1.cols / 150.f), et.y() / (image1.rows / 150.f)), cv::Scalar(c1, c2, c3), 2);
        break;
    case 2:
        cv::line(image5, cv::Point(pt.x() / (imageun.cols / 150.f), pt.y() / (imageun.rows / 150.f)), cv::Point(et.x() / (imageun.cols / 150.f), et.y() / (imageun.rows / 150.f)), cv::Scalar(c1, c2, c3), 2);
        break;
    case 3:
        cv::line(image6, cv::Point(pt.x() / (imageun.cols / 150.f), pt.y() / (imageun.rows / 150.f)), cv::Point(et.x() / (imageun.cols / 150.f), et.y() / (imageun.rows / 150.f)), cv::Scalar(c1, c2, c3), 2);
        break;
    }
}
std::string MainFrame::image_to_matrix(std::string im_path, std::vector<std::vector<int>>& matrix_pixels, wxTextCtrl* text)
{
    cv::Mat image = cv::imread(im_path);
    std::cout << "Розміри зображення: " << image.rows << "x" << image.cols << std::endl;
    std::cout << "Кількість каналів: " << image.channels() << std::endl;
    std::cout << "Загальний розмір в байтах: " << image.total() * image.elemSize() << std::endl;
    cv::Mat grayImage;
    cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    std::vector<int> buf; \
    int d = 0, dd=0;
    for (int x = 0; x < grayImage.rows; x++)
    {
        if ((x == 0 || x == grayImage.rows - 1)&& d<=1)
        {
            for (int y = 0; y < grayImage.cols; y++)
            {
                if ((y == 0 || y == grayImage.cols - 1) && dd == 0)
                {
                    buf.push_back(grayImage.at<uchar>(x, y));
                    dd++;
                }

                buf.push_back(grayImage.at<uchar>(x, y));
                dd = 0;
            }

            matrix_pixels.push_back(buf);
            buf.clear();
            d++;
        }

        for (int y = 0; y < grayImage.cols; y++)
        {
            if ((y == 0 || y == grayImage.cols - 1) && dd == 0)
            {
                buf.push_back(grayImage.at<uchar>(x, y));
                dd++;
            }

            buf.push_back(grayImage.at<uchar>(x, y));
            dd = 0;
        }

        matrix_pixels.push_back(buf);
        buf.clear();
        d = 0;
        
    }
    std::string buf_text = "";
    
   /* {
        using namespace std;
        for (int i = 0; i < matrix_pixels.size();i++)
        {
            for (int t = 0; t < matrix_pixels[i].size()*0.8; t++)
            {
              text->AppendText(std::to_string(matrix_pixels[i][t])+" ");
            }
            text->AppendText("\n");
        }
      
    }*/
    return buf_text;
    //rayImage.at<uchar>(y, x);
}
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    wxNotebook* notebook = new wxNotebook(this, wxID_ANY);
    //svm_hog_p = &my_hog;
    wxString imagePath = "D:\\_G_Cyb.png";
    wxString imagePath2 = "D:\\_G_Cyb.png";
    // Створення першої вкладки
    panel1 = new wxPanel(notebook, wxID_ANY);
    wxStaticText* Text1 = new wxStaticText(panel1, wxID_ANY, "Для проходження автентифікації необхідно:\n 1.Обрати фото еталону кнопкою \" Вибрати фото еталону\" \n 2. Обрати фото кандидату за яким буде проходити автнетифікацію, кнопка \"Вибрати фото кандидату\"\n 3. Натиснути кнопку \"Підтвердити ввід данних\"", wxPoint(400, 20), wxSize(350, 380), wxALIGN_LEFT);
    wxBoxSizer* sizer1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer3 = new wxBoxSizer(wxHORIZONTAL);
    wxButton* button = new wxButton(panel1, BUTTON_ID, "Вибрати фото еталону", wxPoint(20, 20));
    wxButton* button2 = new wxButton(panel1, BUTTON_ID2, "Вибрати фото кандидату", wxPoint(200, 20));
    wxButton* button3 = new wxButton(panel1, BUTTON_ID3, "Підтвердити ввід данних", wxPoint(100, 400));
    textCtrl1 = new wxTextCtrl(panel1, wxID_ANY, "", wxPoint(190, 60), wxSize(170, 80), wxTE_MULTILINE);
    textCtrl2 = new wxTextCtrl(panel1, wxID_ANY, "", wxPoint(10, 60), wxSize(170, 80), wxTE_MULTILINE);
    button->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
    button2->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked2, this);
    button3->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked3, this);
    panel1->SetSizer(sizer1);
    notebook->AddPage(panel1, "Вибір файлів");
    // Створення другої вкладки
    panel2 = new wxPanel(notebook, wxID_ANY);
    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* Text2 = new wxStaticText(panel2, wxID_ANY, "Фото еталону та фото кандидату зі знайденими ключовими точками на обличчі", wxPoint(120, 20));
    wxFont font = Text2->GetFont();
    font.SetPointSize(12);
    Text2->SetFont(font);
    wxStaticText* Text3 = new wxStaticText(panel2, wxID_ANY, "Фото еталону за яким проводилась нормалізація", wxPoint(30, 450));
    wxStaticText* Text4 = new wxStaticText(panel2, wxID_ANY, "Фото кандидату із проведеною нормалізацію", wxPoint(460, 450));
    panel2->SetSizer(sizer2);
    notebook->AddPage(panel2, "Нормалізація та знаходження ключових точок");
    // Створення третьої вкладки
    panel3 = new wxPanel(notebook, wxID_ANY);
    wxBoxSizer* sizer4 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* Text6 = new wxStaticText(panel3, wxID_ANY, "Таблця відстаней між точками між точками", wxPoint(350, 20));
    grid = new wxGrid(panel3, wxID_ANY, wxPoint(350, 60), wxSize(400, 400));
    grid->CreateGrid(10, 3); // Створення таблиці з 10 рядками і 3 стовпцями
    grid->SetColLabelValue(0, "Назва відрізку");
    grid->SetColLabelValue(1, "Довжина для еталону");
    grid->SetColLabelValue(2, "Довжина для кандидата");
    grid->SetColSize(0, 95);
    grid->SetColSize(1, 130);
    grid->SetColSize(2, 150);
    //textCtrl3 = new wxTextCtrl(panel3, wxID_ANY, "", wxPoint(350, 60), wxSize(400,400), wxTE_MULTILINE);
    panel3->SetSizer(sizer4);
    notebook->AddPage(panel3, "Формування відрізків");
    image3 = cv::imread(imagePath2.ToStdString());
    cv::cvtColor(image3, image3, cv::COLOR_BGR2RGB);
    cv::resize(image3, image3, cv::Size(300, 414));
    //wxImage wximg(image3.cols, image3.rows, image3.data, true);
    //wxBitmap bitmap(wximg);
    //staticBitmap = new wxStaticBitmap(panel3, wxID_ANY, bitmap, wxPoint(190, 200));
  // Створення четвертої вкладки
    panel4 = new wxPanel(notebook, wxID_ANY);
    wxBoxSizer* sizer5 = new wxBoxSizer(wxHORIZONTAL);
    wxPanel* panel1k = new wxPanel(panel4, wxID_ANY);
    image4 = cv::imread(imagePath.ToStdString());
    cv::cvtColor(image4, image4, cv::COLOR_BGR2RGB);
    cv::resize(image4, image4, cv::Size(150, 150));
    wxImage wximg2(image4.cols, image4.rows, image4.data, true);
    wxBitmap bitmap2(wximg2);
    staticBitmap = new wxStaticBitmap(panel1k, wxID_ANY, bitmap2, wxPoint(10, 20));
    wxStaticText* Text7 = new wxStaticText(panel4, wxID_ANY, "������", wxPoint(60, 200));

    image5 = cv::imread(imagePath.ToStdString());
    cv::cvtColor(image5, image5, cv::COLOR_BGR2RGB);
    cv::resize(image5, image5, cv::Size(150, 150));
    wxImage wximg3(image5.cols, image5.rows, image5.data, true);
    wxBitmap bitmap3(wximg3);
    staticBitmap = new wxStaticBitmap(panel1k, wxID_ANY, bitmap3, wxPoint(200, 20));
    wxStaticText* Text8 = new wxStaticText(panel4, wxID_ANY, "�ϲ���Ĳ���", wxPoint(225, 200));

    image6 = cv::imread(imagePath.ToStdString());
    cv::cvtColor(image6, image6, cv::COLOR_BGR2RGB);
    cv::resize(image6, image6, cv::Size(150, 150));
    wxImage wximg4(image6.cols, image6.rows, image6.data, true);
    wxBitmap bitmap4(wximg4);
    staticBitmap = new wxStaticBitmap(panel1k, wxID_ANY, bitmap4, wxPoint(390, 20));
    wxStaticText* Text9 = new wxStaticText(panel4, wxID_ANY, "��������", wxPoint(435, 200));

    grid2 = new wxGrid(panel4, wxID_ANY, wxPoint(10, 300), wxSize(750, 400));
    grid2->CreateGrid(5, 5); // Створення таблиці з 6 рядками і 5 стовпцями
    grid2->SetColLabelValue(0, "Назва співвідношення");
    grid2->SetColLabelValue(1, "Знач. для еталону");
    grid2->SetColLabelValue(2, "Знач. для кандидата");
    grid2->SetColLabelValue(3, "Допустиме відхилення");
    grid2->SetColLabelValue(4, "Співпадіння");
    grid2->HideRowLabels();
    grid->HideRowLabels();
    panel4->SetSizer(sizer5);
    notebook->AddPage(panel4, "Порівняння співвідношень");
    //три зображення обличчя посередині якого намальовані співпадіння і математичні формули можливо с чекбоксами
  // Додавання вкладок до головного вікна
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(notebook, 1, wxEXPAND);
    SetSizerAndFit(mainSizer);

    panel5 = new wxPanel(notebook, wxID_ANY);
    panel5->SetSizer(sizer1);
    notebook->AddPage(panel5, "Налаштування ідентифікації");
    wxStaticText* Text10 = new wxStaticText(panel5, wxID_ANY, "Оберіть кількість розподілень, та зображення", wxPoint(20, 20), wxSize(100, 20), wxALIGN_LEFT);
    button4 = new wxButton(panel5, BUTTON_ID, "Вибрати фото еталону", wxPoint(20, 40), wxSize(200, 20));
    button4->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked3, this);  //УВАГА ТУТ БІНД НА ЛІВУ КНОПКУ
    checkbox = new wxCheckBox(
        panel5,              // Батьківське вікно
        wxID_ANY,          // ID
        "Усі",  // Надпис біля чекбоксу
        wxPoint(20, 60)    // Позиція
    );
    checkbox1 = new wxCheckBox(
        panel5,              // Батьківське вікно
        wxID_ANY,          // ID
        "2x2",  // Надпис біля чекбоксу
        wxPoint(100, 60)    // Позиція
    );
    checkbox2 = new wxCheckBox(
        panel5,              // Батьківське вікно
        wxID_ANY,          // ID
        "4x4",  // Надпис біля чекбоксу
        wxPoint(180, 60)    // Позиція
    );
    checkbox3 = new wxCheckBox(
        panel5,              // Батьківське вікно
        wxID_ANY,          // ID
        "8x8",  // Надпис біля чекбоксу
        wxPoint(260, 60)    // Позиція
    );
    checkbox4 = new wxCheckBox(
        panel5,              // Батьківське вікно
        wxID_ANY,          // ID
        "16x16",  // Надпис біля чекбоксу
        wxPoint(20, 100)    // Позиція
    );
    checkbox5 = new wxCheckBox(
        panel5,              // Батьківське вікно
        wxID_ANY,          // ID
        "32x32",  // Надпис біля чекбоксу
        wxPoint(100, 100)    // Позиція
    );
    checkbox6 = new wxCheckBox(
        panel5,              // Батьківське вікно
        wxID_ANY,          // ID
        "64x64",  // Надпис біля чекбоксу
        wxPoint(180, 100)    // Позиція
    );
    checkbox7 = new wxCheckBox(
        panel5,              // Батьківське вікно
        wxID_ANY,          // ID
        "128x128",  // Надпис біля чекбоксу
        wxPoint(260, 100)    // Позиція
    );
    checkbox8 = new wxCheckBox(
        panel5,              // Батьківське вікно
        wxID_ANY,          // ID
        "256x256",  // Надпис біля чекбоксу
        wxPoint(20, 140)    // Позиція
    );
    checkbox9 = new wxCheckBox(
        panel5,              // Батьківське вікно
        wxID_ANY,          // ID
        "512x512",  // Надпис біля чекбоксу
        wxPoint(100, 140)    // Позиція
    );
    checkbox10 = new wxCheckBox(
        panel5,              // Батьківське вікно
        wxID_ANY,          // ID
        "1024x1024",  // Надпис біля чекбоксу
        wxPoint(180, 140)    // Позиція
    );
    checkbox11 = new wxCheckBox(
        panel5,              // Батьківське вікно
        wxID_ANY,          // ID
        "2048x2048",  // Надпис біля чекбоксу
        wxPoint(260, 140)    // Позиція
    );
        
    imagePath7 = "C:\\Users\\Windows\\source\\DYPLOM_MAGA_ON_VS\\DYPLOM_MAGA_ON_VS\\default.png";
    image7 = cv::imread(imagePath7.ToStdString());
    wxImage wximg5(image7.cols, image7.rows, image7.data, true);
    wxBitmap bitmap5(wximg5);
  
    wxGenericStaticBitmap* imageCtrl = new wxGenericStaticBitmap(
        panel5,              // Батьківське вікно
        wxID_ANY,          // ID
        bitmap5,            // Зображення
        wxPoint(20, 200)  // Позиція
    );
    wxBitmap bitmap6(wximg5);

    wxGenericStaticBitmap* imageCtrl2 = new wxGenericStaticBitmap(
        panel5,              // Батьківське вікно
        wxID_ANY,          // ID
        bitmap6,            // Зображення
        wxPoint(420, 200)  // Позиція
    );

   button5 = new wxButton(panel5, BUTTON_ID4, "порівняти", wxPoint(345, 200), wxSize(50, 20));
   button5->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked5, this);
   button6 = new wxButton(panel5, BUTTON_ID5, "Навчити модель", wxPoint(385, 200), wxSize(50, 20));
   std::vector <std::vector<int>> matrix;

  //wxFont font2(6, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
  //textCtrl16= new wxTextCtrl(panel5, wxID_ANY, "", wxPoint(20, 20), wxSize(1300, 600), wxTE_MULTILINE | wxHSCROLL | wxTE_DONTWRAP);
  //textCtrl16->SetFont(font2);
  //image_to_matrix(imagePath7.ToStdString(), matrix, textCtrl16);
   // button5->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);

}
void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
    int id = evt.GetId();
    if (id == BUTTON_ID) {
        wxFileDialog fileDialog(this, "Виберіть файл", "", "", "Усі файли (*.*)|*.*", wxFD_OPEN);
        if (fileDialog.ShowModal() == wxID_OK) {
            wxString filePath = fileDialog.GetPath();
            textCtrl2->SetValue(filePath);
            cv::Mat image11 = cv::imread(filePath.ToStdString());
            cv::cvtColor(image11, image11, cv::COLOR_BGR2RGB);
            image1 = image11;
            imageun = image11;
            cv::resize(image11, image11, cv::Size(150, 150));
            wxImage wximg(image11.cols, image11.rows, image11.data, true);
            wxBitmap bitmap(wximg);
            staticBitmap1 = new wxStaticBitmap(panel1, wxID_ANY, bitmap, wxPoint(10, 200));
        }

    }
    // Обробка вибраного файлу
}
void MainFrame::OnButtonClicked2(wxCommandEvent& evt) {
    int id2 = evt.GetId();
    if (id2 == BUTTON_ID2) {
        wxFileDialog fileDialog2(this, "Виберіть файл", "", "", "Усі файли (*.*)|*.*", wxFD_OPEN);
        if (fileDialog2.ShowModal() == wxID_OK) {
            wxString filePath2 = fileDialog2.GetPath();
            textCtrl1->SetValue(filePath2);
            cv::Mat image22 = cv::imread(filePath2.ToStdString());
            cv::cvtColor(image22, image22, cv::COLOR_BGR2RGB);
            image2 = image22;
            cv::resize(image22, image22, cv::Size(150, 150));
            wxImage wximg(image22.cols, image22.rows, image22.data, true);
            wxBitmap bitmap(wximg);
            staticBitmap2 = new wxStaticBitmap(panel1, wxID_ANY, bitmap, wxPoint(190, 200));
        }
        // Обробка вибраного файлу
    }
}
void MainFrame::UpdatePanel2()
{
    cv::cvtColor(image1, image1, cv::COLOR_BGR2RGB);
    cv::cvtColor(image2, image2, cv::COLOR_BGR2RGB);
    cv::resize(image1, image1, cv::Size(300, 300));
    wxImage wximg(image1.cols, image1.rows, image1.data, true);
    wxBitmap bitmap(wximg);
    staticBitmap = new wxStaticBitmap(panel2, wxID_ANY, bitmap, wxPoint(20, 100));
    cv::resize(image2, image2, cv::Size(300, 300));
    wxImage wximg2(image2.cols, image2.rows, image2.data, true);
    wxBitmap bitmap2(wximg2);
    staticBitmap = new wxStaticBitmap(panel2, wxID_ANY, bitmap2, wxPoint(450, 100));
}
void MainFrame::UpdatePanel3()
{
    cv::resize(image3, image3, cv::Size(300, 414));
    wxImage wximg(image3.cols, image3.rows, image3.data, true);
    wxBitmap bitmap(wximg);
    staticBitmap = new wxStaticBitmap(panel3, wxID_ANY, bitmap, wxPoint(20, 100));
}

void MainFrame::UpdatePanel3_Text()
{
    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            switch (col)
            {
            case 0:
                grid->SetCellValue(row, col, wxString::Format("L%d", row + 1));
                break;
            case 1:
                grid->SetCellValue(row, col, std::to_string(intVectorArray[row][2]));
                break;
            case 2:
                grid->SetCellValue(row, col, std::to_string(intVectorArray2[row][2]));
                break;
            }
        }
    }

}
void MainFrame::UpdatePanel4() {
    cv::cvtColor(image4, image4, cv::COLOR_BGR2RGB);
    cv::resize(image4, image4, cv::Size(150, 150));
    wxImage wximg2(image4.cols, image4.rows, image4.data, true);
    wxBitmap bitmap2(wximg2);
    staticBitmap = new wxStaticBitmap(panel4, wxID_ANY, bitmap2, wxPoint(10, 20));

    cv::cvtColor(image5, image5, cv::COLOR_BGR2RGB);
    cv::resize(image5, image5, cv::Size(150, 150));
    wxImage wximg3(image5.cols, image5.rows, image5.data, true);
    wxBitmap bitmap3(wximg3);
    staticBitmap = new wxStaticBitmap(panel4, wxID_ANY, bitmap3, wxPoint(200, 20));

    cv::cvtColor(image6, image6, cv::COLOR_BGR2RGB);
    cv::resize(image6, image6, cv::Size(150, 150));
    wxImage wximg4(image6.cols, image6.rows, image6.data, true);
    wxBitmap bitmap4(wximg4);
    staticBitmap = new wxStaticBitmap(panel4, wxID_ANY, bitmap4, wxPoint(390, 20));
}
void MainFrame::UpdatePanel4_Text1(long double b, int g)
{

    grid2->SetCellValue(0, 3, "10%");
    grid2->SetCellValue(1, 3, "15%");
    grid2->SetCellValue(2, 3, "15%");
    grid2->SetCellValue(3, 3, "15%");
    grid2->SetCellValue(4, 3, "10%");
    grid2->SetColSize(0, 150);
    grid2->SetColSize(1, 140);
    grid2->SetColSize(2, 140);
    grid2->SetColSize(3, 140);
    grid2->SetColSize(4, 130);
    int k = 1;
    int l = 2;
    for (int col = 0; col < 2; col++)
    {
        switch (col)
        {
        case 0:
            grid2->SetCellValue(g, col, wxString::Format("L%d/L%d", k + 2 * g, l + 2 * g));
            break;
        case 1:
            grid2->SetCellValue(g, col, std::to_string(b));
            break;
        }
    }


}
void MainFrame::UpdatePanel4_Text2(long double b, int g)
{
    grid2->SetCellValue(g, 2, std::to_string(b));
}

void MainFrame::UpdatePanel4_CheckBox(int g)
{
    attrred = new wxGridCellAttr();
    attrgreen = new wxGridCellAttr();
    attrred->SetBackgroundColour(wxColour(255, 0, 0));
    attrgreen->SetBackgroundColour(wxColour(0, 255, 0));
    switch (g)
    {
    case 0:
        grid2->SetAttr(g, 4, attrgreen);
        grid2->SetCellValue(g, 4, "Збіг");
        break;
    case 1:
        grid2->SetAttr(g - 1, 4, attrred);
        grid2->SetCellValue(g - 1, 4, "Збігу немає");
        break;
    case 2:
        grid2->SetAttr(g / 2, 4, attrgreen);
        grid2->SetCellValue(g / 2, 4, "Збіг");
        break;
    case 3:
        grid2->SetAttr((g - 1) / 2, 4, attrred);
        grid2->SetCellValue((g - 1) / 2, 4, "Збігу немає");
        break;
    case 4:
        grid2->SetAttr(g / 2, 4, attrgreen);
        grid2->SetCellValue(g / 2, 4, "Збіг");
        break;
    case 5:
        grid2->SetAttr((g - 1) / 2, 4, attrred);
        grid2->SetCellValue((g - 1) / 2, 4, "Збігу немає");
        break;
    case 6:
        grid2->SetAttr(g / 2, 4, attrgreen);
        grid2->SetCellValue(g / 2, 4, "Збіг");
        break;
    case 7:
        grid2->SetAttr((g - 1) / 2, 4, attrred);
        grid2->SetCellValue((g - 1) / 2, 4, "Збігу немає");
        break;
    case 8:
        grid2->SetAttr(g / 2, 4, attrgreen);
        grid2->SetCellValue(g / 2, 4, "Збіг");
        break;
    case 9:
        grid2->SetAttr((g - 1) / 2, 4, attrred);
        grid2->SetCellValue((g - 1) / 2, 4, "Збігу немає");
        break;

    }
}
void MainFrame::UpdatePanel4_Text3(int g)
{
    switch (g)
    {
    case 0:
        Text7 = new wxStaticText(panel4, wxID_ANY, "Ви пройшли автентифікацію", wxPoint(560, 20));
        break;
    case 1:
        Text7 = new wxStaticText(panel4, wxID_ANY, "Нажаль, автентифікація \nне пройдена", wxPoint(560, 20), wxSize(150, 100));
        break;
    }
    wxFont font = Text7->GetFont();
    font.SetPointSize(12);
    Text7->SetFont(font);
}
void MainFrame::OnButtonClicked3(wxCommandEvent& evt) {
    int id3 = evt.GetId();
    if (id3 == BUTTON_ID3) {
        cv::cvtColor(image1, image1, cv::COLOR_BGR2RGB);
        cv::cvtColor(image2, image2, cv::COLOR_BGR2RGB);
        dlib::cv_image<dlib::bgr_pixel> dlibImage1(image1);
        dlib::cv_image<dlib::bgr_pixel> dlibImage2(image2);


        // Виявлення обличчi на зображеннях (з використанням алгоритму Dlib)
        dlib::frontal_face_detector faceDetector = dlib::get_frontal_face_detector();
        dlib::shape_predictor shapePredictor;   
        dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> shapePredictor;
        std::vector<dlib::rectangle> faceRects1 = faceDetector(dlibImage1);
        std::vector<dlib::rectangle> faceRects2 = faceDetector(dlibImage2);


        // Вибір першого обличчя
        dlib::full_object_detection shape1 = shapePredictor(dlibImage1, faceRects1[0]);
        dlib::full_object_detection shape2 = shapePredictor(dlibImage2, faceRects2[0]);

        // Вибір точок з ключових точок Dlib
        std::vector<cv::Point2f> point1, point2;
        for (int i = 0; i < shape1.num_parts(); i++) {
            point1.push_back(cv::Point2f(shape1.part(i).x(), shape1.part(i).y()));
            point2.push_back(cv::Point2f(shape2.part(i).x(), shape2.part(i).y()));
        }

        // Оцінка матриці гомографії
        cv::Mat homography = cv::findHomography(point2, point1, cv::RANSAC);

        // Вирівнювання зображення
        cv::Mat aligned_image;
        cv::warpPerspective(image2, image2, homography, image1.size());
        aligned_image = image2;
        // Відображення результатів
        dlib::cv_image<dlib::bgr_pixel> dlibImage3(image1);
        dlib::cv_image<dlib::bgr_pixel> dlibImage4(image2);
        std::vector<dlib::rectangle> faceRects3 = faceDetector(dlibImage3);
        std::vector<dlib::rectangle> faceRects4 = faceDetector(dlibImage4);
        dlib::full_object_detection faceLandmarks = shapePredictor(dlibImage3, faceRects3[0]);
        dlib::point pt;
        dlib::point et;

        // Відображення ключових точок на зображенні
        for (unsigned int i = 0; i < faceLandmarks.num_parts(); ++i) {
            pt = faceLandmarks.part(i);
            cv::circle(image1, cv::Point(pt.x(), pt.y()), 1, cv::Scalar(0, 255, 0), -1);
            // cv::putText(image2, std::to_string(i   ), cv::Point(pt.x() + 5, pt.y() + 5), cv::FONT_HERSHEY_SIMPLEX, 0.2, cv::Scalar(255, 255, 255), 1);
        }
        faceLandmarkglobal = faceLandmarks;
        UpdatePanel3();
        intVectorArray.push_back({ 39,42,points(39,42,255,0,0) }); intVectorArray.push_back({ 27,8,points(27,8,255,0,0) });
        intVectorArray.push_back({ 36,45,points(36,45,255,0,0) }); intVectorArray.push_back({ 27,29,points(27,29,255,0,0) });
        intVectorArray.push_back({ 36,39,points(36,39,255,0,0) }); intVectorArray.push_back({ 37,41,points(37,41,255,0,0) });
        intVectorArray.push_back({ 42,45,points(42,45,255,0,0) }); intVectorArray.push_back({ 43,47,points(43,47,255,0,0) });
        intVectorArray.push_back({ 48,54,points(48,54,255,0,0) }); intVectorArray.push_back({ 27,30,points(27,30,255,0,0) });
        int ai = 0;
        std::ofstream outputFile("D:\\cmake\\build\\x64\\Release\\output.txt");

        for (int k = 0; k < intVectorArray.size(); k += 2)
        {
            ratioPoint.push_back(intVectorArray[k][2] / intVectorArray[k + 1][2]);

            //outputFile << "distance(" << intVectorArray[k][0] << "," << intVectorArray[k][1] << ")=" << intVectorArray[k][2]  << ", distance(" << intVectorArray[k+1][0] << "," << intVectorArray[k+1][1] << ")=" << intVectorArray[k+1][2] << " ratio=" << ratioPoint[ai] << std::endl;
            outputFile << ratioPoint[ai] << std::endl;
            UpdatePanel4_Text1(ratioPoint[ai], ai);
            ai++;
        }
        outputFile << std::endl;
        /* cv::imshow("Vectors", image3);
         cv::waitKey(0);*/
        UpdatePanel3();
        faceLandmarks = shapePredictor(dlibImage4, faceRects4[0]);
        points11(39, 42, 255, 0, 0, 1);// points11(39, 42, 255, 0, 0, 3);
        points11(27, 8, 255, 0, 0, 1); //points11(27, 8, 255, 0,0, 3);
        points11(36, 45, 255, 0, 0, 1);// points11(21, 22, 255, 0, 0, 3);
        points11(27, 29, 255, 0, 0, 1);// points11(51, 62, 255, 0, 0, 3);
        points11(36, 39, 255, 0, 0, 1);// points11(36, 39, 255, 0, 0, 3);
        points11(37, 41, 255, 0, 0, 1);// points11(37, 41, 255, 0, 0, 3);
        points11(42, 45, 255, 0, 0, 1);// points11(42, 45, 255, 0, 0, 3);
        points11(43, 47, 255, 0, 0, 1);// points11(43, 47, 255, 0, 0, 3);
        points11(48, 54, 255, 0, 0, 1);// points11(48, 54, 255, 0, 0, 3);
        points11(27, 30, 255, 0, 0, 1);// points11(27, 30, 255, 0, 0, 3);
        // Відображення ключових точок на зображенні
        for (unsigned int i = 0; i < faceLandmarks.num_parts(); ++i) {
            pt = faceLandmarks.part(i);
            cv::circle(aligned_image, cv::Point(pt.x(), pt.y()), 1, cv::Scalar(0, 255, 0), -1);
            //cv::putText(aligned_image, std::to_string(i), cv::Point(pt.x() + 10, pt.y() + 10), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 255), 1);
        }
        faceLandmarkglobal = faceLandmarks;
        intVectorArray2.push_back({ 39,42,points(39,42,255,0,0) }); intVectorArray2.push_back({ 27,8,points(27,8,255,0,0) });
        intVectorArray2.push_back({ 36,45,points(36,45,255,0,0) }); intVectorArray2.push_back({ 27,29,points(27,29,255,0,0) });
        intVectorArray2.push_back({ 36,39,points(36,39,255,0,0) }); intVectorArray2.push_back({ 37,41,points(37,41,255,0,0) });
        intVectorArray2.push_back({ 42,45,points(42,45,255,0,0) }); intVectorArray2.push_back({ 43,47,points(43,47,255,0,0) });
        intVectorArray2.push_back({ 48,54,points(48,54,255,0,0) }); intVectorArray2.push_back({ 27,30,points(27,30,255,0,0) });
        int ai2 = 0;
        std::ofstream outputFile2("D:\\cmake\\build\\x64\\Release\\output2.txt");
        UpdatePanel3_Text();
        for (int k = 0; k < intVectorArray2.size(); k += 2)
        {
            ratioPoint2.push_back(intVectorArray2[k][2] / intVectorArray2[k + 1][2]);

            //outputFile << "distance(" << intVectorArray[k][0] << "," << intVectorArray[k][1] << ")=" << intVectorArray[k][2]  << ", distance(" << intVectorArray[k+1][0] << "," << intVectorArray[k+1][1] << ")=" << intVectorArray[k+1][2] << " ratio=" << ratioPoint[ai] << std::endl;
            outputFile2 << ratioPoint2[ai2] << std::endl;
            UpdatePanel4_Text2(ratioPoint2[ai2], ai2);
            ai2++;
        }
        outputFile2 << std::endl;
        UpdatePanel2();
        /* cv::imshow("Original Image", image2);
         cv::imshow("Aligned Image", aligned_image);
         cv::waitKey(0);*/
         //for (int k = 0; k < intVectorArray2.size(); k++)
         //{
         //    ratioPoint2.push_back(intVectorArray2[23][2] / intVectorArray2[k][2]);
         //    outputFile2 << "distance(" << intVectorArray2[k][0] << "," << intVectorArray2[k][1] << ")=" << intVectorArray2[k][2] << " ratio=" << ratioPoint2[k] << std::endl;
         //    //outputFile2 << ratioPoint2[k]<<std::endl;
         //}

              // ПЕРЕВІРКА НА ВІДПОВІДНІСТЬ
        int count = 0;
        points11(39, 42, 255, 0, 0, 3);
        points11(27, 8, 255, 0, 0, 3);
        points11(36, 45, 255, 0, 0, 3);
        points11(27, 29, 255, 0, 0, 3);
        points11(36, 39, 255, 0, 0, 3);
        points11(37, 41, 255, 0, 0, 3);
        points11(42, 45, 255, 0, 0, 3);
        points11(43, 47, 255, 0, 0, 3);
        points11(48, 54, 255, 0, 0, 3);
        points11(27, 30, 255, 0, 0, 3);

        if (ratioPoint2[0] >= ratioPoint[0] * 0.9 && ratioPoint2[0] <= ratioPoint[0] * 1.1)
        {
            count++;
            points11(39, 42, 0, 255, 0, 2);
            points11(27, 8, 0, 255, 0, 2);
            UpdatePanel4_CheckBox(0);
        }
        else
        {
            points11(39, 42, 0, 0, 255, 2);
            points11(27, 8, 0, 0, 255, 2);
            UpdatePanel4_CheckBox(1);
        }
        if (ratioPoint2[1] >= ratioPoint[1] * 0.85 && ratioPoint2[1] <= ratioPoint[1] * 1.15)
        {
            count++;
            points11(36, 45, 0, 255, 0, 2);
            points11(27, 29, 0, 255, 0, 2);
            UpdatePanel4_CheckBox(2);
        }
        else
        {
            points11(36, 45, 0, 0, 255, 2);
            points11(27, 29, 0, 0, 255, 2);
            UpdatePanel4_CheckBox(3);
        }
        if (ratioPoint2[2] >= ratioPoint[2] * 0.85 && ratioPoint2[2] <= ratioPoint[2] * 1.15)
        {
            count++;
            points11(36, 39, 0, 255, 0, 2);
            points11(37, 41, 0, 255, 0, 2);
            UpdatePanel4_CheckBox(4);
        }
        else
        {
            points11(36, 39, 0, 0, 255, 2);
            points11(37, 41, 0, 0, 255, 2);
            UpdatePanel4_CheckBox(5);
        }
        if (ratioPoint2[3] >= ratioPoint[3] * 0.85 && ratioPoint2[3] <= ratioPoint[3] * 1.15)
        {
            count++;
            points11(42, 45, 0, 255, 0, 2);
            points11(43, 47, 0, 255, 0, 2);
            UpdatePanel4_CheckBox(6);
        }
        else
        {
            points11(42, 45, 0, 0, 255, 2);
            points11(43, 47, 0, 0, 255, 2);
            UpdatePanel4_CheckBox(7);
        }
        if (ratioPoint2[4] >= ratioPoint[4] * 0.9 && ratioPoint2[4] <= ratioPoint[4] * 1.1)
        {
            count++;
            points11(48, 54, 0, 255, 0, 2);
            points11(27, 30, 0, 255, 0, 2);
            UpdatePanel4_CheckBox(8);
        }
        else
        {
            points11(48, 54, 0, 0, 255, 2);
            points11(27, 30, 0, 0, 255, 2);
            UpdatePanel4_CheckBox(9);
        }
        UpdatePanel4();
        if (count >= 4)
        {
            UpdatePanel4_Text3(0);
        }
        else
            UpdatePanel4_Text3(1);
    }
}
void MainFrame::OnButtonClicked5(wxCommandEvent& evt) 
{
    int id = evt.GetId();
    if (id == BUTTON_ID4)
    {
       
        wxFileDialog openFileDialog(
            this,                              // Батьківське вікно
            "Виберіть файл",                  // Заголовок вікна
            "",                               // Початкова директорія
            "",                               // Початкове ім'я файлу
            "Всі файли (*.*)|*.*",            // Фільтр файлів
            wxFD_OPEN | wxFD_FILE_MUST_EXIST  // Опції
        );
        if (openFileDialog.ShowModal() == wxID_CANCEL) {
            return; // Користувач скасував вибір
        }
        wxMessageDialog dialog(
            this,                           // Батьківське вікно
            "Нажміть так якщо бажаєте використати стандартну модель або ні якщо власну?", // Текст повідомлення
            "Обрання моделі",            // Заголовок вікна
            wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION // Кнопки "Так" / "Ні" і піктограма
        );
        if (dialog.ShowModal() == wxID_YES) {
            std::string filePath = openFileDialog.GetPath().ToStdString();
           my_hog.svm_hog_predict(filePath);
        }
        else {
            my_hog.svm_hog_training("D:\\1\\DYPLOM_MAGA\\train_foto\\test_true", "D:\\1\\DYPLOM_MAGA\\train_foto\\test_false");
        }
       
    }
        //взяти дефолтну або запустити тренування
        //вивести пунк що обличчя знайдено 
        //ввести зображення квадрату
        //відмалювати точки по квадрату 
        //можна точні координати вивести

    
}
//void sobel_filter(std::vector<std::vector<int>>& matrix_pixels)
//{
//   const int b_x = 3;
//   const int b_y = 3;
//    int sobel_matrix_v[3][3] = { -1, 0, 1,  
//                               -2, 0, 2,
//                               -1, 0, 1};
//    int sobel_matrix_h[3][3] = { -1, -2, -1,
//                                  0,  0,  0,
//                                  1,  2 , 1 };
//    int buf_matrix_v[b_x][b_y];
//    int buf_matrix_h[b_x][b_y];
//    int buf_sum_v = 0;
//    int buf_sum_h = 0;
//    for (int x = 1; x < matrix_pixels.size(); x++)
//    {
//        for (int y = 1; y < matrix_pixels[x].size(); y++)
//        {
//            for (int i = 0; i < b_x; i++)
//            {
//                for (int k = 0; k < b_y; k++)
//                {
//                    buf_matrix_v[i][k] = matrix_pixels[x - 1+i][y - 1+k] * sobel_matrix_v[i][k];
//                    buf_matrix_h[i][k] = matrix_pixels[x - 1+i][y - 1+k] * sobel_matrix_h[i][k];
//                    buf_sum_v += buf_matrix_v[i][k];
//                    buf_sum_h += buf_matrix_h[i][k];
//                }
//            }
//        }
//        float magnitude = sqrt(buf_sum_v * buf_sum_v + buf_sum_h * buf_sum_h);
//        float direction = atan2(buf_sum_v, buf_sum_h);
//    }
//
//}

//int sum_matrix(int** mat1)
//{
//    int buf = 0;
//    for(int i=0)
//   return 
//}

