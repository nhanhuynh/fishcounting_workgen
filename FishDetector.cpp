///*
// * FishDetector.cpp
// *
// *  Created on: Aug 28, 2013
// *      Author: zac
// */
//#include "FishDetector.h"
//FishDetector::FishDetector(string cascade_file)
//	{
//		//load cascade file
//		bool load = fish_cascade.load(cascade_file);
//		if( !load ){
//			cout<<"Error loading cascade classifier";
//		}
//	};
//string FishDetector::detect(string img_path)
//{
//	IplImage* img= cvLoadImage(img_path.c_str());
//	float scale = 1;
//	Mat mat_img = imread(img_path,1);
//	Mat mat_gray;
//	std::vector<Rect> fishes;
//	IplImage* frame_gray = cvCreateImage(cvSize (
//				cvRound(img->width / scale) , cvRound(img->height/scale))
//			,8, 1);
//	cvtColor(mat_img, mat_gray, CV_BGR2GRAY);
//	equalizeHist(mat_gray, mat_gray);
//	fish_cascade.detectMultiScale(mat_gray, fishes, 1.1, 3, 0| CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 20));
//	Rect r = fishes[0];
//	return Rects2Json(&fishes);
//}
//
//string FishDetector::detect(string img_paths[], int length)
//{
//	std::vector<Rect> fishes;
//	for (int i =0 ; i< length; i++)
//	{
//		const char * img_path = img_paths[i].c_str();
//		IplImage* img= cvLoadImage(img_path);// load image from argument to OpenCV img type
//		float scale = 1;
//		Mat mat_img = imread(img_path, 1); //turn image to matrix
//		Mat mat_gray; //matrix contain gray scale version of the img
//		std::vector<Rect> temp; //temporary storage for the Rect
//
//		//process image before detecting
//		IplImage* frame_gray = cvCreateImage(cvSize (
//					cvRound(img->width / scale) , cvRound(img->height/scale))
//				,8, 1);
//		cvtColor(mat_img, mat_gray, CV_BGR2GRAY);
//		equalizeHist(mat_gray, mat_gray);
//
//		//detect
//		fish_cascade.detectMultiScale(mat_gray, temp, 1.1, 3, 0| CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 20));
//		//push the result to fishes vector
//		fishes.insert(fishes.end(), temp.begin(), temp.end());
//		//Deallocate memory
//		cvReleaseImage(&img);
//		cvReleaseImage(&frame_gray);
//
//	}
//	return Rects2Json(&fishes);
//}
//string FishDetector::Rect2Obj( Rect rect)
//	{
//		stringstream ss;
//		ss<<"{\"x\":\""<<rect.x<<"\","<<"\"y\":\""<<rect.y<<+"\","<<" \"width\":\""<<rect.width<<"\","<<"\"rect.width\":\""<<rect.height<<"\"}";
//		return ss.str();
//
//	}
//string FishDetector::Rects2Json(vector<Rect> *rects)
//{
//	int size = rects->size();
//	if (!rects || size==0)
//		return "[]";
//	string json ="[";
//	for (int i=0; i < size; i++)
//	{
//		if (i == size-1)
//			json += Rect2Obj(rects->at(i)) +"]";
//		else
//			json += Rect2Obj(rects->at(i)) +",";
//	}
//	return json;
//}
