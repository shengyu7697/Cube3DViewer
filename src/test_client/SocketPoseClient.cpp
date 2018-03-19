#include "SocketPoseClient.h"

#include <string.h>

SocketPoseClient::SocketPoseClient() 
{
	const std::string hostname = "127.0.0.1";
	int port = 7000;
	printf("start client, connect to %s:%d\n", hostname.c_str(), port);

	onConnect = std::bind(&SocketPoseClient::onConnect2, this, std::placeholders::_1);
	mClient.setOnConnectCB(onConnect);
	onDisconnect = std::bind(&SocketPoseClient::onDisconnect2, this, std::placeholders::_1);
	mClient.setOnDisconnectCB(onDisconnect);
	onRecv = std::bind(&SocketPoseClient::onRecv2, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	mClient.setOnRecvCB(onRecv);
	mClient.start(hostname, 7000);
}

SocketPoseClient::~SocketPoseClient() 
{
	mClient.stop();
}

inline void opencv2opengl(float pos[])
{
	pos[0] = -pos[0];
	pos[1] = -pos[1];
	pos[2] = pos[2];
}

void SocketPoseClient::sendPose(float pos[3], bool cv2gl)
{
	if (cv2gl) {
		float scale = 100.0;
		opencv2opengl(pos);
		pos[0] = pos[0] * scale;
		pos[1] = pos[1] * scale;
		pos[2] = pos[2] * scale;
	}

	char buf[64];
	sprintf(buf, "%f, %f, %f", pos[0], pos[1], pos[2]);
	mClient.send(buf, (int)strlen(buf));
}

void SocketPoseClient::onConnect2(int session)
{
	printf("onConnect\n");
}

void SocketPoseClient::onDisconnect2(int session)
{
	printf("onDisconnect\n");
}

void SocketPoseClient::onRecv2(int session, const char *buf, int len)
{
	//printf("session=%d, len=%d, buf=%s\n", session, len, buf);
	printf("Server: %s\n", buf);
}
