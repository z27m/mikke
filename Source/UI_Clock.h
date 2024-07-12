#pragma once

#include "UI.h"

//�E�㎞�vUI
class Clock :public UI
{
public:
	Clock() {};
	~Clock()override {};

	//������
	void Initialize() override;

	//�I����
	void Finalize() override;

	//�X�V����
	void Update(float elapsedTime) override;

	//�`�揈��
	void Render() override;

	//void RenderClock();

private:
	Sprite* spr = nullptr;

	const float ToRadian = 6.0f;
	float angle = 90;

	float Width = 1100;		//���\���T�C�Y(��)
	float Height = 100;		//�c�\���T�C�Y(����)

	float positionX = 200;	//�\���ʒu
	float positionY = 50;

};