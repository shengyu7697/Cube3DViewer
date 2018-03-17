#include "FakePoseGenerator.h"

#include <stdio.h>
#include <unistd.h>

FakePoseGenerator::FakePoseGenerator() 
{
	mThread = std::thread(&FakePoseGenerator::run, this);
}

FakePoseGenerator::~FakePoseGenerator() 
{
	if (mThread.joinable())
		mThread.join();
}

void FakePoseGenerator::run()
{
	poseFromGenerator();
	//poseFromFile("pose.log");
}

void FakePoseGenerator::poseFromGenerator()
{
	for (int i = 0; i < 20; i++) {
		mPos[0] = 0;
		mPos[1] = 0;
		mPos[2] += 0.3;
		usleep(1000*100);
	}
}

void FakePoseGenerator::poseFromFile(const char *filename)
{
	char buf[512];
	FILE *fp = NULL;
	int ret;
	float pos[3];
	float scale = 100.0;

	fp = fopen(filename, "r");
	while (1) {
		ret = fscanf(fp, "%f, %f, %f", &pos[0], &pos[1], &pos[2]);
		if (ret == EOF)
			break;
		usleep(1000*50);

		opencv2opengl(pos);
		mPos[0] = pos[0] * scale;
		mPos[1] = pos[1] * scale;
		mPos[2] = pos[2] * scale;
		printf("%f, %f, %f\n", mPos[0], mPos[1], mPos[2]);
	}
	if (fp != NULL)
		fclose(fp);
}

void FakePoseGenerator::opencv2opengl(float pos[])
{
	pos[0] = -pos[0];
	pos[1] = -pos[1];
	pos[2] = pos[2];
}

void FakePoseGenerator::getPose(float pos[])
{
	pos[0] = mPos[0];
	pos[1] = mPos[1];
	pos[2] = mPos[2];
}
