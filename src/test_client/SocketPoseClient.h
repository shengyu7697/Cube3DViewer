#ifndef SOCKETPOSECLIENT_H
#define SOCKETPOSECLIENT_H

#include "TinyTcpClient.h"
#include <functional>

class SocketPoseClient
{
    typedef std::function<void(int session)> OnConnect;
    typedef std::function<void(int session)> OnDisconnect;
    typedef std::function<void(int session, const char *buf, int len)> OnRecv;
public:
	SocketPoseClient();
	~SocketPoseClient();

	void sendPose(float pos[3], float euler[3], bool cv2gl = false);

private:
	void onConnect(int session);
	void onDisconnect(int session);
	void onRecv(int session, const char *buf, int len);

	float mPos[3] = {0.0, 0.0, 0.0};
	TinyTcpClient mClient;

	OnConnect onConnectCB = nullptr;
	OnDisconnect onDisconnectCB = nullptr;
	OnRecv onRecvCB = nullptr;
};

#endif // SOCKETPOSECLIENT_H
