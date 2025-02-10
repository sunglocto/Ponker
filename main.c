#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    const float maxX = 10.25f;
    const float maxY = 5.0f;
   
    InitWindow(screenWidth, screenHeight, "PONKER");
    InitAudioDevice();
    Texture2D petet = LoadTexture("res/petet.jpg");
    Sound hitSound = LoadSound("res/hit.wav"); 
    Sound winSound = LoadSound("res/win.wav");
    // Initialize the camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 0.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 70.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    SetTargetFPS(60);
    float i;
    float ii;
    i = GetRandomValue(0,1);
    if (i > 0.5) {
    	ii = -1;
    } else {
    	ii = 1;
    }
    Vector3 Velocity = {0.2f * ii, 0.2f*ii, 0.0f};
    Vector3 position = {0.0f, 0.0f, 0.0f};
    
    float p1Y = 0.0f;
    float p2Y = 0.0f;
    int p1Score = 0;
    int p2Score = 0;
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
     
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        
        BeginDrawing();
            //DrawTexture(petet,0,0,WHITE);
	    DrawText(TextFormat("%d pts", p1Score), 20, 21, 20, BLACK);
	    DrawText(TextFormat("%d pts", p1Score), 20, 20, 20, RED);
	    DrawText(TextFormat("%d pts", p2Score), 700, 21, 20, BLACK);
	    DrawText(TextFormat("%d pts", p2Score), 700, 20, 20, ORANGE);
            ClearBackground(WHITE);
	    //ImageClearBackground(petet);
	    BeginMode3D(camera);
                DrawCube(position,.5f,.5f,.5f,BLUE);
                DrawCube((Vector3){-maxX, p1Y, 0.0f}, 1, 3, 1, RED);
                DrawCube((Vector3){maxX, p2Y, 0.0f}, 1, 3, 1, ORANGE);
            EndMode3D();

           
	    

	    

        EndDrawing();
        // TODO variable updates go HERE 
            if (position.x > maxX - .75f) {
		if (abs(p2Y - position.y) > 1.5f) {
			p1Score++;
			position = (Vector3){0.0f, GetRandomValue(-maxY, maxY), 0.0f};
			PlaySound(winSound);
			Velocity.x = -Velocity.x;
			//BeginDrawing();
			//ClearBackground(RED);
			//EndDrawing();
		} else {
		PlaySound(hitSound);
	    	Velocity.x = -Velocity.x;
		
		}
	    } else if (position.x < -maxX + .75f) {
		if (abs(p1Y - position.y) > 1.5f) {
			p2Score++;
			position = (Vector3){0.0f, GetRandomValue(-maxY,maxY), 0.0f};
			PlaySound(winSound);
			Velocity.x = -Velocity.x;
			//BeginDrawing();
			//ClearBackground(ORANGE);
			//EndDrawing();
		} else {
		PlaySound(hitSound);
	    	Velocity.x = -Velocity.x; 
		}
		
            }

            if (position.y > maxY || position.y < -maxY) {
                Velocity.y = -1 * Velocity.y;
            }
	    position = Vector3Add(position, Velocity);

	    if (IsKeyDown(KEY_W) && p1Y < maxY) {
	    	p1Y += 0.5f;
	    }

	    if(IsKeyDown(KEY_S) && p1Y > -maxY) {
	    	p1Y -= 0.5f;
	    }

	   if (IsKeyDown(KEY_UP) && p2Y < maxY) {
	    	p2Y += 0.5f;
	    }

	    if(IsKeyDown(KEY_DOWN) && p2Y > -maxY) {
	    	p2Y -= 0.5f;
	    }

	   //p2Y = position.y;
	   //p1Y = position.y;
        //----------------------------------------------------------------------------------
    }
    
    // De-Initialization

    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

