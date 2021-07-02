// openssl.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<tchar.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<iostream>

#include "openssl/rsa.h"      
#include "openssl/crypto.h"
#include "openssl/x509.h"
#include "openssl/pem.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/rand.h"


#include <thread>
using namespace std;

#pragma comment(lib, "ws2_32")

#if 0
#define SERVER_KEY "rsa_keyServer.pem"
#define SERVER_CER "certServer.cer"
#else
#define SERVER_KEY "server.pem"
#define SERVER_CER "server.crt"
#endif

#define MAXBUF (1024+512)
#define PORT 8080
int main()
{
	WSADATA wsadData;
	WSAStartup(MAKEWORD(2, 2), &wsadData);

	int sockfd, new_fd;
	socklen_t len;
	struct sockaddr_in my_addr, their_addr;
	unsigned int myport, lisnum;
	SSL_CTX *ctx;
	const SSL_METHOD *meth = TLSv1_2_server_method();

	/* SSL ���ʼ�� */
	SSL_library_init();
	/* �������� SSL �㷨 */
	OpenSSL_add_all_algorithms();
	/* �������� SSL ������Ϣ */
	SSL_load_error_strings();
	/* �� SSL V2 �� V3 ��׼���ݷ�ʽ����һ�� SSL_CTX ���� SSL Content Text */
	ctx = SSL_CTX_new(SSLv23_server_method());
	/* Ҳ������ SSLv2_server_method() �� SSLv3_server_method() ������ʾ V2 �� V3��׼ */
	if (ctx == NULL) {
		printf("SSL_CTX_new failed!\n");
		exit(1);
	}
	/* �����û�������֤�飬 ��֤���������͸��ͻ��ˡ� ֤��������й�Կ */
	if (SSL_CTX_use_certificate_file(ctx, SERVER_CER, SSL_FILETYPE_PEM) <= 0) {
		printf("SSL_CTX_use_certificate_file failed!\n");
		exit(1);
	}
	/* �����û�˽Կ */
	if (SSL_CTX_use_PrivateKey_file(ctx, SERVER_KEY, SSL_FILETYPE_PEM) <= 0) {
		printf("SSL_CTX_use_PrivateKey_file failed!\n");
		exit(1);
	}
	//����˽Կ���룬�����ն���ʾ�û��ֶ���������  
	/*����
	#include <openssl/ssl.h>
	void SSL_CTX_set_default_passwd_cb(SSL_CTX *ctx, pem_password_cb *cb);
	void SSL_CTX_set_default_passwd_cb_userdata(SSL_CTX *ctx, void *u);
	int pem_passwd_cb(char *buf, int size, int rwflag, void *userdata);

	int pem_passwd_cb(char *buf, int size, int rwflag, void *password)
	{
	strncpy(buf, (char *)(password), size);
	buf[size - 1] = '\0';
	return(strlen(buf));
	}
	*/
	//SSL_CTX_set_default_passwd_cb_userdata(ctx, "123456");


	/* ����û�˽Կ�Ƿ���ȷ */
	if (!SSL_CTX_check_private_key(ctx)) {
		printf("SSL_CTX_check_private_key failed!\n");
		exit(1);
	}

	/* ����һ�� socket ���� */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	else
		printf("socket created\n");

	memset(&my_addr, 0x00, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &my_addr.sin_addr);

	if (::bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr))	== -1) {
		perror("bind");
		exit(1);
	}

	if (listen(sockfd, 5) == -1) {
		perror("listen");
		exit(1);
	}

	while (1) {
		len = sizeof(struct sockaddr);
		/* �ȴ��ͻ��������� */
		if ((new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &len)) == -1) {
			perror("accept");
			//exit(errno);
			continue;
		}
		else
		{
			char ip[32] = { 0 };
			inet_ntop(AF_INET, &their_addr.sin_addr, ip, sizeof(ip));
			printf("server: got connection from %s, port %d, socket %d\n", ip, ntohs(their_addr.sin_port), new_fd);
		}

		std::thread([ctx, new_fd]() {
			{
				int fd = new_fd;
				socklen_t len;
				char buf[MAXBUF + 1] = {'\0'};
				SSL *ssl;
				/* ���� ctx ����һ���µ� SSL */
				ssl = SSL_new(ctx);
				/* �������û��� socket ���뵽 SSL */
				SSL_set_fd(ssl, fd);
				/* ���� SSL ���� */
				if (SSL_accept(ssl) == -1) {
					perror("accept");
					closesocket(fd);
					goto finish;
				}
				do 
				{
					/* ��ʼ����ÿ���������ϵ������շ� */
					memset(buf, 0xFF, MAXBUF);
					/* ����Ϣ���ͻ��� */
					len = SSL_write(ssl, buf, strlen(buf));

					if (len <= 0) {
						printf("SSL_write failed, error:%d��\n", GetLastError());
						goto finish;
					}
					else
						printf("SSL_write success len:%d��\n", len);

					memset(buf, 0x00, MAXBUF + 1);
					/* ���տͻ��˵���Ϣ */
					len = SSL_read(ssl, buf, MAXBUF + 1);
					if (len > 0)
						printf("SSL_read success len:%d��", len);
					else
						printf("SSL_read failed, error:%d��\n", GetLastError());
					/* ����ÿ���������ϵ������շ����� */
				} while (1);
			finish:
				/* �ر� SSL ���� */
				SSL_shutdown(ssl);
				/* �ͷ� SSL */
				SSL_free(ssl);
				/* �ر� socket */
				closesocket(fd);
			}
		}).detach();
	}

	/* �رռ����� socket */
	closesocket(sockfd);
	/* �ͷ� CTX */
	SSL_CTX_free(ctx);
	return 0;
}

