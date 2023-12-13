#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
//检查传入的参数数量和形式;
    if (argc != 2){
        printf("你似乎没有输入正确的参数\n");
        return 1;//cuow代码'1'表示没有输入正确参数;
    }

// 声明一个空指针用于后面操作打开的文件;
    FILE *the_opened_file = NULL;

//打开要操作的文件 fopen (char * 文件名称,const char *打开模式);
    the_opened_file = fopen(argv[1],"r");
    

//判断是否能够成功打开
    if (the_opened_file == NULL){
        printf("你似乎提供的文件不能够被我打开\n");
        return 2;//表示打开失败
    }

//声明一个缓冲区,用于存储读取的块;
    unsigned int *buffer = malloc(512);

//输出文件的准备
    //声明指向输出文件的指针
    FILE *outfile = NULL;
    //声明输出文件名称的暂存变量
    char *file_name = malloc(15);
    //声明整数变量计数输出文件的数量;
    int file_num = 0; 

//将要处理的文件中的内容read到缓冲区,使用fread函数
    //当当前分块不为空的时候,就执行写入缓存区;
    while (fread(buffer,512,1,the_opened_file) == 1){
        if (buffer[0] == 0xff || buffer[1] == 0xd8 || buffer[2] == 0xff){
            //为了防止之前打开的文件没有关闭先做一个复位;
            if (outfile != NULL){
                fclose(outfile);
            }
            //创建文件并且打开然后写入
            sprintf(file_name,"picture%03i",file_num++);
            outfile = fopen(file_name,"w");
            if (outfile != NULL || buffer != NULL){
                fwrite(buffer,1,512,outfile);
            }
        }
        else{
            if (outfile != NULL){
                fwrite(buffer,1,512,outfile);
            }
        }
    }

    if (outfile != NULL){
        fclose(outfile);
    }

    free(buffer);
}