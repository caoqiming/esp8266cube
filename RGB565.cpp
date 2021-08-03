#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
#include "udpclient.hpp"
//using namespace cv;

using boost::asio::ip::udp;
using std::string;
using std::cout;
using std::endl;
#define TARGETH 230
#define TARGETW 230

void make_command(string c, char* data){
	if(data==nullptr){
		cout<<"make_command get nullptr"<<endl;
		return;
	}
	if(c=="pic1"){
		*data=0x00;// 第一部分数据
	}else if(c=="pic2"){
		*data=0x01;// 第二部分数据
	}else if(c=="pic3"){
		*data=0x02;// 第三部分数据
	}
	else if(c=="pic_size"){
		*data=0x03;// 图片大小 显示x 显示y
	}
	
}

void get_pic_size(const int &size,int &size_1,int &size_3){ //根据图片大小获取图片每个包的大小，一个图片分三个包发送,size2和size1相同
	size_1 = size/3;
	size_3 = size - 2*size_1;
}

void rgb565(cv::Mat &image_resized,uint16_t *&data ,size_t &data_size){
    int target_w=image_resized.cols;
    int target_h=image_resized.rows;
    data_size=target_w*target_h;
    data=new uint16_t[data_size];
    memset(data,0,data_size*2);
    uint16_t *data_p=data; 
    for(int row = 0; row < image_resized.rows; ++row) {
        uchar* p = image_resized.ptr(row); 
        for(int col = 0; col < image_resized.cols*3; ) { //B,G,R
            //B 8-3=5
            *data_p |= *(p+2)>>3; 
            *data_p <<=6;
            //G 8-2=6
            *data_p |= *(p+1)>>2;
            *data_p <<= 5;
            //R 8-3=5
            *data_p |= *(p+2)>>3;

            col+=3;
            p+=3;
            ++data_p;
        }
    }   
}

void reshape(cv::Mat &image, cv::Mat &image_resized){
    int width=image.cols;
    int height=image.rows;
    int target_w , target_h;
    if(width<height){
        target_h=TARGETH;
        target_w=TARGETW*width/height;
    }else if(width==height){
        target_h=TARGETH;
        target_w=TARGETW;
    }else{
        target_h=TARGETH*height/width;
        target_w=TARGETW;
    }
    resize(image,image_resized,cv::Size(target_w,target_h));
}

void save(){
    //cout<<argc<<endl;
    //if(argc < 2){
    //    cout<<"too few arg";
    //    return 0;
    //}
    //cv::Mat image;
    //image = cv::imread(argv[1]);
    //if(image.data== nullptr)
    //{
    //    cout<<"path error"<<endl;
    //    return 0;
    //}

    //cv::Mat image_resized;
    //reshape(image,image_resized);

    //uint16_t *data;
    //size_t data_size;
    //rgb565(image_resized,data,data_size);

    //size_t data_size_c = data_size * 2;
    //uchar* data_c = (uchar*)data;
    //    std::ofstream outfile;
    // save to pic.c to use in code
    //outfile.open("pic.c", std::ios::app);
    //outfile<<"const char picture["<<data_size_c<<"] ={"<<endl;
    //for(int i=0;i<data_size_c;++i){
    //    outfile<<"0x"<<std::hex<<static_cast<unsigned int>(*(data_c+i))<<", ";
    //    if(i%16==15)
    //        outfile<<endl;
    //}
    //outfile<<"};";
    //outfile.close();
    
     //save to binary
    //outfile.open("pic", std::ios::app | std::ios::binary);
    //outfile.write((char*)(data_c),data_size_c*2); // uint16_t 是两个字节
    //outfile.close();
    //delete []data;
    // waitKey( 0 );
}

int main(int argc, char* argv[]){
    //if(argc < 2){
    //    cout<<"too few arg";
    //    return 0;
    //}
    //cv::Mat image;
    //image = cv::imread(argv[1]);
    //if(image.data== nullptr)
    //{
    //    cout<<"path error"<<endl;
    //    return 0;
    //}

    cv::Mat image;
    image = cv::imread("cat.jpeg");
    cv::Mat image_resized;
    reshape(image,image_resized);

    uint16_t *data;
    size_t data_size;
    rgb565(image_resized,data,data_size);

    size_t data_size_c = data_size * 2;
    uchar* data_c = (uchar*)data;

    int a;

    std::cin >> a;
	boost::asio::io_service io_service;
	UDPClient client(io_service, "192.168.4.1", "2333");

    int size_1, size_3;
    get_pic_size(data_size_c, size_1, size_3);
    cout << "size0:" << size_1 << " size_2:" << size_3 << endl;
    char* data_1 = new char[size_1 + 1];
    char* data_2 = new char[size_1 + 1];
    char* data_3 = new char[size_3 + 1];
    make_command("pic1",data_1);
    make_command("pic2",data_2);
    make_command("pic3",data_3);
    memcpy(data_1 + 1, data, size_1);
    memcpy(data_2 + 1, data+size_1, size_1);
    memcpy(data_3 + 1, data+2*size_1, size_3);

    cout << "send pic1" << endl;
    client.send(data_1,size_1 + 1);
    std::cin >> a;

    cout << "send pic2" << endl;
    client.send(data_2,size_1 + 1);
    std::cin >> a;

    cout << "send pic3" << endl;
    client.send(data_3,size_3 + 1);
    std::cin >> a;

    delete []data;
    delete []data_1;
    delete []data_2;
    delete []data_3;
    return 0;
}
