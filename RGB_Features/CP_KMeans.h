/*
*功能：实现图像颜色聚类的KMeans算法
*作者：程嘉梁
*日期：2018/05/21
*历史来源：https://blog.csdn.net/Muses_9/article/details/53118872
*/

#pragma once
#ifndef CP_KMEANS_H
#define CP_KMEANS_H

#include<iostream>
#include<vector>
using namespace std;

typedef struct Pixel//像素点结构体
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class KMeans
{
public:
	KMeans(vector<Pixel> node, int dimension);
	~KMeans();

	//得到对应维数的图像特征向量
	int* kmeans();

private:

	//得到欧氏距离
	double getDistance(Pixel x1,Pixel x2);

	//根据质心确定当前像素点属于哪个族
	int clusterOfPixel(Pixel p);

	//获得给定族的误差
	float getError();

	//获得当前族的质心
	Pixel getMeans(vector<Pixel> cluster);

	//用k-means++算法选择k个点作为初始聚类中心
	void initSeeds();

	vector<Pixel> m_node;//初始图像数据集
	int m_dimension;//特征维度
	vector<Pixel> *m_clusters;//存储聚类
	Pixel *m_means;//每个类质心
};

#endif // !CP_KMEANS_H
