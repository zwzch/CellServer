//
// Created by zw on 17-11-22.
//
//7.0 置空操作
#ifndef BZERO
//v必须是个变量
#define BZERO(v) \
    memset(&v,0,sizeof(v))
#endif/* !BZERO */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<errno.h>
#include<sys/types.h>
#include <zconf.h>
#include <array>
#include "iostream"
using namespace std;
//int port=8888;
//int udpserver0(){
//    int sockfd;
//    socklen_t len;
//    int z;
//    char buf[256];
//    //绑定了一个对方 udp点对点传输
//    struct sockaddr_in adr_inet;
//    struct sockaddr_in adr_clnt;
//    printf("waiting for client...\n");
//    adr_inet.sin_family=AF_INET;
//    adr_inet.sin_port=htons(port);
//    adr_inet.sin_addr.s_addr=htonl(INADDR_ANY);
//    bzero(&(adr_inet.sin_zero),8);
//    len=sizeof(adr_clnt);
//    sockfd=socket(AF_INET,SOCK_DGRAM,0);
//    if(sockfd==-1){
//        perror("socket error_1");
//        exit(1);
//    }
//    z=bind(sockfd,(struct sockaddr *)&adr_inet,sizeof(adr_inet));
//    if(z==-1){
//        perror("bind error_1");
//        exit(1);
//    }
//    while(1){
//        z=recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&adr_clnt,&len);
//        if(z<0){
//            perror("recvfrom error_1");
//            exit(1);
//        }
//        buf[z]=0;
//        printf("接收：%s",buf);
//        if(strncmp(buf,"stop",4)==0){
//            printf("结束....\n");
//            break;
//        }
//    }
//    close(sockfd);
//    exit(0);
//}
//int udpclient0(){
//    int sockfd;
//    int i=0;
//    int z;
//    char buf[80],str1[80];
//    struct hostent *host;
//    struct sockaddr_in adr_srvr;
//    if((host=gethostbyname("127.0.0.1"))==NULL){
//        herror("gethostbyname error!");
//        exit(1);
//    }
//    printf("connecting server....\n");
//    adr_srvr.sin_family=AF_INET;
//    adr_srvr.sin_port=htons(port);
//    adr_srvr.sin_addr=*((struct in_addr *)host->h_addr);
//    bzero(&(adr_srvr.sin_zero),8);
//    sockfd=socket(AF_INET,SOCK_DGRAM,0);
//    if(sockfd==-1){
//        perror("socket error!");
//        exit(1);
//    }
//    printf("send file ...\n");
//    for(i=0;i<3;i++){
//        fgets(str1,80,stdin);
//        printf("%d:%s",i,str1);
//        sprintf(buf,"%d:%s",i,str1);//输入到str
//        z=sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&adr_srvr,sizeof(adr_srvr));
//        if(z<0){
//            perror("recvfrom error");
//            exit(1);
//        }
//    }
//    printf("send ....\n");
//    sprintf(buf,"stop\n");
//    z=sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&adr_srvr,sizeof(adr_srvr));
//    if(z<0){
//        perror("sendto error");
//        exit(1);
//    }
//    close(sockfd);
//    exit(0);
//}
//int udp0(){
////    udpserver0();
//    udpclient0();
//    return 0;
//}
int udpclt(){
    int fd, len;
    struct sockaddr_in ar = { AF_INET };
    socklen_t al = sizeof (struct sockaddr_in);
    char msg[BUFSIZ] = "oh my beautiful girl";
    // 创建 client socket
    if ((fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("main socket dgram");
        exit(EXIT_FAILURE);
    }
    ar.sin_port = htons(6000);
    // 开始发送消息包到服务器, 默认走 INADDR_ANY
    sendto(fd, msg, sizeof msg - 1, 0, (struct sockaddr *)&ar, al);
    // 开始接收服务器回过来的报文
    len = recvfrom(fd, msg, sizeof msg - 1, 0, (struct sockaddr *)&ar, &al);
    if (len == -1) {
        perror("main recvfrom");
        exit(EXIT_FAILURE);
    }
    msg[len] = '\0';
    printf("[%s:%hd] -> %s\n", inet_ntoa(ar.sin_addr), ntohs(ar.sin_port), msg);
    // 程序结束
    return close(fd);
}
int udpclient1() {
    setvbuf(stdout, NULL, _IONBF, 0);
    fflush(stdout);
    int fd = -1;
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {//是无保障的面向消息的socket ， 主要用于在网络上发广播信息
        cout << "sock error" << endl;
        return -1;
    }
    const int opt = -1;
    int nb = 0;
    nb = setsockopt(fd, SOL_SOCKET, SO_BROADCAST, (char *) &opt, sizeof(opt));//设置套接字类型
    if (nb == -1) {
        cout << "set socket error...\n" << endl;
        return -1;
    }
    struct sockaddr_in ar;
    bzero(&ar, sizeof(struct sockaddr_in));
    ar.sin_family = AF_INET;
    ar.sin_addr.s_addr = htonl(INADDR_BROADCAST);//套接字地址为广播地址
    //inet_addr("255.255.255.255");
    ar.sin_port = htons(6000);//套接字广播端口号为6000
    socklen_t al = sizeof (struct sockaddr_in);
    //sockin的大小
    int len;
    sleep(1);
    char msg[] = {"the message"};
    sendto(fd, msg, sizeof msg - 1, 0, (struct sockaddr *)&ar, al);
    // 开始接收服务器回过来的报文
    len = recvfrom(fd, msg, sizeof msg - 1, 0, (struct sockaddr *)&ar, &al);
    if (len == -1) {
        perror("main recvfrom");
        exit(EXIT_FAILURE);
    }
    msg[len] = '\0';
    printf("[%s:%hd] -> %s\n", inet_ntoa(ar.sin_addr), ntohs(ar.sin_port), msg);
    return 0;
}

int udpserver1() {
    setvbuf(stdout, NULL, _IONBF, 0);
    //设置缓冲区
    //指向流的指针，期望缓冲区的地址，期望缓冲区的类型，缓冲区内字节数量
    fflush(stdout);

    struct sockaddr_in addrto;
    bzero(&addrto, sizeof(struct sockaddr_in));
    addrto.sin_family = AF_INET;
    addrto.sin_addr.s_addr = htonl(INADDR_ANY);
    //改变网络字节序
    //0.0.0.0服务器监听所有
    addrto.sin_port = htons(6000);
    //honts16位 hontl  32位
    socklen_t len = sizeof(addrto);
    //结构体大小
    int sock = -1;
    // AF_INET 表示采用TCP/IP协议族
    // sock_dgram   是无保障的面向消息的socket ， 主要用于在网络上发广播信息
    // 0是通常的默认情况
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        cout << "socket error..." << endl;
        return -1;
    }

    const int opt = -1;
    int nb = 0;

    nb = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *) &opt, sizeof(opt));
    //一般在发送UDP数据报的时候，希望该socket发送的数据具有广播特性：
    if (nb == -1) {
        cout << "set socket errror..." << endl;
        return -1;
    }
    if (bind(sock, (struct sockaddr *) &(addrto), len) == -1) {
        cout << "bind error..." << endl;
        return -1;
    }
    //int bind(int sockfd, const struct sockaddr *addr,socklen_t *addrlen);

    char msg[100] = {0};
    while (1) {
        int ret = recvfrom(sock, msg, 100, 0, (struct sockaddr *) &addrto, &len);
        //sock套接字,缓冲区,缓冲区长度,调用操作方式,指向装有源地址的缓冲区,指向from缓冲区的长度值
        //接收一个数据报并保存源地址。
        if (ret <= 0) {
            cout << "read error..." << endl;
        }
        else {
            printf("Received a string from client [%s:%hd] -> %s\n", inet_ntoa(addrto.sin_addr), ntohs(addrto.sin_port), msg);
            sendto(sock,msg,strlen(msg),0,(struct sockaddr *) &addrto, len);
        }
        sleep(1);

    }
    return 0;
}
int udp1(){
//    udpserver1();
    udpclient1();
    return 0;
}
//#define MCAST_PORT 8888
//#define MCAST_ADDR "224.0.0.88"  // 多播地址
//#define MCAST_DATA "BROADCAST TEST DATA"  // 多播内容
//#define MCAST_INTERVAL 5  //多播时间间隔
//#define BUFF_SIZE 256   //接收缓冲区大小
//int udpclient2() {
//    int sock;
//    struct sockaddr_in mcast_addr;
//    sock = socket(AF_INET, SOCK_DGRAM, 0);
//    if (sock == -1) {
//        cout << "socket error" << endl;
//        return -1;
//    }
//    memset(&mcast_addr, 0, sizeof(mcast_addr));
//    mcast_addr.sin_family = AF_INET;
//    mcast_addr.sin_addr.s_addr = inet_addr(MCAST_ADDR);
//    mcast_addr.sin_port = htons(MCAST_PORT);
//    while (1) {       //向局部多播地址发送多播内容
//        int n = sendto(sock, MCAST_DATA, sizeof(MCAST_DATA), 0, (struct sockaddr *) &mcast_addr, sizeof(mcast_addr));
//        if (n < 0) {
//            cout << "send error" << endl;
//            return -2;
//        }
//        else {
//            cout << "send message is going ...." << endl;
//        }
//        sleep(MCAST_INTERVAL);
//
//    }
//    return 0;
//}
//
//int udpserver2() {
//    int sock;
//    struct sockaddr_in local_addr;
//    int err = -1;
//    sock = socket(AF_INET, SOCK_DGRAM, 0);
//    if (sock == -1) {
//        cout << "sock error" << endl;
//        return -1;
//    }
//    /*初始化地址*/
//    local_addr.sin_family = AF_INET;
//    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//    local_addr.sin_port = htons(MCAST_PORT);
//    /*绑定socket*/
//    err = bind(sock, (struct sockaddr *) &local_addr, sizeof(local_addr));
//    if (err < 0) {
//        cout << "bind error" << endl;
//        return -2;
//    }
//    /*设置回环许可*/
//    int loop = 1;
//    err = setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));
//    if (err < 0) {
//        cout << "set sock error" << endl;
//        return -3;
//    }
//    struct ip_mreq mreq;/*加入多播组*/
//    mreq.imr_multiaddr.s_addr = inet_addr(MCAST_ADDR);//多播地址
//    mreq.imr_interface.s_addr = htonl(INADDR_ANY); //网络接口为默认
//    /*将本机加入多播组*/
//    err = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
//    if (err < 0) {
//        cout << "set sock error" << endl;
//        return -4;
//    }
//    int times = 0;
//    socklen_t addr_len = 0;
//    char buff[BUFF_SIZE];
//    int n = 0;
//    /*循环接受多播组的消息，5次后退出*/
//    for (times = 0;; times++) {
//        addr_len = sizeof(local_addr);
//        memset(buff, 0, BUFF_SIZE);
//        n = recvfrom(sock, buff, BUFF_SIZE, 0, (struct sockaddr *) &local_addr, &addr_len);
//        if (n == -1) {
//            cout << "recv error" << endl;
//            return -5;
//        }
//        /*打印信息*/
//        printf("RECV %dst message from server : %s\n", times, buff);
//        sleep(MCAST_INTERVAL);
//    }
//    /*退出多播组*/
//    err = setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
//    close(sock);
//    return 0;
//}
//int udp2(){
//    udpserver2();
//    udpclient2();
//    return 0;
//}