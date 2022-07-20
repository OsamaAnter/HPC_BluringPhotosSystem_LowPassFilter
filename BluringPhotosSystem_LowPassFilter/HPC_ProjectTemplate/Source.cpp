//#include <iostream>
//#include <math.h>
//#include <stdlib.h>
//#include<string.h>
//#include<msclr\marshal_cppstd.h>
//#include <ctime>// include this header 
//#pragma once
//#include <mpi.h>
//#using <mscorlib.dll>
//#using <System.dll>
//#using <System.Drawing.dll>
//#using <System.Windows.Forms.dll>
//using namespace std;
//using namespace msclr::interop;
//
//int* inputImage(int* w, int* h, System::String^ imagePath) //put the size of image in w & h
//{
//	int* input;
//
//
//	int OriginalImageWidth, OriginalImageHeight;
//
//	//*********************************************************Read Image and save it to local arrayss*************************	
//	//Read Image and save it to local arrayss
//
//	System::Drawing::Bitmap BM(imagePath);
//
//	OriginalImageWidth = BM.Width;
//	OriginalImageHeight = BM.Height;
//	*w = BM.Width;
//	*h = BM.Height;
//	int *Red = new int[BM.Height * BM.Width];
//	int *Green = new int[BM.Height * BM.Width];
//	int *Blue = new int[BM.Height * BM.Width];
//	input = new int[BM.Height*BM.Width];
//	for (int i = 0; i < BM.Height; i++)
//	{
//		for (int j = 0; j < BM.Width; j++)
//		{
//			System::Drawing::Color c = BM.GetPixel(j, i);
//
//			Red[i * BM.Width + j] = c.R;
//			Blue[i * BM.Width + j] = c.B;
//			Green[i * BM.Width + j] = c.G;
//
//			input[i*BM.Width + j] = ((c.R + c.B + c.G) / 3); //gray scale value equals the average of RGB values
//
//		}
//
//	}
//	return input;
//}
//
//
//void createImage(int* image, int width, int height, int index)
//{
//	System::Drawing::Bitmap MyNewImage(width, height);
//
//
//	for (int i = 0; i < MyNewImage.Height; i++)
//	{
//		for (int j = 0; j < MyNewImage.Width; j++)
//		{
//			//i * OriginalImageWidth + j
//			if (image[i*width + j] < 0)
//			{
//				image[i*width + j] = 0;
//			}
//			if (image[i*width + j] > 255)
//			{
//				image[i*width + j] = 255;
//			}
//			System::Drawing::Color c = System::Drawing::Color::FromArgb(image[i*MyNewImage.Width + j], image[i*MyNewImage.Width + j], image[i*MyNewImage.Width + j]);
//			MyNewImage.SetPixel(j, i, c);
//		}
//	}
//	MyNewImage.Save("..//Data//Output//outputRes" + index + ".png");
//	cout << "result Image Saved " << index << endl;
//}
//
//
//int sum(int* imageData, int ImageHeight, int ImageWidth, int j)
//{
//	int sum = 0;
//	int count = 0;
//	int count2 = 0;
//	for (; j < (ImageHeight * ImageWidth); j++)
//	{
//		sum += imageData[j];
//		count++;
//		if (count == 3)
//		{
//			count = 0;
//			count2++;
//			j = j + ImageWidth - 2;
//
//		}
//		if (count2 == 3)
//		{
//			count2 = 0;
//			break;
//		}
//
//	}
//	return (sum / 9);
//
//
//}
//
//int main()
//{
//	int ImageWidth = 4, ImageHeight = 4;
//
//	int start_s, stop_s, TotalTime = 0;
//
//	System::String^ imagePath;
//	std::string img;
//	img = "..//Data//Input//test.png";
//
//	int size, rank;
//	MPI_Init(NULL, NULL);
//
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//	imagePath = marshal_as<System::String^>(img);
//	int* imageData = inputImage(&ImageWidth, &ImageHeight, imagePath);
//
//	start_s = clock();
//
//	int num_ofRows;
//	MPI_Status stat;
//
//	if (rank == 0)
//	{
//		cout << "____________> before image read\n";
//		int* imageData = inputImage(&ImageWidth, &ImageHeight, imagePath);
//		cout << "____________> image read\n";
//		num_ofRows = ImageHeight / (size - 1);
//		MPI_Send(imageData, ImageWidth * (num_ofRows + 1), MPI_INT, 1, 0, MPI_COMM_WORLD);
//		cout << "sent part to machine 1\n";
//		MPI_Send(&imageData[((ImageWidth* ImageWidth) - num_ofRows - ImageWidth)], ImageWidth * (num_ofRows + 1), MPI_INT, size - 1, 0, MPI_COMM_WORLD);
//		cout << "sent part to machine size - 1\n";
//		for (int i = 2; i < size - 1; i++) {
//			MPI_Send(&imageData[(num_ofRows * (i - 1)* ImageWidth) - ImageWidth], ImageWidth * (num_ofRows + 2), MPI_INT, i, 0, MPI_COMM_WORLD);
//				cout << "sent part to machine " << i << endl;;
//		}
//
//	}
//	MPI_Bcast(&ImageHeight, 1, MPI_INT, 0, MPI_COMM_WORLD);
//	//cout << "Bcast height\n";
//	MPI_Bcast(&ImageWidth, 1, MPI_INT, 0, MPI_COMM_WORLD);
//	//cout << "Bcast width\n";
//	//MPI_Bcast(&imageData, 1, MPI_INT, 0, MPI_COMM_WORLD);
//	MPI_Bcast(&num_ofRows, 1, MPI_INT, 0, MPI_COMM_WORLD);
//	//cout << "Bcast #rows\n";
//
//
//	cout << ">>>>>>> Rank: " << rank << endl;
//
//	if (rank == 0) {
//		int* result = new int[(ImageHeight - 2) * (ImageWidth - 2)];
//		//int* recv = new int[(ImageWidth - 2) * (num_ofRows - 1)];
//		MPI_Recv(&result[0], (ImageWidth - 2) * (num_ofRows - 1), MPI_INT, 1, 0, MPI_COMM_WORLD, &stat);
//		cout << "recv localData from machine (((1))))\n";
//
//		for (int i = 2; i < size - 1; i++)
//		{
//			MPI_Recv(&result[((num_ofRows) * (i - 1) * (ImageWidth-2))], (ImageWidth - 2) * (num_ofRows), MPI_INT, i, 0, MPI_COMM_WORLD, &stat);
//			cout << "recv localData from machine " << i << endl;
//
//		}
//		MPI_Recv(&result[((ImageWidth - 2) * (num_ofRows - 1)) + ((ImageWidth - 2) * (num_ofRows))], (ImageWidth - 2) * (num_ofRows - 1), MPI_INT, size - 1, 0, MPI_COMM_WORLD, &stat);
//		cout << "recv localData from machine size - 1\n";
//		createImage(result, ImageWidth - 2, (ImageHeight - 2), 0);
//		free(result);
//	}
//	else if (rank == 1)
//	{
//		cout << "ANA RANK 111111111111111\n";
//		int* arr = new int[ImageWidth * (num_ofRows + 1)];
//		int* localData = new int[(ImageWidth - 2) * (num_ofRows - 1)];
//		int temp = 0;
//		MPI_Recv(arr, ImageWidth * (num_ofRows + 1), MPI_INT, 0, 0, MPI_COMM_WORLD, &stat);
//		cout << "recv part from 0 in 1\n";
//
//		for (int i = 0; i < ImageWidth * (num_ofRows + 1); i++)
//		{
//			temp++;
//
//			// get the end of matrix
//			if (i == (ImageWidth * (num_ofRows+1)) - (2 * ImageWidth) - 2)
//			{
//				break;
//			}
//
//			//to move Block
//			if (temp == ImageWidth - 1)
//			{
//				temp = 0;
//				i += 2;
//			}
//			localData[i] = sum(arr, (num_ofRows + 1), ImageWidth, i);
//		}
//	
//
//		MPI_Send(localData, (ImageWidth - 2) * (num_ofRows - 1), MPI_INT, 0, 0, MPI_COMM_WORLD);
//		cout << "sent localData to 0 in 1\n";
//
//	}
//
//	else if (rank == size - 1)
//	{
//		int* arr = new int[ImageWidth * (num_ofRows + 1)];
//		MPI_Recv(arr, ImageWidth * (num_ofRows + 1), MPI_INT, 0, 0, MPI_COMM_WORLD, &stat);
//		cout << "recv part from 0 in size - 1\n";
//
//		int* localData = new int[(ImageWidth - 2) * (num_ofRows)];
//		int temp = 0;
//		for (int i = 0; i < ImageWidth * (num_ofRows + 1); i++)
//		{
//			temp++;
//
//			// get the end of matrix
//			if (i == (ImageWidth * (num_ofRows+1)) - (2 * ImageWidth) - 2)
//			{
//				break;
//			}
//
//			//to move Block
//			if (temp == ImageWidth - 1)
//			{
//				temp = 0;
//				i += 2;
//			}
//			localData[i] = sum(arr, (num_ofRows + 1), ImageWidth, i);
//		}
//		
//		MPI_Send(localData, (ImageWidth - 2) * (num_ofRows - 1), MPI_INT, 0, 0, MPI_COMM_WORLD);
//		cout << "sent to 0 localData in size - 1\n";
//
//	}
//	else if (rank != 0 && rank != (size - 1) && rank != (1))
//	{
//		int* arr = new int[ImageWidth * (num_ofRows + 2)];
//		MPI_Recv(arr, ImageWidth * (num_ofRows + 2), MPI_INT, 0, 0, MPI_COMM_WORLD, &stat);
//		cout << "recv part from 0 in " << rank << endl;;
//
//		int* localData = new int[(ImageWidth - 2) * (num_ofRows)];
//		int temp = 0;
//		for (int i = 0; i < ImageWidth * (num_ofRows + 2); i++)
//		{
//			temp++;
//
//			// get the end of matrix
//			if (i == (ImageWidth * (num_ofRows+2)) - (2 * ImageWidth) - 2)
//			{
//				break;
//			}
//
//			//to move Block
//			if (temp == ImageWidth - 1)
//			{
//				temp = 0;
//				i += 2;
//			}
//			localData[i] = sum(arr, (num_ofRows + 1), ImageWidth, i);
//		}
//
//		MPI_Send(localData, (ImageWidth - 2) * (num_ofRows), MPI_INT, 0, 0, MPI_COMM_WORLD);
//		cout << "sent to 0 localData in " << rank << endl;;
//
//	}
//	//createImage(imageData, ImageWidth, ImageHeight, 0);
//	stop_s = clock();
//	TotalTime += (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
//	cout << "time: " << TotalTime << endl;
//
//	//free(imageData);
//
//	return 0;
//
//}
//
//
//





