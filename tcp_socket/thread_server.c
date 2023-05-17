/*
 * server.c为服务器端代码
*/

#include "config.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>


void *thread(void *connfd)
{
    ssize_t n;
	char buff[MAX_LINE];
	int connfd_new = *(int *)connfd;
	printf("thread connfd_new %d\n",connfd_new);
	while((n = read(connfd_new , buff , MAX_LINE)) > 0)
	{
		printf("write thread connfd_new %d-->data:%s\n",connfd_new,buff);
		write(connfd_new , buff , n);
	}
    return NULL;
}


int main(int argc , char **argv)
{
	/*声明服务器地址和客户链接地址*/
	struct sockaddr_in servaddr , cliaddr;

	/*声明服务器监听套接字和客户端链接套接字*/
	int listenfd , connfd;
	pid_t childpid;

	/*声明缓冲区*/
	char buf[MAX_LINE];

	socklen_t clilen;

	/*(1) 初始化监听套接字listenfd*/
	if((listenfd = socket(AF_INET , SOCK_STREAM , 0)) < 0)
	{
		perror("socket error");
		exit(1);
	}//if

	/*(2) 设置服务器sockaddr_in结构*/
	bzero(&servaddr , sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //表明可接受任意IP地址
	servaddr.sin_port = htons(PORT);

	/*(3) 绑定套接字和端口*/
	if(bind(listenfd , (struct sockaddr*)&servaddr , sizeof(servaddr)) < 0)
	{
		perror("bind error");
		exit(1);
	}//if

	/*(4) 监听客户请求*/
	if(listen(listenfd , LISTENQ) < 0)
	{
		perror("listen error");
		exit(1);
	}//if

	/*(5) 接受客户请求*/
	for( ; ; )
	{
		clilen = sizeof(cliaddr);
		if((connfd = accept(listenfd , (struct sockaddr *)&cliaddr , &clilen)) < 0 )
		{
			perror("accept error");
			exit(1);
		}//if

		pthread_t pth;
		int ret = pthread_create(&pth, NULL, thread, &connfd);
	}//for
	
	/*(6) 关闭监听套接字*/
	close(listenfd);
}
