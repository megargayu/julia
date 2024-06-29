#ifndef JULIA_SHADER_HPP
#define JULIA_SHADER_HPP

#include <SFML/Graphics.hpp>
#include <chrono>

class JuliaShader
{
private:
  sf::Shader m_shader;
  sf::RectangleShape m_blankRectangle;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_start;

  void updateVariables();

public:
  float m_zoom = 1.0;
  sf::Vector2f m_c;
  sf::Vector2u m_windowSize;

  JuliaShader(sf::Vector2u windowSize);
  void draw(sf::RenderWindow &window);
  float activeTime();
  sf::Vector2f getCoords(sf::Vector2f screen);
};

#endif // JULIA_SHADER_HPP
