#include"CP_Test.h"
#include"CP_KMeans.h"
#include "atlimage.h"
#include<fstream>
#include<string>


void approximateRGB(Pixel &p)
{

	p.r = p.r / 32 + 1;
	p.g = p.g / 32 + 1;
	p.b = p.b / 32 + 1;

}

void test()
{

	fstream file("imagelist.txt");
	if (!file)
		exit(1);

	CImage image;
	int iHeight, iWidth;
	Pixel node;
	vector<Pixel> nodes;
	string imageName;
	int dimension = 0;
	fstream outfile("extractFeatures.txt");
	int times = 0;

	cout << "Please input dimension:";
	cin >> dimension;// ‰»ÎÃÿ’˜Œ¨∂»

	while (getline(file, imageName))
	{
		times++;
		nodes.swap(vector<Pixel>());

		imageName = "image/" + imageName;
		image.Load(imageName.c_str());

		iHeight = image.GetHeight();
		iWidth = image.GetWidth();

		for (int iRow = 0; iRow<iWidth; iRow+=2)
			for (int iCol = 0; iCol<iHeight; iCol+=2)
			{
				COLORREF colorref = image.GetPixel(iRow, iCol);

				if (colorref == CLR_INVALID)
				{
					cout << "Out of range!";
					continue;
				}

				node.r = GetRValue(colorref);
				node.g = GetGValue(colorref);
				node.b = GetBValue(colorref);

				approximateRGB(node);
				nodes.push_back(node);
			}

		image.Destroy();

		KMeans KM(nodes, dimension);

		int *result = KM.kmeans();

		cout << times << ": ";
		for (int i = 0; i < dimension; i++)
		{
			cout << result[i] << " ";
			outfile << result[i] << " ";
		}

		cout << endl;
		outfile << endl;
	}

}