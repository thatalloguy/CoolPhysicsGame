
#include "Instructo/Core/Window.h"
#include "Instructo/Core/Camera.h"
#include "Instructo/Core/Entity.h"
#include "Instructo/Utils/Toolbox.h"
#include "Instructo/Utils/ECS.h"
#define RLIGHTS_IMPLEMENTATION
#include "Instructo/Utils/rlights.h"
#include <raymath.h>

int main() {
	Window window;
	ECS ecs;
	Entity tree;
	Entity water;
	Entity island;

	window.createWindow(1920,1080, "Hello world", false);
	tree.init({ 0,0,0 }, { 0, 0, 0 }, 1, "Res/tree_pine.obj", "Res/treePineTexture.png");
	ecs.addEntity(tree);
	IN_Camera camera;
	camera.init(10, 10, 10, 90);
	camera.lookAt(0, 0, 0);
	//camera.setMode(CAMERA_ORBITAL);
	Vector2 scale = GetWindowScaleDPI();

	water.init({ 5, 0, 0 }, { 0, 0, 0 }, 1, "Res/tree_pine.obj", "Res/treePineTexture.png");
	water.model = LoadModelFromMesh(GenMeshPlane(20, 20, 5, 5));
	Shader waterShader = LoadShader(TextFormat("Res/Shaders/water.vs", 330),
		TextFormat("Res/Shaders/water.fs", 330));
	// Get some required shader locations
	waterShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(waterShader, "viewPos");
	waterShader.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(waterShader, "time");
	water.setShader(waterShader);
	

	//Sun
	Vector3 sunPos = { 2, 0, 0};
	Vector3 sunCol = { 1, 1, 1 };

	// SHADERSS
	Shader shader = LoadShader(TextFormat("Res/Shaders/lighting.vs", 330),
		TextFormat("Res/Shaders/lighting.fs", 330));
	// Get some required shader locations
	shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

	int ambientLoc = GetShaderLocation(shader, "ambient");
	float values[4] = {
		0.1f, 0.1f, 0.1f, 1.0f
	};
	SetShaderValue(shader, ambientLoc, values, SHADER_UNIFORM_VEC4);

	// Assign out lighting shader to model
	tree.setShader(shader);

	// Create lights
	Light lights[MAX_LIGHTS] = { 0 };
	lights[0] = CreateLight(LIGHT_POINT, { -2, 1, -2 }, Vector3Zero(), YELLOW, shader);
	lights[1] = CreateLight(LIGHT_DIRECTIONAL, { 2, 5, 2 }, Vector3Zero(), RED, shader);
	lights[2] = CreateLight(LIGHT_POINT, { -2, 1, 2 }, Vector3Zero(), GREEN, shader);
	lights[3] = CreateLight(LIGHT_POINT, { 2, 1, -2 }, Vector3Zero(), BLUE, shader);
	
	float time = GetTime();

	//island.init({ 0, 0, 0 }, { 0, 0, 0 }, 1, "Res/tree_pine.obj", "Res/treePineTexture.png");
	//generateIslandAndExportToPNG(1024, "ISLAND.png");
	//Image image = LoadImage("ISLAND.png");             // Load heightmap image (RAM)
	//Texture2D texture = LoadTextureFromImage(image);
	//island.model = LoadModelFromMesh(GenMeshHeightmap(image, { 160, 8, 160 }));
	//generateIslandAndExportToPNG(512, "ISLANDDD.png");
	//UnloadImage(image);

	while (!WindowShouldClose()) {
		time = GetTime();
		//std::cout << time << std::endl;
		camera.Update();
		camera.lookAt(tree.position.x, tree.position.y, tree.position.z);
		float cameraPos[3] = { camera.x, camera.y, camera.z };
		SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
		float values[] = { time };
		SetShaderValue(waterShader, waterShader.locs[SHADER_LOC_MAP_EMISSION], values, SHADER_UNIFORM_FLOAT);

		for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(shader, lights[i]);
		lights[1].position.y = sin(lights[1].position.y + time);
		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera.getRaw());

		tree.render();
		water.render();
		//island.render();
		for (int i = 0; i < MAX_LIGHTS; i++)
		{
			if (lights[i].enabled) DrawSphereEx(lights[i].position, 0.2f, 8, 8, lights[i].color);
			else DrawSphereWires(lights[i].position, 0.2f, 8, 8, ColorAlpha(lights[i].color, 0.3f));
		}

		DrawGrid(10, 10);


		EndMode3D();
		EndDrawing();
		//ecs.render(camera);
	
	}
	ecs.cleanUp();
	window.closeWindow();
	return 0;
}