//#include <iostream>
//#include <math.h>
//#include <mpi.h> ////
//#include <stdio.h>////
//#include <stdlib.h>
//#include <string.h>
//#include <msclr\marshal_cppstd.h>
//#include <ctime>// include this header
//#pragma once
//
//#using <mscorlib.dll>
//#using <System.dll>
//#using <System.Drawing.dll>
//#using <System.Windows.Forms.dll>
//using namespace std;
//using namespace msclr::interop;
//
//int* inputImage(int* w, int* h, System::String^ imagePath) //put the size of image in w & h
//{
//	int* input;
//
//
//	int OriginalImageWidth, OriginalImageHeight;
//
//	//********************Read Image and save it to local arrayss********
//	//Read Image and save it to local arrayss
//
//	System::Drawing::Bitmap BM(imagePath);
//
//	OriginalImageWidth = BM.Width;
//	OriginalImageHeight = BM.Height;
//	*w = BM.Width;
//	*h = BM.Height;
//	int* Red = new int[BM.Height * BM.Width];
//	int* Green = new int[BM.Height * BM.Width];
//	int* Blue = new int[BM.Height * BM.Width];
//	input = new int[BM.Height * BM.Width];
//	for (int i = 0; i < BM.Height; i++)
//	{
//		for (int j = 0; j < BM.Width; j++)
//		{
//			System::Drawing::Color c = BM.GetPixel(j, i);
//
//			Red[i * BM.Width + j] = c.R;
//			Blue[i * BM.Width + j] = c.B;
//			Green[i * BM.Width + j] = c.G;
//
//			input[i * BM.Width + j] = ((c.R + c.B + c.G) / 3); //gray scale value equals the average of RGB values
//
//		}
//
//	}
//	return input;
//}
//void createImage(int* image, int width, int height, int index)
//{
//	System::Drawing::Bitmap MyNewImage(width, height);
//
//
//	for (int i = 0; i < MyNewImage.Height; i++)
//	{
//		for (int j = 0; j < MyNewImage.Width; j++)
//		{
//			//i * OriginalImageWidth + j
//			if (image[i * width + j] < 0)
//			{
//				image[i * width + j] = 0;
//			}
//			if (image[i * width + j] > 255)
//			{
//				image[i * width + j] = 255;
//			}
//			System::Drawing::Color c = System::Drawing::Color::FromArgb(image[i * MyNewImage.Width + j], image[i * MyNewImage.Width + j], image[i * MyNewImage.Width + j]);
//			MyNewImage.SetPixel(j, i, c);
//		}
//	}
//	MyNewImage.Save("..//Data//Output//outputRes" + index + ".png");
//	std::cout << "result Image Saved " << index << endl;
//}
//int sum(int* imageData, int ImageWidth, int j)
//{
//	int sum = 0;
//	int count = 0;
//	int count2 = 0;
//	for (; j < 9; j++)
//	{
//		sum += imageData[j];
//		count++;
//		if (count == 3)
//		{
//			count = 0;
//			count2++;
//			j = j + ImageWidth - 2;
//
//		}
//		if (count2 == 3)
//		{
//			count2 = 0;
//			break;
//		}
//
//	}
//	return ceil(sum / 9);
//}
//
//int main(int args, char** argv)
//{
//	MPI_Init(NULL, NULL);
//	int size, rank;
//	MPI_Comm_size(MPI_COMM_WORLD, &size); //processors number
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //processor id
//	int ImageWidth = 4, ImageHeight = 4; //imgwidth=cols ,,imgheight=rows
//	int* imageData = NULL; //1d img data
//	int processLenght, start, end, recvcount, /*subStart*/remenderlength;
//	int* subarr = NULL, * subarrres = NULL;//contain sub send data
//	int* resultMatrix = new int[(ImageHeight - 2) * (ImageWidth - 2)];
//	int StartCalc = 0;
//	//cout << "Size Of Processor" << size;
//	MPI_Status stut;
//	if (rank == 0)
//	{
//		// start get img data
//		System::String^ imagePath;
//		std::string img;
//		img = "..//Data//Input//test.png"; //img path
//		imagePath = marshal_as<System::String^>(img);
//		imageData = inputImage(&ImageWidth, &ImageHeight, imagePath);
//		// end get img data
//		//start split the data 1darr
//		processLenght = (ImageHeight / size) * ImageWidth; //need to be send to other process //kam height
//		remenderlength = (ImageHeight % size) * ImageWidth;
//		for (int i = 1; i < size; i++)
//		{
//			start = i * processLenght; //zero index
//			if (i == size - 1)
//			{
//				processLenght += remenderlength;
//			}
//			MPI_Send(&processLenght, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
//			MPI_Send(&ImageHeight, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
//			MPI_Send(&ImageWidth, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
//			if (i == size - 1)
//			{
//				std::cout << "sending data to processor " << i << endl;
//				recvcount = processLenght + ImageWidth;
//				MPI_Send(&recvcount, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
//				MPI_Send(&imageData[start - ImageWidth], recvcount, MPI_INT, i, 0, MPI_COMM_WORLD);
//			}
//			else
//			{
//				std::cout << "sending data to processor " << i << endl;
//				recvcount = processLenght + ImageWidth * 2;
//				MPI_Send(&recvcount, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
//				MPI_Send(&imageData[start - ImageWidth], recvcount, MPI_INT, i, 0, MPI_COMM_WORLD);
//			}
//
//		}
//
//		std::cout << "Satrt Bluring processor 0 ";
//		recvcount = processLenght + ImageWidth;
//		subarrres = new int[recvcount - (2 * (ImageWidth - 2)) - 2 * (ImageHeight / size)];
//		int  CounterClm = 0, index = 0;
//		StartCalc = 0;
//		while (true)// infinty loop
//		{
//			CounterClm++;
//			if (StartCalc == ((recvcount)-(2 * ImageWidth) - 2))
//			{
//				std::cout << "finish Bluring in processor 0";
//				break;
//			}
//			// if End Of Matrix
//
//			if (CounterClm / (ImageWidth - 1) == 1) //end of Row
//			{
//				CounterClm = 0;
//				StartCalc += 2;
//			}
//			resultMatrix[index] = sum(imageData, (ImageWidth), StartCalc);
//			index++;
//			StartCalc++;
//		}
//
//
//	}
//	else if (rank < size) //start recv data
//	{
//
//		MPI_Recv(&processLenght, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &stut);
//		MPI_Recv(&ImageHeight, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &stut);
//		MPI_Recv(&ImageWidth, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &stut);
//		MPI_Recv(&recvcount, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &stut);
//		subarr = new int[recvcount];
//		MPI_Recv(subarr, recvcount, MPI_INT, 0, 0, MPI_COMM_WORLD, &stut);
//		std::cout << "recieve processor " << rank << endl;
//		
//
//		std::cout << "Starting Bluring ..." << endl;
//		int StartCalc = 0, CounterClm = 0, index = 0;
//		vector<int> tmpMatrix;
//		for (int i = 0; i < recvcount; i++)
//		{
//			tmpMatrix.push_back(0);
//		}
//		while (true)// infinty loop
//		{
//			CounterClm++;
//			// if End Of Matrix
//			if (StartCalc == ((recvcount)-(2 * ImageWidth) - 2))
//			{
//				std::cout << "finish bluring in processor " << rank << endl;
//				//cout << "sub res "<< subarrres[index] <<endl;
//				
//				break;
//			}
//			else if (CounterClm == (ImageWidth - 1)) //end of Row
//			{
//				CounterClm = 0;
//				StartCalc += 2;
//			}
//			int sum = 0;
//			int count = 0;
//			int count2 = 0;
//			for (int j = StartCalc; j < StartCalc + 9; j++)
//			{
//				sum += subarr[j];
//				count++;
//				if (count == 3)
//				{
//					count = 0;
//					count2++;
//					j = j + ImageWidth - 2;
//
//				}
//				if (count2 == 3)
//				{
//					count2 = 0;
//					break;
//				}
//
//			}
//			tmpMatrix.push_back(ceil(sum / 9));
//			//cout << "sub res " << (sum / 9) << endl;
//			//subarrres[index] = ceil(sum / 9);
//			//cout << "sub res " << subarrres[index] << endl;
//			//subarrres[index] = sum(subarr, (ImageWidth), StartCalc);
//			index++;
//			StartCalc++;
//		}
//		
//		if (rank == size - 1)
//		{
//			
//			//recvcount = recvcount - (2* (ImageWidth - 2) + 2 * (ImageHeight / size) + 2 * (ImageHeight % size));
//			recvcount = tmpMatrix.size();
//			int tmp;
//			for (int i = 0; i < recvcount; i++)
//			{
//				if (tmpMatrix[i] == 0)
//				{
//					tmp = i;
//					break;
//				}
//				subarrres[i] = tmpMatrix[i];
//			}
//			recvcount = tmp;
//			MPI_Send(&recvcount, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
//			
//			MPI_Send(subarrres, recvcount, MPI_INT, 0, 0, MPI_COMM_WORLD);
//			std::cout << "finish sending from..  " << rank << endl;
//
//		}
//		else
//		{
//			recvcount = tmpMatrix.size();
//			int tmp;
//			for (int i = 0; i < recvcount; i++)
//			{
//				if (tmpMatrix[i] == 0)
//				{
//					tmp = i;
//					break;
//				}
//				subarrres[i] = tmpMatrix[i];
//			}
//			recvcount = tmp;
//			//recvcount = recvcount - ((ImageWidth - 2) + 2 * (ImageHeight / size));
//			MPI_Send(&recvcount, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
//			MPI_Send(&subarrres, recvcount, MPI_INT, 0, 0, MPI_COMM_WORLD);//////
//			std::cout << "finish sending from..   " << rank << endl;
//		}
//	} //end recv data
//
//	std::cout << "Ana Rank /////////////////"<<rank;
//	if (rank == 0)//collect data
//	{
//		std::cout << "Collect Data ";
//		int var = StartCalc;
//		for (int j = 1; j < size; j++)
//		{
//			int x;
//			MPI_Recv(&x, 1, MPI_INT, j, 0, MPI_COMM_WORLD, &stut);//rank j
//			subarr = new int[x];
//			MPI_Recv(subarr, x, MPI_INT, j, 0, MPI_COMM_WORLD, &stut);//rank j
//			for (int i = 0; i < x; i++)
//			{
//				resultMatrix[var++] = subarr[i];
//				
//			}
//
//		}
//
//		//make img
//		//start clock times
//		int start_s, stop_s, TotalTime = 0;
//		start_s = clock();
//		createImage(resultMatrix, ImageWidth - 2, ImageHeight - 2, 0);
//		stop_s = clock();
//		TotalTime += (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
//		std::cout << "time: " << TotalTime << endl;
//		free(imageData);
//	}
//	MPI_Finalize();
//	return 0;
//}



