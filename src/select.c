#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h> 
#include <strings.h>

int main()
{
	int ret;
	char buf[100];
	int timecount;
	int maxfd;
	fd_set rfds;//设置监听读集合
	struct timeval tv;//设置等待时间，0不等待，NULL一直等待。
		
	FD_ZERO(&rfds);//清空集合

/*
*	通常，一个进程启动时，都会打开 3 个文件：标准输入、标准输出和标准出错处理。这
*  	3 个文件分别对应文件描述符为 0、1 和 2（也就是宏替换 STDIN_FILENO、STDOUT_FILENO
*  	和 STDERR_FILENO，鼓励读者使用这些宏替换）。 
*/
		
	timecount = 0;
	while(1)
	{
        	FD_SET(STDIN_FILENO, &rfds);//把标准输入句柄0加入到集合中
		maxfd = STDIN_FILENO + 1;
		tv.tv_sec = 10;
		tv.tv_usec = 0;//设置等待时间
		ret = select(maxfd, &rfds, NULL, NULL, &tv);
		if(ret<0)
		{
			printf("select error, process will eixt\n");
			exit(0);
		}
		else if(FD_ISSET(STDIN_FILENO, &rfds))//测试是否有数据
		{
			fgets(buf, 100, stdin);
			if (!strncasecmp(buf, "quit", 4)) 
			{
				printf("exit test！\n");
				break;
			}
			printf("You input is %s\n",buf);
				
		}
		else
		{
			
			timecount++;
			printf("\ntime out: %d\n", timecount);
			
		}
	}
	return 0;
}
