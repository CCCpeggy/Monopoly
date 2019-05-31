#include "Item.h"
#include "BaseBlock.h"
#include "Player.h"
vector<Item> Item::itemList ={ 
	Item("路障", "放置到指定格子上，使經過的玩家停止。", 0)
	,Item("遙控骰子", "自由選擇前進的點數(2~12)", 1) 
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