#include <iostream>
#include <math.h>
#include <mpi.h> ////
#include <stdio.h>////
#include <stdlib.h>
#include <string.h>
#include <msclr\marshal_cppstd.h>
#include <ctime>// include this header 
#pragma once

#using <mscorlib.dll>
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>
using namespace std;
using namespace msclr::interop;

int* inputImage(int* w, int* h, System::String^ imagePath) //put the size of image in w & h
{
	int* input;


	int OriginalImageWidth, OriginalImageHeight;

	//*********************************************************Read Image and save it to local arrayss*************************	
	//Read Image and save it to local arrayss

	System::Drawing::Bitmap BM(imagePath);

	OriginalImageWidth = BM.Width;
	OriginalImageHeight = BM.Height;
	*w = BM.Width;
	*h = BM.Height;
	int* Red = new int[BM.Height * BM.Width];
	int* Green = new int[BM.Height * BM.Width];
	int* Blue = new int[BM.Height * BM.Width];
	input = new int[BM.Height * BM.Width];
	for (int i = 0; i < BM.Height; i++)
	{
		for (int j = 0; j < BM.Width; j++)
		{
			System::Drawing::Color c = BM.GetPixel(j, i);

			Red[i * BM.Width + j] = c.R;
			Blue[i * BM.Width + j] = c.B;
			Green[i * BM.Width + j] = c.G;

			input[i * BM.Width + j] = ((c.R + c.B + c.G) / 3); //gray scale value equals the average of RGB values

		}

	}
	return input;
}
void createImage(int* image, int width, int height, int index)
{
	System::Drawing::Bitmap MyNewImage(width, height);


	for (int i = 0; i < MyNewImage.Height; i++)
	{
		for (int j = 0; j < MyNewImage.Width; j++)
		{
			//i * OriginalImageWidth + j
			if (image[i * width + j] < 0)
			{
				image[i * width + j] = 0;
			}
			if (image[i * width + j] > 255)
			{
				image[i * width + j] = 255;
			}
			System::Drawing::Color c = System::Drawing::Color::FromArgb(image[i * MyNewImage.Width + j], image[i * MyNewImage.Width + j], image[i * MyNewImage.Width + j]);
			MyNewImage.SetPixel(j, i, c);
		}
	}
	MyNewImage.Save("..//Data//Output//outputRes" + index + ".png");
	cout << "result Image Saved " << index << endl;
}
int sum(int* imageData, int ImageWidth, int j)
{
	int sum = 0;
	int count = 0;
	int count2 = 0;
	for (; j < 9 + j; j++)
	{
		sum += imageData[j];
		count++;
		if (count == 3)
		{
			count = 0;
			count2++;
			j = j + ImageWidth - 2;

		}
		if (count2 == 3)
		{
			count2 = 0;
			break;
		}

	}
	return ceil(sum / 9);
}

