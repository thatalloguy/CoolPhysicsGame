#pragma once
#include <vector>
#include "../Core/Entity.h"
#include "../Core/Camera.h"

#include <iostream>
class ECS {

public:
	void render(IN_Camera camera) {
		BeginDrawing();
		BeginMode3D(camera.getRaw());
		ClearBackground(BLUE);
		for (int i = 0; i < entities.size(); i++) {
			entities[i].render();	
		}
		DrawGrid(10 ,10);
		EndMode3D();

		EndDrawing();
	}
	void addEntity(Entity entity) {
		entities.push_back(entity);
	}
	void cleanUp() {
		for (int i = 0; i < entities.size(); i++) {
			entities[i].cleanUp();
		}
		entities.clear();
	}

private:
	std::vector<Entity> entities = {};

};