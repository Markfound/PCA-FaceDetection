//
//  GetFeatures.h
//  FaceDetection
//
//  Created by Markfound on 2019/4/18.
//  Copyright © 2019年 Markfound. All rights reserved.
//

#ifndef GetFeatures_h
#define GetFeatures_h

void MyPCA();
void GetFeatures();
double** Mycov(double* SrcData,const int n,const int m);
bool PCA_Dis(Mat SrcImg);
#endif /* GetFeatures_h */
