#include "SocketPoseService.h"
#include <stdio.h>

SocketPoseService::SocketPoseService() 
{
	onConnect = std::bind(&SocketPoseService::onConnect2, this, std::placeholders::_1);
	mServer.setOnConnectCB(onConnect);
	onDisconnect = std::bind(&SocketPoseService::onDisconnect2, this, std::placeholders::_1);
	mServer.setOnDisconnectCB(onDisconnect);
	onRecv = std::bind(&SocketPoseService::onRecv2, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	mServer.setOnRecvCB(onRecv);
	mServer.start(7000, 5);
}

SocketPoseService::~SocketPoseService() 
{
}

void SocketPoseService::getPose(float pos[3], float rot[3])
{
	pos[0] = mPos[0];
	pos[1] = mPos[1];
	pos[2] = mPos[2];
	rot[0] = mRot[0];
	rot[1] = mRot[1];
	rot[2] = mRot[2];
}

void SocketPoseService::onConnect2(int session)
{
	printf("onConnect\n");
}

void SocketPoseService::onDisconnect2(int session)
{
	printf("onDisconnect\n");
}

void SocketPoseService::onRecv2(int session, const char *buf, int len)
{
//	printf("session=%d, len=%d, buf=%s\n", session, len, buf);
	float pos[3], euler[3];
	sscanf(buf, "%f, %f, %f, %f, %f, %f", &pos[0], &pos[1], &pos[2], &euler[0], &euler[1], &euler[2]);
	printf("%f, %f, %f, %f, %f, %f\n", pos[0], pos[1], pos[2], euler[0], euler[1], euler[2]);

	mPos[0] = pos[0];
	mPos[1] = pos[1];
	mPos[2] = pos[2];
	mRot[0] = euler[0];
	mRot[1] = euler[1];
	mRot[2] = euler[2];
}
