#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "SocketPoseClient.h"
#include "TimeUtil.h"

using namespace std;

void sendPoseFromFakePoseGenerator()
{
    SocketPoseClient spc;

    while(1) {
        if (spc.isConnect())
            break;
        else
            sleep_ms(10);
    }

    // float pos[3] = {0.0f, 0.0f, 2.0f}; FIXME can't ParseFromString via protobuf 2.6.1
    // float rot[3] = {0.0f, 0.0f, 0.0f};
    float pos[3] = {0.01f, 0.01f, 2.0f};
    float rot[3] = {0.01f, 0.01f, 0.01f};

    for (int i = 0; i < 20; i++) {
        pos[2] += 0.3f;
        spc.sendPose(pos, rot);
        sleep_ms(100);
    }
}

void sendPoseFromFile(const char *filename)
{
    SocketPoseClient spc;

    while(1) {
        if (spc.isConnect())
            break;
        else
            sleep_ms(10);
    }

    char buf[128];
    FILE *fp = NULL;
    int ret;
    float pos[3];
    float rot[3];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: can not read %s file!\n", filename);
        return;
    }

    while (1) {
        ret = fscanf(fp, "%f, %f, %f, %f, %f, %f", &pos[0], &pos[1], &pos[2], &rot[0], &rot[1], &rot[2]);
        if (ret == EOF)
            break;

        spc.sendPose(pos, rot, true);
        sleep_ms(50);
    }

    if (fp != NULL)
        fclose(fp);
}

int main(int argc, char* argv[])
{
    /*if (argc < 3) {
        fprintf(stderr, "Usage: %s ip_address port_number\n", argv[0]);
        exit(1);
    }*/

    sendPoseFromFakePoseGenerator();
    //sendPoseFromFile(argv[1]);

    printf("end of process.\n");

    return 0;
}
