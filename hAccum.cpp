#include "hAccum.h"
#include <opencv.hpp>
#include <vector>
#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;

const double PI = 3.14159265358979323846;
const double E =  2.71828182845904523536;

HoughAccumulator::HoughAccumulator(int width, int height, vector< pair<Point, Point> > pointPairs, Mat img) {
	this->width = width;
	this->height = height;
	this->img = img;
	this->pointPairs = pointPairs;
	this->diagonal = hypotf(width, height);
	this->rhoMax = (int)(diagonal / 2) + 1;
	this->thetaMax = 180;
	
	matrix = Mat::zeros(rhoMax, thetaMax, CV_32F);

	for (i = 0; i < pointPairs.size(); i++) {
		if (gradDir(pointPairs[i].first, img) - gradDir(pointPairs[i].second, img) == 0) {
			float rho = symRho(pointPairs[i].first, pointPairs[i].second);
			float theta = symTheta(pointPairs[i].first, pointPairs[i].second);

			matrix.at<double>(rho, theta) += 1;
			
			if (i == (int)(pointPairs.size() / 4)) 
				cout << "25%" << endl;
			if (i == (int)(pointPairs.size() / 2))
				cout << "50%" << endl;
			if (i == ((int)(pointPairs.size()) / 4) * 3)
				cout << "75%" << endl;
		}
	}
}

float HoughAccumulator::symRho(Point i, Point j) {
	float mag;

	mag = ((i.x + j.x) / 2) * (cos ( symTheta(i, j))) + ((i.y + j.y) / 2) * (sin(symTheta(i, j)));
   
	return mag;
}

float HoughAccumulator::symTheta(Point i, Point j) {
	float theta;	

   	if (j.x - i.x == 0)
    	theta = 90;
   	else
      	theta = atan2((j.y - i.y), (j.x - i.x)) * 180 / PI;
	
	return theta;
}

/*float HoughAccumulator::weight(Point i, Point j) {
	
	weight = 1 / sqrt(2 * PI) * pow(e, -(pow(gradDir(i) - gradDir(j)), 2) / 2);
	
	return weight;
}*/

float HoughAccumulator::gradDir(Point a, Mat img) {
	float Gx, Gy, theta;
	Point p1, p2, p3, p4, p5, p6, p7, p8, p9;

	p1 = Point(a.x - 1, a.y + 1);
	p2 = Point(a.x, a.y + 1);	
	p3 = Point(a.x + 1, a.y + 1);
	p4 = Point(a.x - 1, a.y);
	p5 = Point(a.x, a.y);
	p6 = Point(a.x + 1, a.y);
	p7 = Point(a.x - 1, a.y - 1);
	p8 = Point(a.x, a.y - 1);
	p9 = Point(a.x + 1, a.y - 1);

	Gx = (img.at<uchar>(p2) - img.at<uchar>(p8) + img.at<uchar>(p1) - img.at<uchar>(p7) + img.at<uchar>(p3) - img.at<uchar>(p9)) / 2;
	Gy = (img.at<uchar>(p6) - img.at<uchar>(p4) + img.at<uchar>(p9) - img.at<uchar>(p7) + img.at<uchar>(p3) - img.at<uchar>(p1)) / 2;

	if (Gy == 0)
		theta = 90;
	else
		theta = atan2(Gx, Gy); 
}

pair<int, int> HoughAccumulator::getMax() {
	int x, y;
	int rhoHigh, thetaHigh;
	int votes = 0;

	for(y = 0; y < matrix.rows; y++){
		for(x = 0; x < matrix.cols; x++){
			if(matrix.at<double>(x, y) > votes) {
				votes = matrix.at<double>(x, y);
				rhoHigh = x;
				thetaHigh = y;
			}
		}
	}
	
	return make_pair(rhoHigh, thetaHigh);
}






