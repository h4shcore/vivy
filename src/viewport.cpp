#include "viewport.hpp"
#include <algorithm>

void Viewport::reset(int imgW, int imgH, int winW, int winH) {
    if (imgW <= 0 || imgH <= 0 || winW <= 0 || winH <= 0) return;
    m_scale = std::min(static_cast<float>(winW) / imgW, static_cast<float>(winH) / imgH);
    m_offsetX = (winW - imgW * m_scale) / 2.0f;
    m_offsetY = (winH - imgH * m_scale) / 2.0f;
}

void Viewport::zoom(float factor, int mouseX, int mouseY) {
    float newScale = std::clamp(m_scale * factor, 0.05f, 50.0f);

    m_offsetX = mouseX - (mouseX - m_offsetX) * (newScale / m_scale);
    m_offsetY = mouseY - (mouseY - m_offsetY) * (newScale / m_scale);

    m_scale = newScale;
}

void Viewport::pan(float dx, float dy) {
    m_offsetX += dx;
    m_offsetY += dy;
}

SDL_Rect Viewport::getRenderRect(int imgW, int imgH) const {
    return SDL_Rect{
        static_cast<int>(m_offsetX),
        static_cast<int>(m_offsetY),
        static_cast<int>(imgW * m_scale),
        static_cast<int>(imgH * m_scale)
    };
}
