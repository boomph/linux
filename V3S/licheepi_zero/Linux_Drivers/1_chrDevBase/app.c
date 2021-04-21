#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>



int main(int argc,char* argv[])
{
    int fd = 0;
    char buf_r[100];
    size_t count_r=100;
    char buf_w[100];
    size_t count_w=100;

    //main open
    fd = open("/dev/mychrdev",O_RDWR);
    if(fd < 0)
    {
        printf("error:  main->open.\r\n");
        return -1;
    }

    //main read
    if(read(fd,buf_r,count_r) < 0)
    {
        printf("error:  main->read.\r\n");
        return -1;
    }

    //main write
    if(write(fd,buf_w,count_w) < 0)
    {
        printf("error:  main->write.\r\n");
        return -1;
    }

    //main close
    if(close(fd) < 0)
    {
        printf("error:  main->close.\r\n");
        return -1;
    }


    return 0;
}