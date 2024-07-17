#include "Graphics/Graphics.h"
#include "UI.h"
#include "UI_Clock.h"

void Clock::Initialize()
{
	//�X�v���C�g������
	spr_base = new Sprite("Data/Sprite/clock_base.png");
	spr_hands = new Sprite("Data/Sprite/clock_hands.png");
}

void Clock::Finalize()
{
	//�X�v���C�g�I����
	if (spr_base != nullptr)
	{
		delete spr_base;
		spr_base = nullptr;
	}
	if (spr_hands != nullptr)
	{
		delete spr_hands;
		spr_hands = nullptr;
	}

}

void Clock::Update(float elapsedTime)
{
	float clockAngle = angle += ToRadian * elapsedTime;
	if (clockAngle == 360)
	{
		//360��������Ƃ��̏���
	}
}

void Clock::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();

	// �`�揈��
	RenderContext rc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ���C�g�����i�������j

	//2D�X�v���C�g�`��
	{

		//���v�n�Օ`��
		spr_base->Render(dc,
			positionX+10, positionY,
			Width,
			Height,
			0, 0,
			static_cast<float>(spr_base->GetTextureWidth()),
			static_cast<float>(spr_base->GetTextureHeight()),
			0,
			1, 1, 1, 1
		);

		//���v�j�`��
		spr_hands->Render(dc,
			positionX+10, positionY+22,
			Width, Height,
			0, 150,
			static_cast<float>(spr_hands->GetTextureWidth()),
			static_cast<float>(spr_hands->GetTextureHeight()),
			angle,
			1, 1, 1, 1
		);
	}
}

