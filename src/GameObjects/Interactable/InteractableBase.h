#pragma once

#include "EditorInteractable.h"
#include "ItemDB.h"

class BaseRoom;

class InteractableBase : public EditorInteractable 
{

public:
	InteractableBase(std::string InteractableName, BaseRoom* OwnerRefernce);
	~InteractableBase();

	virtual void Start() abstract;

	virtual void Update() abstract;

	virtual void Render();

	void SetCorrectItem(Item_Type type, bool consume = false, bool repeat = true);

	virtual bool CheckInteract(sf::FloatRect MousePosition);
	virtual bool CheckInteract(sf::Vector2f MousePosition);
	virtual bool CheckInteract(sf::Vector2i MousePosition);

	virtual void OnInteract(class Inventory* inv) abstract;

	//Not Shown for the player, used for JSON Parsing
	std::string name;

	BaseRoom* Owner;
	bool isInteractable = true;

protected:
	virtual void OnFail(Item_Type item) abstract;

	Item_Type CorrectItem = Item_Type::EMPTY;
	bool ConsumeItem = false;
	bool repeatable = false;

};
