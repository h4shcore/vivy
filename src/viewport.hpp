#pragma once

#include <SDL2/SDL.h>

class Viewport {
public:
  Viewport() = default;

  // Recalculates scale and offsets to fit image inside window and center it
  void reset(int imgW, int imgH, int winW, int winH);

  // Zooms in/out keeping the point under (mouseX, mouseY) fixed on screen
  void zoom(float factor, int mouseX, int mouseY);

  // Pans the image when dragging
  void pan(float dx, float dy);

  // Converts float coordinates into an SDL_Rect for rendering
  SDL_Rect getRenderRect(int imgW, int imgH) const;

private:
  float m_scale{1.0f};
  float m_offsetX{0.0f};
  float m_offsetY{0.0f};
};
