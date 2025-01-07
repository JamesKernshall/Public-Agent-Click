#pragma once

#include "InteractableBase.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class AudioInteractable : public InteractableBase
{
public:

	AudioInteractable(std::string InteractableName, BaseRoom* OwnerRefernce);

	~AudioInteractable();


	virtual void Start();

	void AttachAudio(std::string fileName);

	void AttachFailAudio(Item_Type itemType, std::string fileName);

	virtual void Update();

	virtual void Render();

	virtual void OnInteract(class Inventory* inv) override;

	virtual void SucceedInteract(class Inventory* inv);

protected:
	bool TryPlayNewSound(sf::SoundBuffer* buffer);

private:
	virtual void OnFail(Item_Type item);

	


	std::unique_ptr<sf::SoundBuffer> InteractAudio;
	std::map<Item_Type, sf::SoundBuffer> failLines;
};