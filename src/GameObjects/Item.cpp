#include "Item.h"

Item::Item() : GameObject()
{
	item_type = Item_Type::EMPTY;
}

Item::Item(const Item& item)
{
	item_type = item.item_type;
	sprite = item.sprite;
}

Item::Item(Item_Type type) : GameObject()
{
	item_type = type;
}

bool Item::operator==(const Item& item)
{
	return this->sprite == item.sprite;
}

Item& Item::operator=(const Item& other)
{
	if (this == &other) return *this;
}