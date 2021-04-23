#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


int main(int argc,char* argv[])
{
    int fd = 0;
    ssize_t szRead;
    char bufRead[100];
    size_t countRead=100;

    ssize_t szWrite;
    char bufWrite[100];
    size_t countWrite=100;

    fd = open(argv[1],O_RDWR);
    if(fd <= 0)
    {
        printf("err:main->open.\r\n");
        return 0;
    }

    szRead = read(fd,bufRead,countRead);
    if(szRead < 0)
    {
        printf("err:main->read.\r\n");
        return 0;
    }

    if(argv[2][0] == '0')
        bufWrite[0]=0;
    else
        bufWrite[1]=1;

    szWrite = write(fd,bufWrite,1);
    if(szWrite < 0)
    {
        printf("err:main->write.\r\n");
        return 0;
    }

    if(close(fd) < 0)
    {
        printf("err:main->close.\r\n");
        return 0;
    }



    return 0;
}