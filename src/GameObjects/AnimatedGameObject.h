#pragma once

#include "GameObject.h"
#include "list"
#include "functional"

class AnimatedGameObject
{
public:
	using Callback = std::function<void()>;
	void SetupAnimatedSprite(std::string fileName, sf::Vector2i spriteSize, int amountOfBlankTiles = 0);
	void SetFrame(int frame);
	void SetFrameRate(int frameRate);
	void AdvanceOneFrame();
	void Animate(float dt);
	void OnAnimationFinishSubscribeOnce(Callback callback);
	sf::Sprite sprite;
	float animationSpeed = 0.125;
	bool isLooping = true;
	bool isPlaying = true;
	bool isFlipped = false;

private:
	float localTime;
	int currentAnimationKeyFrame = 0;
	int animation_length = 0;
	sf::Vector2i* animation_key_frames;
	sf::Vector2i spriteSize;

	void UpdateFrameVisual();
	void CallSubscribableEvents();
	bool CheckTexturePartHasTextures(sf::Vector2i texturePart);
	
	std::list<Callback> callbacks;

};
