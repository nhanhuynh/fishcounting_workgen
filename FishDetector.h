///*
// * FishDetector.h
// *
// *  Created on: Aug 28, 2013
// *      Author: zac
// */
//
//#ifndef FISHDETECTOR_H_
//#define FISHDETECTOR_H_
//#include <cv.h>
//#include <highgui.h>
//#include "string"
//#include "opencv2/core/core.hpp"
//using namespace cv;
//using namespace std;
//class FishDetector
//{
//public:
//	//constructor
//	//input: the link to pretrained cascade file
//	FishDetector(string cascade_file);
//
//	//detect a single image
//	string detect(string img_path);
//
//	//detect multiple images
//	string detect(string img_paths[], int length);
//private:
//	CascadeClassifier fish_cascade;
//
//	string Rect2Obj( Rect rect);
//	string Rects2Json(vector<Rect> *rects);
//};
//
//
//
//#endif /* FISHDETECTOR_H_ */
