#pragma once
#include <raylib.h>

class Entity
{
public:
	Vector3 position;
	Vector3 Rotation;
	float Scale;
	
	void init(Vector3 pos, Vector3 rot, float scale, const char* modelPath, const char* texturePath) {
		model = LoadModel(modelPath);
		texture = LoadTexture(texturePath);
		model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
		position = pos;
		Rotation = rot;
		Scale = scale;
	}

	void render() {
		DrawModel(model, position, Scale, WHITE);
	}

	void cleanUp() {
		UnloadTexture(texture);
	}
	
	void setShader(Shader shader) {
		model.materials[0].shader = shader;
		
	}

	Model model;
	Texture2D texture;
};

