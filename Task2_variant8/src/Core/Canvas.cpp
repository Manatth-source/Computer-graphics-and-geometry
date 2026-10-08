#include "Core/Canvas.h"


Canvas::Canvas(const sf::RenderWindow& window)
    : window_(&window)
{
}


void Canvas::setWindow(const sf::RenderWindow& window)
{
    window_ = &window;
}