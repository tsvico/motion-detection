#include<iostream>
#include"opencv2/opencv.hpp"  
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<stdio.h>
#include<unistd.h>
using namespace std;
using namespace cv;

int main()
{
	//读入视频
	//VideoCapture capture("CarLights2.avi");
	VideoCapture capture(0);//如果是笔记本，0打开的是自带的摄像头，1 打开外接的相机 
	//namedWindow("camera",WINDOW_AUTOSIZE);
	//namedWindow("moving area",WINDOW_AUTOSIZE);
	Mat tempframe, currentframe, previousframe;
	Mat frame;
	int framenum = 0;
	 int num=0;
		//读取一帧处理
	while (true)
	{
		if(!capture.isOpened())
		{
			cout << "read video failure" << endl;
			return - 1;
		}
		//tempframe = capture.read(frame);


		capture >> frame;
		tempframe = frame;
		framenum++; 
		if (framenum == 1)
		{
			cvtColor(tempframe, previousframe, CV_BGR2GRAY);
		}
		if (framenum >= 2)
		{
			Mat currentframe1,currentframe2, currentframe3, currentframe4;
			cvtColor(tempframe, currentframe, CV_BGR2GRAY);//转化为单通道灰度图，此时currentFrame已经存了tempFrame的内容 
			absdiff(currentframe,previousframe,currentframe);//做差求绝对值  
			threshold(currentframe, currentframe, 20, 255.0, CV_THRESH_BINARY);
			//dilate(currentframe, currentframe,Mat());//膨胀
		    //erode(currentframe, currentframe,Mat());//腐蚀
			//////////////*//////////
			int counter = 0;  
            // 访问mat中的像素  
            for (int i=0; i<currentframe.rows; i++)  
            {  
                uchar *data = currentframe.ptr<uchar>(i); //获取每一行的指针  
                for (int j=0;j<currentframe.cols; j++)  
                {  
                    if (data[j] == 255) //访问到像素值  
                    {  
                        counter++;  
                    }                     
                }  
            }  
           
            char OutName[100];
            
             //录制视频
                double rate = 25.0; //视频的帧率
                Size videoSize(1280,960);  
                bool mm=false;
            if (counter > 8000) //达到阈值的像素数达到一定的数量则保存该图像  
            { 
               cout<<"是不是有东西在动～"<<endl;
                sprintf(OutName,"./img/%d.jpg",++num);
                imwrite(OutName,tempframe);  
                mm=true;
            }  
			
			if(num%15==0)
			    system("clear");//清屏
			if(mm){
			    //录视频
               VideoWriter writer("1.avi",CV_FOURCC('M','J','P','G'),rate,videoSize);
              // sleep(5);
               }
			 
			
			//////////////////////////
			//显示图像  
			imshow("camera", tempframe);
			imshow("moving area", currentframe);

		}
		//把当前帧保存作为下一次处理的前一帧  
		cvtColor(tempframe, previousframe, CV_BGR2GRAY);
		if (waitKey(20) == 27)//27是键盘摁下esc时，计算机接收到的ascii码值  
        {  
            break;  
        } 
		waitKey(30); //延时30ms  
		
	}//end while  
}
