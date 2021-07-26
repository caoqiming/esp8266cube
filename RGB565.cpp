#include <iostream>
#include "udpclient.hpp"

using std::string;
using std::cout;
using std::endl;

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


int main()
{
	boost::asio::io_service io_service;
	UDPClient client(io_service, "localhost", "2333");
	char *p=new char[20];
	strcpy(p,"hello");
	client.send(p,5);
	return 0;
}