#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>

#include <sys/ioctl.h>
#include <linux/if.h>

void getlocalhostip()
{
	int  MAXINTERFACES=16;
	long ip;
	int fd, intrface, retn = 0;
	struct ifreq buf[MAXINTERFACES]; //if.h
	struct ifconf ifc;				 //if.h
	ip = -1;
	if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) >= 0) {
		ifc.ifc_len = sizeof(buf);
		ifc.ifc_buf = (caddr_t) buf;
		if (!ioctl (fd, SIOCGIFCONF, (char *) &ifc)) {
			intrface = ifc.ifc_len / sizeof (struct ifreq); 
			printf("interface: %d\n\n", intrface);
			while (intrface-- > 0) 	{
				struct ifreq *ip = 0;
				struct sockaddr_in *ip_addr = 0;
				ip = ifc.ifc_req + intrface;
				printf("ifreq 的地址是: %x\n", ip);
				ip_addr = (struct sockaddr_in *)&(ip->ifr_addr);
				printf("%s : %s\n", ip->ifr_name, inet_ntoa(ip_addr->sin_addr));
			}
		}
		close (fd);
	}
}

int main(int argc, char **argv)
{
	//                  ------------------
	//WARNING! 本程序有 | 刷屏级别的警告 |,无视之~
	//                  ------------------
    char *ip = 0;
	long ret = 0;
	int r = 0;

	//获取本机所有interface的IP
	getlocalhostip(); 

	//test字节顺序
	r = ret = 0;
	ip = "12.34.56.78";
	printf("\nIP实际是:%s\n",ip);
	r = inet_aton(ip, &ret);
	printf("aton\tret = %11d,\tIP = %8X\n", r, ret);
	ret = inet_addr(ip);
	printf("addr\tret = %11d,\tIP = %8X\n", ret, ret);
	ret = inet_network(ip);
	printf("network\tret = %11d,\tIP = %8X\n", ret, ret);


	//test 255bug
	r = ret = 0;
	ip = "255.255.255.255";
	printf("\nIP实际是:%s\n",ip);
	r = inet_aton(ip, &ret);
	printf("aton\tret = %11d,\tIP = %X\n", r, ret);
	ret = inet_addr(ip);
	printf("addr\tret = %11d,\tIP = %X\n", ret, ret);
	ret = inet_network(ip);
	printf("network\tret = %11d,\tIP = %X\n", ret, ret);
	
	r = ret = 0;
	ip = "0.0.0.0";
	printf("\nIP实际是:%s\n",ip);
	r = inet_aton(ip, &ret);
	printf("aton\tret = %11d,\tIP = %X\n", r, ret);
	ret = inet_addr(ip);
	printf("addr\tret = %11d,\tIP = %X\n", ret, ret);
	ret = inet_network(ip);
	printf("network\tret = %11d,\tIP = %X\n", ret, ret);

	r = ret = 0;
	ip = "255.255.";
	printf("\nIP实际是:%s\n",ip);
	r = inet_aton(ip, &ret);
	printf("aton\tret = %11d,\tIP = %X\n", r, ret);
	ret = inet_addr(ip);
	printf("addr\tret = %11d,\tIP = %X\n", ret, ret);
	ret = inet_network(ip);
	printf("network\tret = %11d,\tIP = %X\n", ret, ret);

	return 0;
}
