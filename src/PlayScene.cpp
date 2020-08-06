#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "../headers/include/PlayScene.h"
#include "../headers/include/MenuScene.h"
#include "../headers/include/EndScene.h"
#include "../headers/include/Game.h"
using namespace std;

PlayScene::PlayScene()
{
    // Crear el personaje
    player = new Character(Vector2f(100, 200));
    add(player);

    minVel = 150;
    createNewEnemy(minVel);
    timeToNewBall.restart();

    // Music
    if (!bgm.openFromFile("./assets/music/astronomia_bgm.wav"))
        cout << "error" << endl;
    else
    {
        bgm.setLoop(true);
        bgm.play();
    }
    // Music

    // Puntaje
    if (!fontScoreText.loadFromFile("./assets/font/Cave-Story.ttf"))
    {
        cerr << "ERROR: no se encontro la fuente "
            << "PlayScene.cpp"
            << endl;
    }
    // Puntaje
    
    // Texturas de nuestros videojuego
    textBackground.loadFromFile("./assets/swamp-game-tileset/2 Background/Background.png");
    spBackground.setTexture(textBackground);
    // Texturas de nuestros videojuego

    score = 0;
    scoreText.setFont(fontScoreText);
    scoreText.setFillColor(Color::White);
}

void PlayScene::update(float elapsed)
{
    //  actualiza el personaje
    BaseScene::update(elapsed);
    // creamos nuevo enemigo
    if (timeToNewBall.getElapsedTime().asSeconds() > 20)
    {
        minVel += 20;
        createNewEnemy(minVel);
        timeToNewBall.restart();
    }
    // Colisiones entre el personaje y las pelotas
    for (const auto &enemy : enemies)
    {
        if (player->collidesWithEnemy(enemy))
        {
            //Dos opciones enter o esc

            if (score > Global::highScore)
                Global::highScore = score;
            // Programar el exit
            cout << "Programar exit " << endl;
            Game::getInstance().switchScene(new EndScene());
        }
    }

    // actualiza el puntaje
    score += elapsed;
    stringstream tmp;
    tmp << "PUNTAJE: " << int(score);
    scoreText.setString(tmp.str());
}

void PlayScene::draw(RenderWindow &window)
{
    // Limpia la pantalla
    window.draw(spBackground);
    BaseScene::draw(window);
    window.draw(scoreText);
}

void PlayScene::createNewEnemy(float minVel)
{
    Enemy *b = new Enemy();
    enemies.push_back(b);
    add(b);
}