int main(int args, char** argv)
{
	MPI_Init(NULL, NULL);
	int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size); //processors number
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //processor id
	int ImageWidth = 4, ImageHeight = 4; //imgwidth=cols ,,imgheight=rows
	int* imageData = NULL; //1d img data
	int processLenght, start, end, recvcount, subStart, remenderlength;
	int new_Size;
	int* subarr = NULL;//contain sub send data
	MPI_Status stut;
	if (rank == 0)
	{
		// start get img data
		System::String^ imagePath;
		std::string img;
		img = "..//Data//Input//test2.png";     //img path
		imagePath = marshal_as<System::String^>(img);
		imageData = inputImage(&ImageWidth, &ImageHeight, imagePath);

		// end get img data
		//start split the data	1darr
		processLenght = (ImageHeight / size) * ImageWidth; //need to be send to other process //kam height
		remenderlength = (ImageHeight % size) * ImageWidth;
		for (int i = 1; i < size; i++)
		{
			start = i * processLenght; //zero index 
			if (i == size - 1) processLenght += remenderlength;
			subStart = ImageWidth;
			//MPI_Send(&processLenght, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(&ImageHeight, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(&ImageWidth, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(&subStart, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			if (i == size - 1)
			{

				recvcount = processLenght + ImageWidth;
				MPI_Send(&recvcount, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
				MPI_Send(&imageData[start - ImageWidth], recvcount, MPI_INT, i, 0, MPI_COMM_WORLD);
				new_Size = (ImageWidth - 2) * ((recvcount / ImageWidth) - 2);
				MPI_Send(&new_Size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

			}
			else
			{

				recvcount = processLenght + ImageWidth * 2;
				MPI_Send(&recvcount, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
				MPI_Send(&imageData[start - ImageWidth], recvcount, MPI_INT, i, 0, MPI_COMM_WORLD);
				new_Size = (ImageWidth - 2) * ((recvcount / ImageWidth) - 2);
				MPI_Send(&new_Size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

			}
		}
		//process 0 data
		processLenght = (ImageHeight / size) * ImageWidth;
		//if (size > 1)
		recvcount = processLenght + ImageWidth;
		//else
			//recvcount = processLenght;
		subStart = 0;
		subarr = new int[recvcount];
		for (int i = 0; i < recvcount; i++)
			subarr[i] = imageData[i];
		//end split the data 1darr
		new_Size = (ImageWidth - 2) * ((recvcount / ImageWidth) - 2);

	}
	if (rank < size && (rank != 0))  //start recv data 
	{
		//MPI_Recv(&processLenght, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &stut);
		MPI_Recv(&ImageHeight, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &stut);
		MPI_Recv(&ImageWidth, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &stut);
		MPI_Recv(&subStart, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &stut);
		MPI_Recv(&recvcount, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &stut);
		subarr = new int[recvcount];
		MPI_Recv(subarr, recvcount, MPI_INT, 0, 0, MPI_COMM_WORLD, &stut);
		MPI_Recv(&new_Size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &stut);

	} //end recv data
	//start process code
	int* subArrSum = new int[new_Size];//for answer data

	std::cout << "Starting Bluring ..." << endl;
	int* resultMatrix = new int[(ImageHeight - 2) * (ImageWidth - 2)];
	int StartCalc = 0, CounterClm = 0, index = 0;
	std::cout << "Loading ..." << endl;
	while (true)// infinty loop
	{
		CounterClm++;
		// if End Of Matrix
		if (StartCalc == (recvcount - (2 * ImageWidth) - 2))
		{
			break;
		}
		else if (CounterClm == (ImageWidth - 1)) //end of Row
		{
			CounterClm = 0;
			StartCalc += 2;
		}
		subArrSum[index] = sum(subarr, (ImageWidth), StartCalc);
		index++;
		StartCalc++;
	}

	if (rank >= 1)//send answer data
	{
		int tmp = new_Size;
		MPI_Send(&tmp, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(subArrSum, tmp, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	if (rank == 0)//collect data
	{
		int inc = 0;
		for (int i = 0; i < new_Size; i++)
			resultMatrix[inc++] = subArrSum[i];

		for (int j = 1; j < size; j++)
		{
			int tmp;
			MPI_Recv(&tmp, 1, MPI_INT, j, 0, MPI_COMM_WORLD, &stut);//rank j
			MPI_Recv(subArrSum, tmp, MPI_INT, j, 0, MPI_COMM_WORLD, &stut);//rank j
			for (int i = 0; i < tmp; i++)
				resultMatrix[inc++] = subArrSum[i];
		}
		//make img
			//start clock times
		int start_s, stop_s, TotalTime = 0;
		start_s = clock();
		createImage(resultMatrix, ImageWidth - 2, ImageHeight - 2, 0);
		stop_s = clock();
		TotalTime += (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
		cout << "time: " << TotalTime << endl;
		free(resultMatrix);
	}
	MPI_Finalize();
	return 0;
}
