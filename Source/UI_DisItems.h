#pragma once

#include "UI.h"

//���㌩�������̗�UI
//DisItems��Discovered Items�F����������
class DisItems :public UI
{
public:
	//DisItems() {};
	DisItems() :state(SQUARE::NONE){};
	~DisItems()override {};

	//������
	void Initialize() override;

	//�I����
	void Finalize() override;

	//�X�V����
	void Update(float elapsedTime) override;

	//�`�揈��
	void Render() override;
	
	enum class SQUARE
	{
		NONE = -1,		//-1�F����
		NORMAL,			//0�F�ʏ�
		BIG,			//1�F�傫��
		SMOLE,			//2�F������
	};

private:
	Sprite* spr = nullptr;

	SQUARE state = SQUARE::NORMAL;
	float Width = 200;		//���\���T�C�Y(��)
	float Height = 50;		//�c�\���T�C�Y(����)

	float positionX = 5;	//�\���ʒu
	float positionY = 5;	
};