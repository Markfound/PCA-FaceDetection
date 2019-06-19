//
//  GetData.cpp
//  FaceDetection
//
//  Created by Markfound on 2019/4/18.
//  Copyright © 2019年 Markfound. All rights reserved.
//

#include "GetData.hpp"
#include"AllHeader.h"

using namespace std;

void GetSrcPh()
{
    VideoCapture Cap(0);
    if(!Cap.isOpened())
    {
        cout<<"Open Video Failed!"<<endl;
        exit(1);
    }
    Mat ph;
    int cnt=1;
    string SavePath=format("/Users/markfound/Documents/FaceSamples/%d.jpg",cnt);
    while(1)
    {
        Cap>>ph;
        imshow("Video",ph);
        if(waitKey(10)=='p')
        {
            imwrite(SavePath,ph);
            cnt++;
            SavePath=format("/Users/markfound/Documents/FaceSamples/%d.jpg",cnt);
        }
        if(waitKey(10)=='q')
        {
            break;
        }
    }
}

void PhTest()
{
    vector<Rect>faces;
    faces.clear();
    string OpenPath="/Users/markfound/Documents/MyFaces/";
    Mat SrcImg,SrcImgGray;
    for(int i=1;i<=11;i++)
    {
        char Photo[10];
        sprintf(Photo,"%d%s",i,".jpg");
        string RealPath=OpenPath+Photo;
        SrcImg=imread(RealPath, -1);
        FindFace(SrcImg,faces);
        if(!faces.empty())
        {
            Mat RealFace=SrcImg(faces[0]);
            imshow(Photo,RealFace);
            resize(RealFace, RealFace, Size(100,100));
            imshow(RealPath,RealFace);
        }
        else
        {
            cout<<i<<endl;
        }
    }
    waitKey(0);
}
void GetPhAuto(int n)  //Automatic acquisition of face images ，n:The number of face photos you want to get
{
    VideoCapture capture(0);
    vector<Rect>faces;
    //OpenCV Self-identification Library
    string xmlPath="/Users/markfound/Documents/opencv-4.1.0/data/haarcascades/haarcascade_frontalface_alt_tree.xml";
    CascadeClassifier Tem;
    if(!Tem.load(xmlPath))
    {
        cout<<"Open Xml Failed!"<<endl;
        exit(1);
    }
    int res=0;   //count the face photos
    Mat SrcImg,face,SrcImgGray;
    char Path[10];
    string savePath="/Users/markfound/Documents/MyFacess/";
    while(1)     //Real-time Face Picture Acquisition by Camera
    {
        capture>>SrcImg;
        faces.clear();
        cvtColor(SrcImg, SrcImgGray, COLOR_BGR2GRAY);
        equalizeHist(SrcImgGray, SrcImgGray);
        Tem.detectMultiScale(SrcImgGray,faces,1.1,3,0,Size(50,50),Size(500,500));
        if(faces.size()==1)
        {
            res++;
            face=SrcImgGray(faces[0]);
            rectangle(SrcImg,faces[0],Scalar(0,0,255),2,8);
            //cv::putText(SrcImg, "Matching success", Point(50,50), cv::FONT_HERSHEY_TRIPLEX, 0.8, cv::Scalar(255, 200, 200), 2, CV_AVX);
            imshow("Video",SrcImg);
            resize(face, face, Size(30,30));    //Standardized picture size
            sprintf(Path, "%d%s",res,".bmp");
            string Pathh=savePath+Path;
            imwrite(Pathh, face);
            if(res==n)
            {
                break;
            }
        }
        waitKey(10);
    }
}

void FindFace(Mat SrcImg,vector<Rect> &faces)
{
    string xmlPath="/Users/markfound/Documents/opencv-4.1.0/data/haarcascades/haarcascade_frontalface_alt_tree.xml";  //识别率高，但是较慢
    CascadeClassifier Tem;
    if(!Tem.load(xmlPath))
    {
        cout<<"Open Xml Failed!"<<endl<<"@Markfound"<<endl;
        exit(1);
    }
    faces.clear();
    Mat SrcImgGray;
    cvtColor(SrcImg, SrcImgGray, COLOR_BGR2GRAY);
    faces.clear();
    equalizeHist(SrcImgGray, SrcImgGray);
    Tem.detectMultiScale(SrcImgGray, faces,1.1,3,0,Size(50,50),Size(500,500));
    
//    for(int cnt=1;cnt<=n;cnt++)
//    {
//        string OpenPath=format("/Users/markfound/Documents/FaceSamples/%d.jpg",cnt);
//        Mat SrcImg=imread(OpenPath,-1);
//        Mat SrcImgGray;
//        cvtColor(SrcImg, SrcImgGray, COLOR_RGB2GRAY);
//        faces.clear();
//        equalizeHist(SrcImgGray,SrcImgGray);
//        Tem.detectMultiScale(SrcImgGray,faces,1.1,3,0,Size(50,50),Size(500,500));
////        for (auto iter=faces.begin();iter!=faces.end();iter++)
//        {
//            rectangle(SrcImg,*iter,Scalar(0,0,255),2,8);
//        }
//        string title=format("%d",cnt);
//        imshow(title,SrcImg);
        
//    }
//    return faces;
}

void BuildData(int n)  //n:The number of face pictures
{
    string OpenPath="/Users/markfound/Documents/MyFaces/";  //Loading Face Picture Library
    Mat SrcImg,SrcImgGray;
    Mat DataBase(900,n,CV_32FC1);   //size (30,30)
    char Photo[10];
    for(int i=1;i<=n;i++)    //feature extraction
    {
        sprintf(Photo,"%d%s",i,".bmp");
        string RealPath=OpenPath+Photo;   //RealPath of face pictures
        SrcImg=imread(RealPath,-1);
        cvtColor(SrcImg, SrcImg, COLOR_BGR2GRAY);
        Mat ImgRow=DataBase.col(i-1);
        SrcImg.reshape(1,900).col(0).convertTo(ImgRow, CV_32FC1);
    }
    PCA pca(DataBase,Mat(),PCA::DATA_AS_COL,400);   //PCA dimension reduction
    Mat Eigenvectors;
    pca.eigenvectors.convertTo(Eigenvectors, CV_32FC1);
    Mat Data=Eigenvectors*DataBase;
    Data.convertTo(Data, CV_32FC1);
    //Save data locally
    FileStorage fs("/Users/markfound/Documents/C++/FaceDetection/vocabulary.xml", FileStorage::WRITE);
    fs<<"DataBase"<<Data;
    fs<<"Eigenvectors"<<Eigenvectors;
    fs.release();
}
