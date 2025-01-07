#include "Data.h"
#include "Game.h"
#include <iostream>
#include "Core/DeltaTime.h"

Game::Game(sf::RenderWindow& game_window) : window(game_window)
{
    srand(time(NULL));

    //Create Data and assign window
    Data::GetInstance()->window = &game_window;
}

Game::~Game()
{

}

bool Game::init()
{
    Data::GetInstance()->OnGameStateSwitch = [this] {this->start(); };
    state_menu.init();
    state_gameplay.init();
    state_pause.init();
    state_GameWin.init();
    state_Debug.init();

    Data::GetInstance()->OnGameStateSwitch();
    return true;
}

void Game::start()
{
    switch (Data::GetInstance()->gamestate)
    {
    case (Data::Gameplay):
        state_gameplay.start();
        break;
    case (Data::Menu):
        state_menu.start();
        break;
    case (Data::Debug):
        state_Debug.start();
        break;
    case (Data::Winner):
        state_GameWin.start();
        break;
    }
}

void Game::update(float dt)
{
    Time::DeltaTime(dt);

    switch (Data::GetInstance()->gamestate)
    {
    case (Data::Gameplay):
        state_gameplay.update(dt);
        break;
    case (Data::Menu):
        state_menu.update(dt);
        break;
    case (Data::Paused):
        state_pause.update(dt);
        break;
    case(Data::Debug):
        state_Debug.update(dt);
        break;
    case(Data::Winner):
        state_GameWin.update(dt);
        break;
    }
}

void Game::render()
{
    switch (Data::GetInstance()->gamestate)
    {
    case (Data::Gameplay):
        state_gameplay.render();
        break;
    case (Data::Menu):
        state_menu.render();
        break;
    case (Data::Paused):
        state_gameplay.render(); // Render Gameplay behind pause
        state_pause.render();
        break;
    case (Data::Debug):
        state_Debug.render();
        break;
    case (Data::Winner):
        state_gameplay.render(); // Render Gameplay behind win
        state_GameWin.render();
        break;
    }
}


void Game::keyPressed(sf::Event event)
{
    switch (Data::GetInstance()->gamestate)
    {
    case (Data::Gameplay):
        state_gameplay.keyPressed(event);
        break;
    case (Data::Menu):
        state_menu.keyPressed(event);
        break;
    case (Data::Paused):
        state_pause.keyPressed(event);
        break;
    case (Data::Debug):
        state_Debug.keyPressed(event);
        break;
    case(Data::Winner):
        state_GameWin.keyPressed(event);
        break;
    }
}

void Game::keyReleased(sf::Event event)
{
    switch (Data::GetInstance()->gamestate)
    {
    case (Data::Gameplay):
        state_gameplay.keyReleased(event);
        break;
    case (Data::Menu):
        state_menu.keyReleased(event);
        break;
    case (Data::Paused):
        state_pause.keyReleased(event);
        break;
    case (Data::Debug):
        state_Debug.keyReleased(event);
        break;
    case (Data::Winner):
        state_GameWin.keyReleased(event);
        break;
    }
}


void Game::mouseClicked(sf::Event event)
{

    switch (Data::GetInstance()->gamestate)
    {
    case (Data::Gameplay):
        state_gameplay.mousePressed(event);
        break;
    case (Data::Menu):
        state_menu.mousePressed(event);
        break;
    case (Data::Debug):
        state_Debug.mousePressed(event);
    }
}