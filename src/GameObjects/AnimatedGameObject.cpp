#include "AnimatedGameObject.h"

void AnimatedGameObject::SetupAnimatedSprite(std::string fileName, sf::Vector2i singleSpriteSize, int amountOfBlankTiles)
{
    GameObject::CreateSprite(sprite, fileName);
    spriteSize = singleSpriteSize;

    this->sprite.setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));

    int spriteMapWide = this->sprite.getTexture()->getSize().x / spriteSize.x;
    int spriteMapHeight = this->sprite.getTexture()->getSize().y / spriteSize.y;
    animation_length = spriteMapWide * spriteMapHeight;
    animation_length -= amountOfBlankTiles;

    animation_key_frames = new sf::Vector2i[animation_length];

    //Generate all whole keyframes based on a sprite size
    for (int height = 0; height < spriteMapHeight; height++)
    {
        for (int wide = 0; wide < spriteMapWide; wide++)
        {
            if (wide + (spriteMapWide * height) < animation_length)
            {
                animation_key_frames[wide + (spriteMapWide * height)] = sf::Vector2i(spriteSize.x * wide, spriteSize.y * height);
            }
            else
            {
                break;
            }
        }
    }

    localTime = 0;
}

void AnimatedGameObject::Animate(float dt)
{
    if (isPlaying)
    {
        if (localTime > animationSpeed)
        {
            localTime = 0;
            AdvanceOneFrame();
        }

        localTime += dt;
    }
}

void AnimatedGameObject::OnAnimationFinishSubscribeOnce(Callback callback)
{
    callbacks.push_back(callback);
}


void AnimatedGameObject::AdvanceOneFrame()
{
    currentAnimationKeyFrame++;
    if (currentAnimationKeyFrame > animation_length - 1)
    {
        currentAnimationKeyFrame = 0;

        if (isLooping)
        {
            UpdateFrameVisual();
        }
        else
        {
            isPlaying = false;
        }
        CallSubscribableEvents();
    }
    else
    {
        UpdateFrameVisual();
    }
}

void AnimatedGameObject::SetFrame(int frame)
{
    currentAnimationKeyFrame = frame;
    isPlaying = true;
    UpdateFrameVisual();
}

void AnimatedGameObject::UpdateFrameVisual()
{
    if (isFlipped)
    {
        sprite.setTextureRect(
            sf::IntRect(sf::Vector2i(animation_key_frames[currentAnimationKeyFrame].x + spriteSize.x, animation_key_frames[currentAnimationKeyFrame].y),
                sf::Vector2i(-spriteSize.x, spriteSize.y)));
    }
    else
    {
        sprite.setTextureRect(
            sf::IntRect(animation_key_frames[currentAnimationKeyFrame], spriteSize));
    }
}

void AnimatedGameObject::CallSubscribableEvents()
{
    for (const auto& callback : callbacks) 
    {
        callback();
    }

    callbacks.clear();
}

void AnimatedGameObject::SetFrameRate(int frameRate)
{
    animationSpeed = 1.0f / float(frameRate);
}