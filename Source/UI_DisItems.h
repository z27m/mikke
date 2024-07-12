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

	//UI�̓��͏����֐�
	void UIInput(float size,float elapsedTime);
	
	// �g��J�n�̊֐�
	void StartScaling(float t);

	enum class SQUARE
	{
		NONE = -1,		//-1�F����
		NORMAL,			//0�F�ʏ�
		BIG,			//1�F�傫��
		SMOLE,			//2�F������
	};

private:
	Sprite* spr = nullptr;
	Sprite* spr_flame = nullptr;
	Sprite* spr_obj = nullptr;

	SQUARE state = SQUARE::NORMAL;
	float Width = 200;		//���\���T�C�Y(��)
	float Height = 50;		//�c�\���T�C�Y(����)

	float positionX = 5;	//�\���ʒu
	float positionY = 5;	

	DirectX::XMFLOAT3		scale_velocity = { 0,0,0 };
	DirectX::XMFLOAT3		position = { 0,0,0 };
	DirectX::XMFLOAT3		angle = { 0,0,0 };
	DirectX::XMFLOAT3		scale = { 1,1,1 };
	//float size = 0;

	// �k���W���i����d�͂ɂ��Ă���j
	float gravity = -0.2f;

	// true...�{�^���������ꂽ
	bool isPushLeftButtonFlag = false;

	// �X�P�[�����O�̍Œ�l
	float minScaling = 1.0f;
};