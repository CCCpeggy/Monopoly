#include "Item.h"
#include "BaseBlock.h"
#include "Player.h"
vector<Item> Item::itemList ={ 
	Item("����", "��m����w��l�W�A�ϸg�L�����a����C")
	,Item("������l", "�ۥѿ�ܫe�i���I��(2~12)") 
};


Item::Item(string newName, string newContent):name(newName),content(newContent)
{

}

Item::Item()
{
}


Item::~Item()
{
}
