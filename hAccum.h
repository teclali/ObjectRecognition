#include <opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class HoughAccumulator {
public:
	HoughAccumulator(int width, int height, Mat img);
	pair<int, int> getMax();
	void add(float rho, float theta)
	
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
};
