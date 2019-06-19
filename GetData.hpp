//
//  GetData.hpp
//  FaceDetection
//
//  Created by Markfound on 2019/4/18.
//  Copyright © 2019年 Markfound. All rights reserved.
//

#ifndef GetData_hpp
#define GetData_hpp

#include <stdio.h>
#include"AllHeader.h"
#endif /* GetData_hpp */

void GetSrcPh();
void FindFace(Mat SrcImg,vector<Rect> &faces);
void PhTest();
void BuildData(int n);
void GetPhAuto(int n);
