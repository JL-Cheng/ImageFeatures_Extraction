#include"CP_KMeans.h"
#include<math.h>
#include<time.h>

#define min(a,b) a<b?a:b

KMeans::KMeans(vector<Pixel> node, int dimension):
	m_node(node),
	m_dimension(dimension)
{
	m_clusters = new vector<Pixel>[m_dimension];
	m_means = new Pixel[m_dimension];

	//��ʼ��
	for (int i = 0; i < m_dimension; i++)
	{
		m_means[i].b = 0;
		m_means[i].g = 0;
		m_means[i].r = 0;
	}

}

KMeans::~KMeans()
{
	delete[]m_clusters;
	delete[]m_means;
}

double KMeans::getDistance(Pixel x1, Pixel x2)
{
	return sqrt((double)((x1.b - x2.b)*(x1.b - x2.b) + (x1.g - x2.g)*(x1.g - x2.g) + (x1.r - x2.r)*(x1.r - x2.r)));
}

int KMeans::clusterOfPixel(Pixel p)
{
	double minDistance = getDistance(m_means[0], p);
	double temp;
	int flag = 0;//��־��һ���������ĸ���
	for (int i = 1; i < m_dimension; i++)
	{
		temp = getDistance(m_means[i], p);
		if (temp < minDistance)
		{
			minDistance = temp;
			flag = i;
		}
	}

	return flag;
}

float KMeans::getError()
{
	double error = 0;
	for (int i = 0; i < m_dimension; i++)
	{
		for (int j = 0; j < m_clusters[i].size(); j++)
		{
			error += getDistance(m_clusters[i][j], m_means[i]);
		}
	}

	return error;
}

Pixel KMeans::getMeans(vector<Pixel> cluster)
{
	double meansR = 0, meansG = 0, meansB = 0;
	Pixel mean;
	for (int i = 0; i < cluster.size(); i++)
	{
		meansR += cluster[i].r;
		meansB += cluster[i].b;
		meansG += cluster[i].g;
	}
	mean.b = meansB / cluster.size();
	mean.g = meansG / cluster.size();
	mean.r = meansR / cluster.size();

	return mean;
}

void KMeans::initSeeds()
{
	srand((unsigned int)time(NULL));
	int idx = rand() % m_node.size();
	int count = 0;
	m_means[count++] = m_node[idx];//��¼ѡ��ľ�ֵ����

	double *distance = new double[m_node.size()];//��¼ÿ�������������ľ�ֵ���ĵľ���
	for (int i = 0; i < m_node.size(); i++)
		distance[i] = 1000;

	while (count < m_dimension)//���ÿ���������������ľ�ֵ���ĵľ���
	{
		double sum = 0;
		for (int i = 0; i < m_node.size(); i++)
		{
			for (int j = 0; j < count; j++)
			{
				if (i == j)continue;
				distance[i] = min(distance[i], getDistance(m_node[i], m_means[j]));
			}
			sum += distance[i];
		}

		for (int i = 0; i < m_node.size(); i++)//�������
		{
			distance[i] /= sum;
		}

		//������ʵ�ǰ׺��
		double *cumprobs = new double[m_node.size()];
		cumprobs[0] = distance[0];
		for (int i = 1; i < m_node.size(); i++)
		{
			cumprobs[i] = cumprobs[i - 1] + distance[i];
		}

		//�жϵ��Ƿ�ʹ��
		bool *used = new bool[m_node.size()];
		for (int i = 0; i < m_node.size(); i++)
			used[i] = true;
		used[idx] = false;

		//Ѱ�������ĵ�
		bool flag = true;
		while (flag)
		{
			double r = (rand() % 1000)*0.001;
			for (int i = 0; i < m_node.size(); i++)
			{
				if (r < cumprobs[i] && used[i])//�������������ص�
				{
					idx = i;
					flag = 0;
					used[i] = false;
					break;
				}
			}
		}

		m_means[count++] = m_node[idx];
		delete[]cumprobs;
		delete[]used;
	}

	delete[]distance;
}
int* KMeans::kmeans()
{
	if (m_node.size() <= 0)
		exit(1);
	initSeeds();//��ʼ����������
	int label = 0;

	for (int i = 0; i < m_node.size(); i++)
	{
		label = clusterOfPixel(m_node[i]);
		m_clusters[label].push_back(m_node[i]);
	}

	double oldError = -1;
	double newError = getError();
	int times = 0;
	//�����Ż�
	while(abs(newError-oldError)>=1&&times<100)
	{
		for (int i = 0; i < m_dimension; i++)//�������ĵ�λ��
		{
			m_means[i] = getMeans(m_clusters[i]);
		}
		oldError = newError;
		newError = getError();
		for (int i = 0; i < m_dimension; i++)
		{
			m_clusters[i].clear();
		}

		for (int i = 0; i < m_node.size(); i++)
		{
			label = clusterOfPixel(m_node[i]);
			m_clusters[label].push_back(m_node[i]);
		}
		times++;
	}

	//���ؽ��������Ϊ�������Ӵ�С˳�����е���ɫ��������ֵ
	int *result = new int[m_dimension];
	for (int i = 0; i < m_dimension; i++)
	{
		result[i] = m_means[i].r * 100 + m_means[i].g * 10 + m_means[i].b;
	}

	//������ֵ�������Ӵ�С��˳������
	vector<Pixel> temp1;
	int temp2;
	for (int i = 0; i < m_dimension; i++)
	{
		for (int j = m_dimension - 1; j > i; j--)
		{
			if (m_clusters[j].size() > m_clusters[j - 1].size())
			{
				temp1 = m_clusters[j];
				m_clusters[j] = m_clusters[j - 1];
				m_clusters[j - 1] = temp1;

				temp2 = result[j];
				result[j] = result[j - 1];
				result[j - 1] = temp2;
			}
		}
	}

	return result;
}