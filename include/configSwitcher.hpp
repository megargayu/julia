#ifndef CONFIG_SWITCHER_HPP
#define CONFIG_SWITCHER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#include "shader.hpp"

class ConfigSwitcher
{
public:
  struct Config
  {
    int id;
    std::string title;
    sf::Vector2f c;
  };

private:
  JuliaShader &m_shaderRef;
  std::vector<Config> m_config;
  int m_currId = -1;
  
public:
  ConfigSwitcher(JuliaShader &shaderRef);
  
};

#endif // CONFIG_SWITCHER_HPP
