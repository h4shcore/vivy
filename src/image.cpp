#include "image.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <iostream>

bool Image::load(SDL_Renderer* renderer, const std::string& path) {
  if (path.empty()) return false;

  SDL_Texture* rawTexture = IMG_LoadTexture(renderer, path.c_str());
  if (!rawTexture) {
    std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    return false;
  }

  m_texture.reset(rawTexture);
  SDL_QueryTexture(m_texture.get(), nullptr, nullptr, &m_width, &m_height);

  std::cout << "Loaded image (" << m_width << "x" << m_height << "): " << path << std::endl;
  return true;
}
