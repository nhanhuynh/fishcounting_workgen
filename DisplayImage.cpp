#include "FishDetector.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/*int main( int argc, char** argv )
//{
	//IplImage* img = cvLoadImage("/home/zac/workspacecpp2/fishcounting/src/img/439.jpg");
	//cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
	//cvShowImage("Example1",img);
	//cvWaitKey(0);
	//cvReleaseImage(&img);
	//cvDestroyWindow("Example1");
	system("wget http://api.metacaptcha.com/public/images/439.png");
	FishDetector fish_detector ("/home/zac/workspacecpp2/fishcounting/src/cascade.xml");
	string json = fish_detector.detect("/home/zac/workspacecpp2/fishcounting/src/img/439.jpg");
	ofstream myfile;
	myfile.open ("out");
	myfile << json;
	myfile.close();
	//cvRectangle(
	//img,
	//cvPoint(r.x,r.y),
	//cvPoint(r.x+r.width,r.y+r.height),
	//cvScalar(255,255,255));
//
	//show image to the screen
	//cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
	//cvShowImage("Example1",img);
	//cvWaitKey(0);
	//cvReleaseImage(&img);
	//cvDestroyWindow("Example1");
//
  return 0;
}
*/
