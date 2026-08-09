#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <memory>
#include <string>

struct TextureDeleter {
  void operator() (SDL_Texture* t) const { if (t) SDL_DestroyTexture(t); }
};

using UniqureTexture = std::unique_ptr<SDL_Texture, TextureDeleter>;

class Image {
public:
  Image() = default;

  bool load(SDL_Renderer* renderer, const std::string& path);
  
  SDL_Texture* getTexture() const { return m_texture.get(); }
  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }
  bool isLoaded() const { return m_texture != nullptr; }

private:
  UniqureTexture m_texture;
  int m_width{0};
  int m_height{0};
};
