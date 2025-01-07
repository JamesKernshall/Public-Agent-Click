#include "AudioInteractable.h"
#include "Core/Data.h"
#include "GameObjects/Inventory.h"
#include <SFML/Audio.hpp>

AudioInteractable::AudioInteractable(std::string InteractableName, BaseRoom* OwnerRefernce) : InteractableBase(InteractableName, OwnerRefernce)
{
	InteractAudio = std::make_unique<sf::SoundBuffer>();
}

AudioInteractable::~AudioInteractable()
{

}

void AudioInteractable::Start()
{

}

void AudioInteractable::AttachAudio(std::string fileName)
{
	InteractAudio->loadFromFile(fileName);
}

void AudioInteractable::AttachFailAudio(Item_Type itemType, std::string fileName)
{
	sf::SoundBuffer buffer;
	if (buffer.loadFromFile(fileName))
	{
		failLines.emplace(itemType, buffer);
	}
}

void AudioInteractable::Update()
{
	
}

void AudioInteractable::Render()
{
	__super::Render();
}

void AudioInteractable::OnInteract(Inventory* inv)
{
	if (CorrectItem == inv->GetHeldItemType())
	{
		if (TryPlayNewSound(InteractAudio.get()))
		{
			if (ConsumeItem)
			{
				inv->RemoveHeldItem();
			}
			if (!repeatable)
			{
				CorrectItem = Item_Type::EMPTY;
			}
			SucceedInteract(inv);
		}
	}
	else
	{
		OnFail(inv->GetHeldItemType());
	}
	inv->DeselectHeldItem();
}

void AudioInteractable::SucceedInteract(Inventory* inv)
{

}

void AudioInteractable::OnFail(Item_Type item)
{
	if (failLines.contains(item))
	{
		TryPlayNewSound(&failLines[item]);
	}
	else
	{
		TryPlayNewSound(&Data::GetInstance()->generic_item_fail);
	}
}

bool AudioInteractable::TryPlayNewSound(sf::SoundBuffer* buffer)
{
	if (buffer == nullptr)
	{
		//If Audio is unnasigned return true to allow unassigned audio to work as normal
		return true;
	}

	sf::Sound* dialogue_SFX = &Data::GetInstance()->DialogueSource;

	if (dialogue_SFX->getStatus() == sf::Sound::Playing)
	{
		dialogue_SFX->stop();
	}

	if (dialogue_SFX->getStatus() != sf::Sound::Playing)
	{
		*dialogue_SFX = sf::Sound(*buffer);
		dialogue_SFX->play();
		return true;
	}

	return false;
}
	