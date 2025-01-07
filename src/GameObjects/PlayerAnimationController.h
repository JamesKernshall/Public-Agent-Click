#pragma once

#include "AnimatedGameObject.h"

class Player;

enum Animation
{
	Idle = 0,
	Walking = 1,
	Running = 2,
	ClimbVertical = 3
};

class PlayerAnimationController
{
public:
	explicit PlayerAnimationController(Player* playerRef);
	~PlayerAnimationController();
	void SetOrigin();


	void Update(float dt);
	void Render();
	Player* player;
	sf::Sprite* GetDefaultAnimation();
	void SetAnimationState(Animation state, AnimatedGameObject::Callback callback = nullptr);


private:
		void SetupAnimations();



	Animation current_animation_type;

	float minStandingVelocity = 2;

	AnimatedGameObject* current_animation;
	AnimatedGameObject* animations[4];

	AnimatedGameObject walk_animation;
	AnimatedGameObject idle_animation;
	AnimatedGameObject run_animation;
	AnimatedGameObject climb_animation;

};