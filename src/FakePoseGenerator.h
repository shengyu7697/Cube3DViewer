#ifndef FAKEPOSEGENERATOR_H
#define FAKEPOSEGENERATOR_H

#include <thread>

class FakePoseGenerator
{
public:
	FakePoseGenerator();
	~FakePoseGenerator();

	void getPose(float pos[]);

private:
	std::thread mThread;
	float mPos[3] = {0.0f, 0.0f, 0.0f};

	void run();
	void poseFromGenerator();
	void poseFromFile(const char *filename);
	void opencv2opengl(float pos[]);
};

#endif // FAKEPOSEGENERATOR_H
