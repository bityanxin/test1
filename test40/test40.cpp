﻿#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void customColorMap(Mat &image);
int main(int argc, const char *argv[])
{
	Mat src = imread("D:/images/dog.bmp");
	if (src.empty())
	{
		printf("could not load image...\n");
		return -1;
	}
	Mat gray, dst;
	// 使用LUT
	applyColorMap(src, dst, COLORMAP_RAINBOW);
	// 显示结果
	imshow("colorMap", dst);

	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);
	customColorMap(gray);

	Mat mat_gray = Mat::zeros(Size(30, 512), CV_8UC1);
	for (int i = 0; i < 256; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			mat_gray.at<uchar>(2 * i, j) = 255 - i;
			mat_gray.at<uchar>(2 * i + 1, j) = 255 - i;
		}
	}

	imshow("mat_gray", mat_gray);
	imwrite("colorbar.bmp", mat_gray);

	waitKey(0);

	return 0;
}

void customColorMap(Mat &image) {
	int lut[256];
	for (int i = 0; i < 256; i++) {
		if (i < 127)
			lut[i] = 0;
		else
			lut[i] = 255;
	}

	int h = image.rows;
	int w = image.cols;
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			int pv = image.at<uchar>(row, col);
			image.at<uchar>(row, col) = lut[pv];
		}
	}
	imshow("lut demo", image);
}

