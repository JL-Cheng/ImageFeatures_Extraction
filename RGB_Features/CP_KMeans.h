/*
*���ܣ�ʵ��ͼ����ɫ�����KMeans�㷨
*���ߣ��̼���
*���ڣ�2018/05/21
*��ʷ��Դ��https://blog.csdn.net/Muses_9/article/details/53118872
*/

#pragma once
#ifndef CP_KMEANS_H
#define CP_KMEANS_H

#include<iostream>
#include<vector>
using namespace std;

typedef struct Pixel//���ص�ṹ��
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

	//�õ���Ӧά����ͼ����������
	int* kmeans();

private:

	//�õ�ŷ�Ͼ���
	double getDistance(Pixel x1,Pixel x2);

	//��������ȷ����ǰ���ص������ĸ���
	int clusterOfPixel(Pixel p);

	//��ø���������
	float getError();

	//��õ�ǰ�������
	Pixel getMeans(vector<Pixel> cluster);

	//��k-means++�㷨ѡ��k������Ϊ��ʼ��������
	void initSeeds();

	vector<Pixel> m_node;//��ʼͼ�����ݼ�
	int m_dimension;//����ά��
	vector<Pixel> *m_clusters;//�洢����
	Pixel *m_means;//ÿ��������
};

#endif // !CP_KMEANS_H
