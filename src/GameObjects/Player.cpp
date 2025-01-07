#include "Player.h"
#include "Core/DeltaTime.h"
#include "Pathfinding/AStar.h"
#include "Room/BaseRoom.h"

Player::Player() : GameObject()
{
	init();
}

void Player::init()
{
	GameObject::CreateSprite(*sprite, "Data/Characters/Agent/SMS_Adv_IdleTemplate.png");
	sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height);
	sprite->setScale(sf::Vector2f(baseScale, baseScale));
	moveSpeed = baseSpeed;
}

void Player::Start()
{
	animator.SetAnimationState(Animation::Idle);
	animator.SetOrigin();
}

void Player::Update()
{
	animator.Update(Time::DeltaTime());

	if (isMoving)
	{
		MoveToTarget();
	}
}

void Player::Render()
{
	sprite->setColor(sf::Color::Red);
	//Data::RenderGameObject(*sprite);
	animator.Render();
}

int Player::_GetDirection()
{
	if (isMoving)
	{
		if((current_Target.x - previous_Target.x) > 0.001f)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	return 0;
}

void Player::SetMovementTarget(sf::Vector2u startPixel, sf::Vector2u endPixel, sf::Image* image, Callback interaction)
{
	isMoving = true;
	DelayInteraction = interaction;
	animator.SetAnimationState(Animation::Running);

	target_path = AStar::find_path(startPixel, endPixel, image);

	//If path is where player already is or invalid
	if (target_path.size() < 2)
	{
		OnCompletePath();
		return;
	}

	target_path_iterator = target_path.begin();
	previous_Target = BaseRoom::ConvertDepthPixelToWorldPosition(*target_path_iterator, depthSize);
	target_path_iterator++;
	current_Target = BaseRoom::ConvertDepthPixelToWorldPosition(*target_path_iterator, depthSize);
	lerpTime = 0;
}

void Player::MoveToTarget()
{
	lerpTime += Time::DeltaTime() * moveSpeed;
	LerpToTarget();
}

void Player::LerpToTarget()
{
	if (++target_path_iterator == target_path.end())
	{
		OnCompletePath();
		return;
	}
	--target_path_iterator;

	if (lerpTime > 1)
	{
		lerpTime--;
		previous_Target = current_Target;
		target_path_iterator++;
		current_Target = BaseRoom::ConvertDepthPixelToWorldPosition(*target_path_iterator, depthSize);
		LerpToTarget();
		return;
	}


	float lerpX = Data::Lerp(previous_Target.x, current_Target.x, lerpTime);
	float lerpY = Data::Lerp(previous_Target.y, current_Target.y, lerpTime);

	sprite->setPosition(lerpX, lerpY);
}

void Player::OnCompletePath()
{
	isMoving = false;
	animator.SetAnimationState(Animation::Idle);

	if (DelayInteraction != nullptr)
	{
		DelayInteraction(inv);
		DelayInteraction = nullptr;
	}
}


void Player::AdjustScale(float factor)
{
	float scaleFactor = baseScale / factor * 10;
	sprite->setScale(scaleFactor, scaleFactor);

	moveSpeed = baseSpeed / factor * 2;

}

void Player::EnterRoom(sf::Vector2f pos, sf::Vector2u depthMapSize)
{
	sprite->setPosition(pos);

	depthSize = depthMapSize;

	//Wait to be properly scaled by room manager
	sprite->setScale(sf::Vector2f(0.0001f, 0.0001f));
}

