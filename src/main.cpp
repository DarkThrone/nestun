#include <cstddef>
#include <cstring>
#include <print>
#include <string>

#include "../external/raylib/src/raylib.h"
#include "../external/raylib/src/raymath.h"  // Required for: Vector2Clamp()
#include "Cpu.hpp"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

using namespace Nestun;
using namespace std;
namespace {
int run_raylib() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  // Enable config flags for resizable window and vertical synchro
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(screenWidth, screenHeight, "raylib [core] example - window letterbox");
  SetWindowMinSize(320, 240);

  int gameScreenWidth = 640;
  int gameScreenHeight = 480;

  // Render texture initialization, used to hold the rendering result so we can easily resize it
  RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
  SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);  // Texture scale filter to use

  Color color = {.r = static_cast<unsigned char>(GetRandomValue(100, 250)),
                 .g = static_cast<unsigned char>(GetRandomValue(50, 150)),
                 .b = static_cast<unsigned char>(GetRandomValue(10, 100)),
                 .a = 255};

  SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    // Compute required framebuffer scaling
    float scale =
        MIN((float)GetScreenWidth() / gameScreenWidth, (float)GetScreenHeight() / gameScreenHeight);

    // Draw
    //----------------------------------------------------------------------------------
    // Draw everything in the render texture, note this will not be rendered on screen, yet
    BeginTextureMode(target);
    ClearBackground(RAYWHITE);  // Clear render texture background color

    DrawRectangle(0, 0, gameScreenWidth, gameScreenHeight, color);

    DrawText(
        "If executed inside a window,\nyou can resize the window,\nand see the screen scaling!", 10,
        25, 20, WHITE);
    // DrawText(TextFormat("Default Mouse: [%i , %i]", (int)mouse.x, (int)mouse.y), 350, 25, 20,
    //          GREEN);
    // DrawText(TextFormat("Virtual Mouse: [%i , %i]", (int)virtualMouse.x, (int)virtualMouse.y),
    // 350, 55, 20, YELLOW);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);  // Clear screen background

    // Draw render texture to screen, properly scaled
    DrawTexturePro(
        target.texture,
        (Rectangle){0.0F, 0.0F, (float)target.texture.width, (float)-target.texture.height},
        (Rectangle){0.5F * (GetScreenWidth() - ((float)gameScreenWidth * scale)),
                    (GetScreenHeight() - ((float)gameScreenHeight * scale)) * 0.5f,
                    (float)gameScreenWidth * scale, (float)gameScreenHeight * scale},
        (Vector2){0, 0}, 0.0F, WHITE);
    EndDrawing();
    //--------------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  UnloadRenderTexture(target);  // Unload render texture

  CloseWindow();  // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
}  // namespace

int main() {
  Bus bus{};
  Cpu cpu(bus);

  bus.load_rom(std::string("file.nes"));

  println("Starting CPU");
  cpu.reset();

  int i = 0;
  while (i++ < 100) {
    cpu.tick();
  }

  run_raylib();
}
