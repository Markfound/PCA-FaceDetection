//
//  GetFeatures.cpp
//  FaceDetection
//
//  Created by Markfound on 2019/4/18.
//  Copyright © 2019年 Markfound. All rights reserved.
//

#include "AllHeader.h"
#include "GetFeatures.h"



double** Mycov(double* SrcData,const int n,const int m)  //n*m的源矩阵:m个n维数据  返回的是一个double类型的二维矩阵
{
    double* avr=new double [m];
    for(int i=0;i<m;i++)
    {
        avr[i]=0;
        for(int j=0;j<n;j++)
        {
            avr[i]+=*(SrcData+i*n+j);
        }
        avr[i]/=n;
        //cout<<avr[i]<<endl;
        for(int j=0;j<n;j++)   //数据去均值
        {
            *(SrcData+i*n+j)=*(SrcData+i*n+j)-avr[i];
        }
    }
    double** cov;
    cov=new double* [m];
    for(int i=0;i<m;i++)
    {
        cov[i]=new double[m];
    }
    for(int i=0;i<m;i++)
    {
        for(int j=i;j<m;j++)
        {
            double ans=0;
            for(int k=0;k<n;k++)
            {
                ans+=*(SrcData+i*n+k)*(*(SrcData+j*n+k));
            }
            ans/=(n-1);
            cov[i][j]=ans;
            //cout<<i<<' '<<j<<' '<<ans<<endl;
        }
    }
    return cov;
}
bool PCA_Dis(Mat SrcImg)
{
    //Load the database
    FileStorage fs("/Users/markfound/Documents/C++/FaceDetection/vocabulary.xml", FileStorage::READ);
    Mat DataBase,Eigenvetors;
    fs["DataBase"]>>DataBase;
    fs["Eigenvectors"]>>Eigenvetors;
    fs.release();
    
    DataBase.convertTo(DataBase, CV_32FC1);
    Eigenvetors.convertTo(Eigenvetors, CV_32FC1);
    transpose(Eigenvetors, Eigenvetors);    //Matrix transposition
    cvtColor(SrcImg, SrcImg, COLOR_BGR2GRAY);
    SrcImg=SrcImg.reshape(1,1);
    SrcImg.convertTo(SrcImg, CV_32FC1);
    Mat Features=SrcImg*Eigenvetors;
    int minn=0x7f7f7f7f;
    //Find the min distance
    for(int i=0;i<1;i++)
    {
        uchar *P=Features.ptr(0);
        int dis=0;
        for(int j=0;j<DataBase.rows;j++)
        {
            uchar *p=DataBase.ptr(j);
            dis+=((int)(*(P+j))-(int)(*(p+i)))*((int)(*(P+j))-(int)(*(p+i)));
        }
        if(dis<minn)
        {
            minn=dis;
        }
    }
    if(minn<=1e3)   //If the min distance is less than 1000, it is considered to be the same person.
    {
        return true;
    }
    return false;
}
