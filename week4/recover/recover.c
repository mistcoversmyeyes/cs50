#include <stdio.h>
#include <stdlib.h>

 
int main(int argc, char *argv[]){
    if (argc == 1 || argc > 2){
        printf("你似乎没有输入你想恢复的文件\n");
        return 1;
    }
    
    FILE *file_ptr = fopen(argv[1],"r");
    if (file_ptr == NULL){
        printf("似乎文件打不开,换一个文件吧\n");
        return 1;
    }




    //开始512byte 的读取
    unsigned char *buffer = malloc(512);//自行划定一个缓冲区用于存储临时二进制数据(缓冲区的数据类型不重要!不重要!不重要!)
    int file_num = 0;
    char *file_name = malloc(15);
    FILE *outfile = NULL;
    
    while (fread(buffer,512,1,file_ptr) == 1){
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff){
            if (outfile != NULL){
                fclose(outfile);
            }
            sprintf(file_name,"picture%03i.jpg",file_num++);
            
            outfile = fopen(file_name,"w");

            if (outfile != NULL){            
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
    free(file_name);
}