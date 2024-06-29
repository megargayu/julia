#include <SFML/Graphics.hpp>
#include <iostream>

#include "shader.hpp"
#include "configSwitcher.hpp"

const sf::Color pointBackColor = sf::Color(166, 200, 255);
const sf::Color pointColor = sf::Color(38, 113, 235);

const sf::Vector2f initialC(400 - 0.54 * 200, 400 - 0.54 * 200);

template <class T>
T squaredLength(sf::Vector2<T> vec)
{
  return vec.x * vec.x + vec.y * vec.y;
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 800), "Julia Sets");

  bool moving = false;
  JuliaShader shader(window.getSize());

  ConfigSwitcher switcher(shader);

  sf::RectangleShape blankRectangle(sf::Vector2f(window.getSize()));

  sf::CircleShape c(5.0);
  c.setFillColor(pointColor);
  c.setOrigin(c.getRadius(), c.getRadius());

  sf::CircleShape cBack(8.0);
  cBack.setFillColor(pointBackColor);
  cBack.setOrigin(cBack.getRadius(), cBack.getRadius());

  shader.m_c = initialC;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::MouseButtonPressed:
        // Mouse button is pressed, get the position and set moving as active
        if (event.mouseButton.button == 0)
        {
          moving = true;
          shader.m_c = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        }
        break;
      case sf::Event::MouseButtonReleased:
        // Mouse button is released, no longer move
        if (event.mouseButton.button == 0)
          moving = false;

        break;
      case sf::Event::MouseMoved:
      {
        if (!moving)
          break;

        shader.m_c = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
        break;
      }
      case sf::Event::MouseWheelScrolled:
        // Ignore the mouse wheel unless we're not moving
        if (moving)
          break;

        // Determine the scroll direction and adjust the zoom level
        // Again, you can swap these to invert the direction
        if (event.mouseWheelScroll.delta <= -1)
          shader.m_zoom = shader.m_zoom + .1f;
        else if (event.mouseWheelScroll.delta >= 1)
          shader.m_zoom = shader.m_zoom - .1f;
        
        break;
      default:
        break;
      }
    }

    shader.m_windowSize = window.getSize();
    shader.draw(window);

    sf::Vector2 mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (moving || squaredLength(mousePos - shader.m_c) < cBack.getRadius() * cBack.getRadius())
      cBack.setFillColor(pointColor);
    else
      cBack.setFillColor(pointBackColor);

    cBack.setPosition(shader.m_c);
    window.draw(cBack);

    c.setPosition(shader.m_c);
    window.draw(c);

    window.display();
  }

  return 0;
}