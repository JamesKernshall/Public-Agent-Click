#include "InteractableBase.h"
#include "Core/Data.h"

InteractableBase::InteractableBase(std::string InteractableName, BaseRoom* OwnerRefernce) : EditorInteractable()
{
	// Used for identifying json data
	name = InteractableName;
	Owner = OwnerRefernce;
	sprite->setPosition(Data::WindowGetSize().x / 2, Data::WindowGetSize().y / 2);
}

InteractableBase::~InteractableBase()
{

}

void InteractableBase::Render()
{
	Data::RenderGameObject(*this);
}

void InteractableBase::SetCorrectItem(Item_Type type, bool consume, bool repeat)
{
	CorrectItem = type;
	ConsumeItem = consume;
	repeatable = repeat;
}

bool InteractableBase::CheckInteract(sf::FloatRect MousePosition)
{
	return (sprite->getGlobalBounds().intersects(MousePosition));
}

bool InteractableBase::CheckInteract(sf::Vector2f MousePosition)
{
	return (sprite->getGlobalBounds().contains(MousePosition));
}

bool InteractableBase::CheckInteract(sf::Vector2i MousePosition)
{
	return CheckInteract(static_cast<sf::Vector2f>(MousePosition));
}

