#include "sprite.hpp"

SpriteObj::SpriteObj(std::string identifier, std::string spriteFile) :
    GameObject(identifier), spriteFile(spriteFile)
{
    this->texture.loadFromFile(this->spriteFile);
    this->sprite.setTexture(this->texture);
}

SpriteObj::SpriteObj(const SpriteObj& other) :
    GameObject(other.getIdentifier()), spriteFile(other.getSpriteFile())
{
    this->texture.loadFromFile(this->spriteFile);
    this->sprite.setTexture(this->texture);
}

SpriteObj::~SpriteObj() { }

void SpriteObj::update() {

}

void SpriteObj::render(sf::RenderWindow& window) {
    window.draw(this->sprite);
}

void SpriteObj::setPosition(sf::Vector2f position) {
    sprite.setPosition(position);
}

void SpriteObj::setScale(sf::Vector2f scale) {
    sprite.setScale(scale);
}

std::string SpriteObj::getSpriteFile() const {
    return this->spriteFile;
}