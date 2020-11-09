#pragma once

#include "gameObject.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class SpriteObj : public GameObject {
private:
    std::string spriteFile;
    sf::Sprite sprite;
    sf::Texture texture;
public:
    SpriteObj(std::string identifier, std::string spriteFile);
    SpriteObj(const SpriteObj& other);
    ~SpriteObj();

public:
    void update() override;
    void render(sf::RenderWindow& window) override;

    void setPosition(sf::Vector2f position);
    void setScale(sf::Vector2f scale);
    std::string getSpriteFile() const;
};

