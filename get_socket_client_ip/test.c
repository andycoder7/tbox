#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>


int open_listenfd(int port)
{
	int listenfd,optval = 1;
	struct sockaddr_in serveraddr;

	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
		return -1;

	/*Eliminates "Address already in use" error from blind*/
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,
		      (const void *)&optval,sizeof(int)) < 0)
		return -1;

	bzero((char *) &serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short)port);
	if(bind(listenfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0)
			return -1;
	if(listen(listenfd,SOMAXCONN) < 0)
		return -1;
	return listenfd;
}

int main()
{
	int fd = open_listenfd(4900);
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr); //这里一定要初始化为sizeof(struct sockaddr)

	bzero((char*)&addr, sizeof(addr));
	int client = accept(fd, (struct sockaddr *) &addr, &len);
	printf("%s\n", inet_ntoa(addr.sin_addr));

	//已经可以拿到client的addr了，下面的代码纯粹是我无聊，测试一下两个函数的区别
	//这里在编译的时候会有一个警告，关于int转char*的，无视之
	getsockname(client, (struct sockaddr *) &addr, &len);
	printf("sock client: %s\n", inet_ntoa(addr.sin_addr));
	getsockname(fd, (struct sockaddr *) &addr, &len);
	printf("sock server: %s\n", inet_ntoa(addr.sin_addr));
	getpeername(client, (struct sockaddr *) &addr, &len);
	printf("peer client: %s\n", inet_ntoa(addr.sin_addr));
	getpeername(fd, (struct sockaddr *) &addr, &len);
	printf("peer server: %s\n", inet_ntoa(addr.sin_addr));

    char buff[256] = {'\0'};//just for pause
	read(client, &buff, 256);
	close(client);
	close(fd);
	
	return 0;
}
