#include "SocketPoseClient.h"
#include <string.h>
using namespace std;

#if defined(USE_PROTOBUF)
#include "pose.pb.h"
using namespace vr;
#endif

SocketPoseClient::SocketPoseClient() 
{
    const std::string hostname = "127.0.0.1";
    int port = 7000;
    printf("start client, connect to %s:%d\n", hostname.c_str(), port);

    onConnectCB = std::bind(&SocketPoseClient::onConnect, this, std::placeholders::_1);
    mTcpClient.setOnConnect(onConnectCB);
    onDisconnectCB = std::bind(&SocketPoseClient::onDisconnect, this, std::placeholders::_1);
    mTcpClient.setOnDisconnect(onDisconnectCB);
    onRecvCB = std::bind(&SocketPoseClient::onRecv, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    mTcpClient.setOnRecv(onRecvCB);
    mTcpClient.start(hostname, 7000);
}

SocketPoseClient::~SocketPoseClient() 
{
    mTcpClient.stop();
}

inline void opencv2opengl(float pos[3], float euler[3])
{
    pos[0] = -pos[0];
    pos[1] = -pos[1];
    //pos[2] = pos[2];
    euler[0] = -euler[0];
    euler[1] = -euler[1];
    euler[2] = -euler[2];
}

void SocketPoseClient::sendPose(float pos[3], float euler[3], bool cv2gl)
{
    if (cv2gl) {
        float scale = 100.0f;
        opencv2opengl(pos, euler);
        pos[0] = pos[0] * scale;
        pos[1] = pos[1] * scale;
        pos[2] = pos[2] * scale;
    }
    printf("%f, %f, %f, %f, %f, %f\n", pos[0], pos[1], pos[2], euler[0], euler[1], euler[2]);

#if defined(USE_PROTOBUF)
    Pose pose;
    pose.set_pos_x(pos[0]);
    pose.set_pos_y(pos[1]);
    pose.set_pos_z(pos[2]);
    pose.set_euler_x(euler[0]);
    pose.set_euler_y(euler[1]);
    pose.set_euler_z(euler[2]);
    string data;
    pose.SerializeToString(&data);
    mTcpClient.send(data.c_str(), data.size());
    //printf("USE_PROTOBUF size=%d\n", data.size());
    /*char buf[512];
    memset(buf, 0, sizeof(buf));
    pose.SerializeToArray(buf, sizeof(buf));
    mTcpClient.send(buf, strlen(buf));*/
#else
    char buf[64];
    sprintf(buf, "%f, %f, %f, %f, %f, %f", pos[0], pos[1], pos[2], euler[0], euler[1], euler[2]);
    mTcpClient.send(buf, (int)strlen(buf));
#endif
}

void SocketPoseClient::onConnect(int session)
{
    mIsConnect = true;
    printf("onConnect\n");
}

void SocketPoseClient::onDisconnect(int session)
{
    mIsConnect = false;
    printf("onDisconnect\n");
}

void SocketPoseClient::onRecv(int session, const char *buf, int len)
{
    //printf("session=%d, len=%d, buf=%s\n", session, len, buf);
    printf("Server: %s\n", buf);
}

bool SocketPoseClient::isConnect()
{
    return mIsConnect;
}
