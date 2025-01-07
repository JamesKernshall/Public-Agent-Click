#pragma once

#include "GameObjects/GameObject.h"
#include "GameObjects/Interactable/ItemDB.h"
#include "PlayerAnimationController.h"
#include "functional"

class Player : public GameObject
{
public:
	Player();

	using Callback = std::function<void(class Inventory* item)>;
	void init();
	void Start();
	void Update();
	void Render();

	int _GetDirection();

	void SetMovementTarget(sf::Vector2u start_pixel, sf::Vector2u end_pixel,sf::Image* image , Callback interaction = nullptr);
	void MoveToTarget();
	void AdjustScale(float factor);
	void EnterRoom(sf::Vector2f pos, sf::Vector2u depthMapSize);

	//Getter
	bool IsPlayerMoving() { return isMoving; }

	class Inventory* inv;


private:

	void LerpToTarget();
	void OnCompletePath();


	PlayerAnimationController animator = PlayerAnimationController(this);

	sf::Vector2f previous_Target, current_Target;
	float lerpTime = 0;
	std::list<sf::Vector2u> target_path;
	std::list<sf::Vector2u>::iterator target_path_iterator;
	bool isMoving = false;
	float moveSpeed;
	float minTargetDistance = 4.3f;
	float baseScale = 5.75;
	float baseSpeed = 234.0f;

	sf::Vector2u depthSize = sf::Vector2u(1,1);

	Callback DelayInteraction;
};