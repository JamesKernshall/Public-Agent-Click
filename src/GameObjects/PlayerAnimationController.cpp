#include "PlayerAnimationController.h"
#include "Player.h"
#include "Core/Data.h"

PlayerAnimationController::PlayerAnimationController(Player* playerRef)
{
    this->player = playerRef;
    SetupAnimations();
}

void PlayerAnimationController::SetupAnimations()
{
    sf::Vector2i sprite_size = sf::Vector2i(16, 32);
    idle_animation.SetupAnimatedSprite("Data/Characters/Agent/SMS_Adv_Idle.png", sprite_size);
    idle_animation.isLooping = true;
    walk_animation.SetupAnimatedSprite("Data/Characters/Agent/SMS_Adv_Walk.png", sprite_size);
    walk_animation.isLooping = true;
    run_animation.SetupAnimatedSprite("Data/Characters/Agent/SMS_Adv_Run.png", sprite_size);
    run_animation.isLooping = true;

    climb_animation.SetupAnimatedSprite("Data/Characters/Agent/Climb/SMS_Adv_Climb_South_Hoist_UP.png", sprite_size);

    animations[0] = &idle_animation;
    animations[1] = &walk_animation;
    animations[2] = &run_animation;
    animations[3] = &climb_animation;
}

void PlayerAnimationController::Update(float dt)
{
    current_animation = animations[current_animation_type];

    // Flip X depending on direction
    if (player->_GetDirection() < 0)
    {
        current_animation->isFlipped = true;
    }
    else
    {
        current_animation->isFlipped = false;
    }

    current_animation->Animate(dt);
}

void PlayerAnimationController::Render()
{
    current_animation->sprite.setPosition(player->sprite->getPosition());
    current_animation->sprite.setScale(player->sprite->getScale());
    Data::RenderGameObject(current_animation->sprite);  
}

sf::Sprite* PlayerAnimationController::GetDefaultAnimation()
{
    current_animation = animations[0];
    return &animations[0]->sprite;
}

void PlayerAnimationController::SetAnimationState(Animation state, AnimatedGameObject::Callback callback)
{
    if (callback != nullptr)
    {
        animations[current_animation_type]->OnAnimationFinishSubscribeOnce(callback);
    }

    current_animation_type = state;
    animations[current_animation_type]->SetFrame(0);
}

PlayerAnimationController::~PlayerAnimationController()
= default;

void PlayerAnimationController::SetOrigin()
{
    for (auto& animation : animations)
    {
        animation->sprite.setOrigin(player->sprite->getOrigin());
    }
}
