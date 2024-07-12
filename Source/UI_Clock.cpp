#include "Graphics/Graphics.h"
#include "UI.h"
#include "UI_Clock.h"

void Clock::Initialize()
{
	//�X�v���C�g������
	spr = new Sprite("Data/Sprite/test_UI.png");

}

void Clock::Finalize()
{
	//�X�v���C�g�I����
	if (spr != nullptr)
	{
		delete spr;
		spr = nullptr;
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
		//�����ŕ\���ʒu��ς���
		spr->Render(dc,
			positionX, positionY,
			Width, Height,
			0, 0,
			static_cast<float>(spr->GetTextureWidth()),
			static_cast<float>(spr->GetTextureHeight()),
			angle,
			1, 1, 1, 1
		);
	}
}

