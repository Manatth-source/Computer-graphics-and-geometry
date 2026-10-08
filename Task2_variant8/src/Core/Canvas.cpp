#include "Core/Canvas.h"


core::Canvas::Canvas(sf::RenderWindow& window)
    : window_(&window)
{
    pixels_.setPrimitiveType(sf::PrimitiveType::Points);
}


void core::Canvas::setWindow(sf::RenderWindow& window)
{
    window_ = &window;
    pixels_.clear();
    pixels_.setPrimitiveType(sf::PrimitiveType::Points);
}


void core::Canvas::clear(sf::Color color)
{
    if (window_) {
        window_->clear(color);
    }
    pixels_.clear();
}


void core::Canvas::putPixel(int x, int y, sf::Color color)
{
    if (!window_) return;

    sf::Vector2u size = window_->getSize();
    if (x >= 0 && x < static_cast<int>(size.x) &&
        y >= 0 && y < static_cast<int>(size.y))
    {
        sf::Vertex pixel(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)), color); 
        pixels_.append(pixel);
    }
}


void core::Canvas::display()
{
    if (window_) {
        window_->draw(pixels_);
        window_->display();
        pixels_.clear();
    }
}


int core::Canvas::getWidth() const 
{ 
    return window_ ? static_cast<int>(window_->getSize().x) : 0; 
}


int core::Canvas::getHeight() const
{
    return window_ ? static_cast<int>(window_->getSize().y) : 0;
}