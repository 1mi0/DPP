#pragma once
#include <string>
#include <openssl/ssl.h>
#include <openssl/err.h>

class SSLClient
{
	std::string buffer;
	int sfd;
	SSL* ssl;
	SSL_CTX* ctx;
public:
	SSLClient(const std::string &hostname, const std::string &port = "443");
	void ReadLoop();
	virtual ~SSLClient();
	virtual bool HandleBuffer(std::string &buffer);
	virtual void write(const std::string &data);
	virtual void close();
};

