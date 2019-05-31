#include "Item.h"
#include "BaseBlock.h"
#include "Player.h"
vector<Item> Item::itemList ={ 
	Item("路障", "放置到指定格子上，使經過的玩家停止。")
	,Item("遙控骰子", "自由選擇前進的點數(2~12)") 
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
