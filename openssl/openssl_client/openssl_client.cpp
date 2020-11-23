// openssl.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<tchar.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<iostream>
#include<openssl\ssl.h>
#include<openssl\err.h>

#pragma comment(lib, "ws2_32")



#define PORT 8080
#define MAXBUF 1024

void ShowCerts(SSL * ssl)
{
	X509 *cert;
	char *line;

	cert = SSL_get_peer_certificate(ssl);
	if (cert != NULL) {
		printf("����֤����Ϣ:\n");
		line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
		printf("֤��: %s\n", line);
		free(line);
		line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
		printf("�䷢��: %s\n", line);
		free(line);
		X509_free(cert);
	}
	else
		printf("��֤����Ϣ��\n");
}

int main(int argc, char **argv)
{
	WSADATA wsadData;
	WSAStartup(MAKEWORD(2, 2), &wsadData);

	int sockfd, len;
	struct sockaddr_in dest;
	char buffer[MAXBUF + 1];
	SSL_CTX *ctx;
	SSL *ssl;

	/* SSL ���ʼ�����ο� ssl-server.c ���� */
	SSL_library_init();
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	ctx = SSL_CTX_new(SSLv23_client_method());
	if (ctx == NULL) {
		ERR_print_errors_fp(stdout);
		exit(1);
	}

	/* ����һ�� socket ���� tcp ͨ�� */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket");
		exit(errno);
	}
	printf("socket created\n");

	/* ��ʼ���������ˣ��Է����ĵ�ַ�Ͷ˿���Ϣ */
	memset(&dest,0x00, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &dest.sin_addr);
	//dest.sin_addr.s_addr = inet_addr("127.0.0.1");

	/* ���ӷ����� */
	if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0) {
		printf("connect error:%d\n", GetLastError());
	}

	/* ���� ctx ����һ���µ� SSL */
	ssl = SSL_new(ctx);
	SSL_set_fd(ssl, sockfd);
	/* ���� SSL ���� */
	if (SSL_connect(ssl) == -1)
		ERR_print_errors_fp(stderr);
	else {
		printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
		ShowCerts(ssl);
	}

	/* ���նԷ�����������Ϣ�������� MAXBUF ���ֽ� */
	memset(buffer, 0x00, MAXBUF + 1);
	/* ���շ�����������Ϣ */
	len = SSL_read(ssl, buffer, MAXBUF);
	if (len > 0)
		printf("������Ϣ�ɹ�:'%s'����%d���ֽڵ�����\n",
			buffer, len);
	else {
		printf
		("��Ϣ����ʧ�ܣ����������%d\n",errno);
		goto finish;
	}
	memset(buffer,0x00 ,MAXBUF + 1);
	memcpy(buffer, "from client->server",strlen("from client->server"));
	/* ����Ϣ�������� */
	len = SSL_write(ssl, buffer, strlen(buffer));
	if (len < 0)
		printf
		("��Ϣ'%s'����ʧ�ܣ����������%d\n",buffer, errno);
	else
		printf("��Ϣ'%s'���ͳɹ�����������%d���ֽڣ�\n",
			buffer, len);

finish:
	/* �ر����� */
	SSL_shutdown(ssl);
	SSL_free(ssl);
	closesocket(sockfd);
	SSL_CTX_free(ctx);
	return 0;
}