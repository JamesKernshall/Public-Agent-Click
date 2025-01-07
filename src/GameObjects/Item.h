#pragma once

#include "GameObject.h"
#include "Interactable/ItemDB.h"

class Item : public GameObject
{
public:
	Item();
	Item(const Item& item);
	Item(Item_Type item);

	bool operator==(const Item& item);
	Item& operator=(const Item& other);

	Item_Type item_type;

};