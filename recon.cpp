#include <iostream>
#include <opencv.hpp>
#include <highgui.h>
#include "hAccum.h"
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <vector>

using namespace std;
using namespace cv;

/*
To find orientation of the line of symmetry take two pixels on the line and use the depth and relative location o find the tilt and slant angles. 
*/

void showImg(Mat img) {
	namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow( "Display window", img );                  

    waitKey(0);                                       
    return;
}

vector< pair<Point, Point> > getPairs(Mat img) {
	
	int width = img.cols;
	int height = img.rows;
	
	Mat edgeImg;
	Canny(img, edgeImg, 100.0, 200.0);
	
	vector<Point> edgePix;
	vector< pair<Point, Point> > pointPair;
	pair<Point, Point> tempPair;

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++) {
			if (edgeImg.at<uchar>(Point(x, y)) == 255)
				edgePix.push_back(Point(x - width / 2, y - height / 2));
		}		

	for (int i = 0; i < edgePix.size(); i++)
		for (int j = i; j < edgePix.size(); j++) {
			tempPair = make_pair(edgePix[i], edgePix[j]);
			pointPair.push_back(tempPair);
		}		
		
	cout << edgePix.size() << endl;
	cout << pointPair.size() << endl;
	
	return pointPair;
}

Mat drawLine(int rho, int theta, int width, int height, Mat img) {
	int i;
	int lcd;

	int x1 = (int)(rho * cos(theta)) + width / 2;
	int y1 = (int)(rho * sin(theta)) + height / 2;
	
	for (i = 0; i < width; i++) {
		if ((int)(tan(theta) * i) == tan(theta) * i)
			lcd = i;
			break;
	}

	int x2 = x1 + 5;
	int y2 = y1 + tan(theta) * lcd * 5;

	Point pt1 (x1, y1);
	Point pt2 (x2, y2);

	line(img, pt1, pt2, Scalar (255, 0, 255), 2, 8, 0);

	return img;
}

int main( int argc, char** argv ) {

	Mat img = imread(argv[1]);
	
	vector< pair<Point, Point> > pointPair = getPairs(img);
	
	HoughAccumulator hAccum(113, 128, pointPair, img);
	
	pair<int, int> result = hAccum.getMax();

	cout << result.first << "," << result.second << endl;
	return 0;
}



