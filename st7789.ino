bool flag_pic_0=false;
bool flag_pic_1=false;
bool flag_pic_2=false;

void receive_handler(char* data){
  switch (*data){
    case 0: // 第一部分数据
      receive_pic(0,data+1);
      flag_pic_0=true;
      drow_pic();
      break;
    case 1: // 第二部分数据
      receive_pic(1,data+1);
      flag_pic_1=true;
      drow_pic();
      break;
    case 2: // 第二部分数据
      receive_pic(2,data+1);
      flag_pic_2=true;
      drow_pic();
      break;
  }
  
}

void receive_pic(int n, char* data){

}
void drow_pic(){
  if(flag_pic_0 && flag_pic_1 && flag_pic_2){
    flag_pic_0=false;
    flag_pic_1=false;
    flag_pic_2=false;
    
  }
}