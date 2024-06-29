#include <SFML/Graphics.hpp>
#include <chrono>

#include "shader.hpp"

void JuliaShader::updateVariables()
{
  m_shader.setParameter("windowSize", sf::Vector2f(m_windowSize));
  m_shader.setParameter("c", m_c);
  m_shader.setParameter("zoom", m_zoom);
  m_shader.setParameter("time", activeTime());
}

JuliaShader::JuliaShader(sf::Vector2u windowSize) : m_windowSize(windowSize)
{
  // Initialize variables
  m_c = sf::Vector2f(m_windowSize) / 2.0f;
  m_blankRectangle = sf::RectangleShape(sf::Vector2f(windowSize));
  m_start = std::chrono::high_resolution_clock::now();

  // Load shader
  if (!m_shader.loadFromFile("/home/ayush/programming/julia/src/julia.frag", sf::Shader::Fragment))
    throw std::runtime_error("Could not load shader.");

  // Set parameters
  updateVariables();
}

void JuliaShader::draw(sf::RenderWindow &window)
{
  updateVariables();
  window.draw(m_blankRectangle, &m_shader);
}

float JuliaShader::activeTime()
{
  auto currTime = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(currTime - m_start).count();
}
