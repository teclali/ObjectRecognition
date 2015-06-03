#include <opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class HoughAccumulator {
public:
	HoughAccumulator(int width, int height, vector< pair<Point, Point> > pointPairs, Mat img);
	pair<int, int> getMax();

	float weight(Point i, Point j);
	float symRho(Point i, Point j);
	float symTheta(Point i, Point j);

	float gradDir(Point a, Mat img);
	
private:
	Mat matrix;
	int i, x, y;
	int rhoHigh, thetaHigh;
	int votes;
	int width;
	int height;
	float diagonal;
	int rhoMax;
	int thetaMax;
	Mat img;
	vector< pair<Point, Point> > pointPairs;
};
