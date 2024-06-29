#include "shader.hpp"
#include "configSwitcher.hpp"

#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <cassert>

// TODO: (I will never do this, I was too lazy)

ConfigSwitcher::ConfigSwitcher(JuliaShader &shaderRef) : m_shaderRef(shaderRef)
{
  // Load configuration data
  YAML::Node config = YAML::LoadFile("/home/ayush/programming/julia/src/configs.yaml");

  const auto configNode = config["configs"];
  assert(configNode.IsSequence());

  m_config = std::vector<Config>();
  for (std::size_t i = 0; i < configNode.size(); i++)
  {
    m_config.push_back(Config{
      configNode[i]["id"].as<int>(), 
      configNode[i]["title"].as<std::string>(), 
      sf::Vector2f(
        configNode[i]["c"][0].as<float>(), 
        configNode[i]["c"][1].as<float>()
      )
    });
  }
}


