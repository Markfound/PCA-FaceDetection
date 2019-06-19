////
////  Test.cpp
////  FaceDetection
////
////  Created by Markfound on 2019/4/14.
////  Copyright � 2019年 Markfound. All rights reserved.
////
//
//#include <iostream>
//#include <string>
//
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/objdetect/objdetect.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//using namespace cv;
//using namespace std;
//
//string xmlPath="/Users/markfound/Documents/opencv-4.1.0/data/haarcascades/haarcascade_frontalface_default.xml";
////xmlpath 记录.xml文件的路径
//void detectAndDisplay(Mat image);
//int main( int argc,char**argv )
//{
//    string path="/Users/markfound/Documents/Fans.jpg";//以检测图片4.jpg为例
//    Mat image =imread(path,-1);
//
//    CascadeClassifier a;     //创建脸部对象
//    if(!a.load(xmlPath))     //如果读取文件不出错，则检测人脸
//    {
//        cout<<"无法加载xml文件"<<endl;
//        return 0;
//    }
//
//    detectAndDisplay(image);// 检测人脸
//    return 0;
//
//}
//
//void detectAndDisplay(Mat image)
//{
//    CascadeClassifier ccf;      //创建脸部对象
//    ccf.load(xmlPath);           //导入opencv自带检测的文件
//    vector<Rect> faces;
//    Mat gray;
//    cvtColor(image,gray,COLOR_BGR2GRAY);
//    equalizeHist(gray,gray);
//    ccf.detectMultiScale(gray,faces,1.1,3,0,Size(50,50),Size(500,500));
//    for(vector<Rect>::const_iterator iter=faces.begin();iter!=faces.end();iter++)
//    {
//        rectangle(image,*iter,Scalar(0,0,255),2,8); //画出脸部矩形
//    }
//    Mat image1;
//
//    for(size_t i=0;i<faces.size();i++)
//    {
//        Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
//        image1= image(Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height));
//    }
//
//    imshow("1",image);
//    imshow("2",image1);
//    waitKey(0);
//
//}
//
//
#include "AllHeader.h"
#include "GetData.hpp"
#include "GetFeatures.h"
//string xmlPath="/Users/markfound/Documents/opencv-4.1.0/data/haarcascades/haarcascade_frontalface_alt_tree.xml";  //识别率高，但是较慢

int main()
{
    VideoCapture capture(0); //Turn on the camera
    if (!capture.isOpened())
    {
        cout << "Open Video Failed!" << endl;
        exit(1);
    }
    string xmlPath = "/usr/local/Cellar/opencv/4.1.0_1/share/opencv4/haarcascades/haarcascade_frontalface_alt_tree.xml";
    //Loading Face Database
    CascadeClassifier Tem;
    if (!Tem.load(xmlPath))
    {
        cout << "Open Xml Failed!" << endl;
        exit(1);
    }
    Mat SrcImg, SrcImgGray, face;
    vector<Rect> faces;
    while (1)
    {
        capture >> SrcImg;
        faces.clear();
        cvtColor(SrcImg, SrcImgGray, COLOR_BGR2GRAY);
        equalizeHist(SrcImgGray, SrcImgGray);
        Tem.detectMultiScale(SrcImgGray, faces, 1.1, 3, 0, Size(50, 50), Size(500, 500));
        if (faces.size() == 1)
        {
            face = SrcImgGray(faces[0]);
            imshow("Video", SrcImg);
            resize(face, face, Size(30, 30));
            //    if(PCA_Dis(face))   //judge the dist;ance between input image and database image
            {
                rectangle(SrcImg, faces[0], Scalar(0, 0, 255), 2, 8);
                //display：Matching success
                cv::putText(SrcImg, "Matching success", Point(50, 50), cv::FONT_HERSHEY_TRIPLEX, 0.8, cv::Scalar(255, 200, 200), 2, CV_AVX);
                imshow("Video", SrcImg);
                break;
            }
        }
        imshow("111", SrcImg);
        waitKey(10);
    }
    return 0;
}
