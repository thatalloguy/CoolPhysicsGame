#pragma once
#include <raylib.h>

class IN_Camera {

public:
	float x, y, z;
	float fov;

	void init(float x, float y, float z, float fov) {
		x = x; y = y; z = z; fov = fov;
		camera.position = Vector3{x, y, z};
		camera.up = Vector3{ 0, 1, 0};
		camera.fovy = fov;
		camera.projection = CAMERA_PERSPECTIVE;
		//SetCameraMode(camera, CAMERA_ORBITAL);
	}

	void lookAt(float x, float y, float z) {
		camera.target = Vector3{ x, y, z };
	}

	void setMode(int mode) {
		SetCameraMode(camera, mode);
	}

	void Update() {
		UpdateCamera(&camera);
	}

	Camera getRaw() {
		return camera;
	}

private:
	Camera camera = {0};
	
};