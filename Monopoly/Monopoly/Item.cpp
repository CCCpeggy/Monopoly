#include "Item.h"
#include "BaseBlock.h"
#include "Player.h"
vector<Item> Item::itemList ={ 
	Item("����", "��m����w��l�W�A�ϸg�L�����a����C", 0)
	,Item("������l", "�ۥѿ�ܫe�i���I��(2~12)", 1) 
};


Item::Item(string newName, string newContent, int index)
	:name(newName),content(newContent),index(index)
{

}

Item::Item()
{
}


Item::~Item()
{
}
