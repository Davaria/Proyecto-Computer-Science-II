#ifndef CHARACTER_H
#define CHARACTER_H

#include "./Entity.h"
#include "../../src/Enemy.cpp"
#include "../include/Collider.h"
// Incluir enemy
// Standart C+11 -> Sobreescribir una funcion de una clase base
class Character : public Entity
{
private:
    RectangleShape body;
    Sprite spChar;
    Texture textCharIdle;
    Texture textCharRun;
    Texture textCharAtk;
    Texture textCharJump;
    //Estadisticas Personaje
    const float charVel = 3.0;
    unsigned int HP = 1000;
    float jumpheight = 0.01f;
    // Animacion
    Animation charAnim;
    float deltaTime = 0.0f;
    Clock clock;
    bool faceR;

public:
    Character(const Vector2f &);
    // Manejo de escena
    void update(float elapsed) override;
    void draw(RenderWindow &) override;
    // Metodo que devuelva el sprite
    Sprite getSprite();
    // Cuando colisiona con el enemigo
    bool collidesWithEnemy(Enemy *);
};

#endif