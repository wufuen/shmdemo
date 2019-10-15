#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_NAME "shmdemo.c"

int main(int argc , void *argv[])
{
    unsigned char * buf = NULL;
    void * p_data = NULL;
    buf = malloc(10240);
    if(buf == NULL)
    {
        printf("malloc buf error\n");
        return -1;
    }

    int fd = open(FILE_NAME,O_RDONLY);
    if(fd < 0)
    {
        printf("cann't open file:%s\n",FILE_NAME);
        return -1;
    }

    int i = 0;
    int len = read(fd,buf,10240);
    if(len < 0)
    {
        printf("read file failed \n");
        close(fd);
        return -1;
    }

    do
    {
        putchar(buf[i]);
        i++;
    }while(len!=i);

    putchar('\n');
    char buf_map[10240];


    p_data = mmap(NULL,10240,PROT_READ,MAP_PRIVATE,fd,0);
    if(p_data == NULL)
    {
        printf("cann't mmap file\n");
        free(buf);
        close(fd);
        return -1;
    }
    memcpy(buf_map,p_data,i);
    
    i = 0;
    do
    {
        putchar(buf_map[i]);
        i++;
    }while(len!=i);



    munmap(p_data,10240);


    free(buf);
    close(fd);
    return 0;
}
