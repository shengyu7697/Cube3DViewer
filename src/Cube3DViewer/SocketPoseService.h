#ifndef SOCKETPOSESERVICE_H
#define SOCKETPOSESERVICE_H

#include "TinyTcpServer.h"
#include <functional>

class SocketPoseService
{
public:
	SocketPoseService();
	~SocketPoseService();

	void getPose(float pos[]);

private:
	void onConnect2(int session);
	void onDisconnect2(int session);
	void onRecv2(int session, const char *buf, int len);

	float mPos[3] = {0.0, 0.0, 0.0};
	TinyTcpServer mServer;

	OnConnect onConnect = nullptr;
	OnDisconnect onDisconnect = nullptr;
	OnRecv onRecv = nullptr;
};

#endif // SOCKETPOSESERVICE_H
