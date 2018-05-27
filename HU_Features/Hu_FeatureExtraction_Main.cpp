#include<iostream>
#include<cv.h>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<fstream>
#include<string>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	ifstream file("imagelist.txt");
	if (!file)
		exit(1);

	ofstream outfile("Hu_Features.txt");
	string imageName;
	int times = 0;

	while (getline(file, imageName))
	{
		times++;
		imageName = "image/" + imageName;
		Mat image = imread(imageName);
		cvtColor(image, image, CV_BGR2GRAY);
		Moments mts = moments(image);
		double hu[7];
		HuMoments(mts, hu);

		cout << times << endl;
		for (int i = 0; i < 7; i++)
		{
			outfile << log(abs(hu[i])) << " ";
		}
		outfile << endl;
	}
	system("pause");
	return 0;
}