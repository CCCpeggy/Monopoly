#include "BankBlock.h"
#include "Game.h"


void BankBlock::startEvent(Player*)
{
}

void BankBlock::arriveEvent(Player*)
{
}

void BankBlock::throughEvent(Player* player)
{

	Game::showDialog("經過銀行", "可以進行相關操作");
	//TODO:操作面板
	/*
	可使用 Player::
		void deposit (int);//存錢 現金->存款
		void withdraw(int);//提款 存款->現金
		void loan(int);//貸款
		void returnLoan(int);//還貸款
	*/
	return;
}

BankBlock& BankBlock::operator=(const BankBlock& b)
{
	BaseBlock::operator=(b);
	return *this;
}

BankBlock::BankBlock(string newName, int newIndex) :BaseBlock(newName, newIndex)
{
}

BankBlock::BankBlock()
{
}


BankBlock::~BankBlock()
{
}
