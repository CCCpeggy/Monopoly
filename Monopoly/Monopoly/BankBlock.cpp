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

	Game::showDialog("�g�L�Ȧ�", "�i�H�i������ާ@");
	//TODO:�ާ@���O
	/*
	�i�ϥ� Player::
		void deposit (int);//�s�� �{��->�s��
		void withdraw(int);//���� �s��->�{��
		void loan(int);//�U��
		void returnLoan(int);//�ٶU��
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
