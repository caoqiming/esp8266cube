#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using std::cout;
using std::endl;
#define TARGETH 240
#define TARGETW 240


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

int main(int argc, char* argv[]){
    cout<<argc;
    if(argc < 2){
        cout<<"参数太少";
        return 0;
    }
    cv::Mat image;
    image = cv::imread(argv[1]);
    if(image.data== nullptr)
    {
        cout<<"图片文件不存在"<<endl;
        return 0;
    }


    cv::Mat image_resized;
    reshape(image,image_resized);

    uint16_t *data;
    size_t data_size;
    rgb565(image_resized,data,data_size);


    
    // std::string image_name= static_cast<std::string>(argv[1]);
    // image_name=image_name.substr(image_name.find_last_of('/') + 1);
    std::ofstream outfile;
    // save to pic.c to use in code
    outfile.open("pic.c", std::ios::app);
    outfile<<"const uint16_t picture["<<data_size<<"] ={"<<endl;
    for(int i=0;i<data_size;++i){
        outfile<<"0x"<<std::hex<<*(data+i)<<", ";
        if(i%16==15)
            outfile<<endl;
    }
    outfile<<"}";
    outfile.close();
    
    // save to binary
    // outfile.open("pic", std::ios::app | std::ios::binary);
    // outfile.write((char*)(&data),data_size*2); // uint16_t 是两个字节
    // outfile.close();
    delete []data;
    // waitKey( 0 );
    return 0;
}
