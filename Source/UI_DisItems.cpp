#include "Graphics/Graphics.h"
#include "UI.h"
#include "UI_DisItems.h"

void DisItems::Initialize()
{
	//�X�v���C�g������
	spr = new Sprite("Data/Sprite/test_UI.png");
}

void DisItems::Finalize()
{
	//�X�v���C�g�I����
	if (spr != nullptr)
	{
		delete spr;
		spr = nullptr;
	}
}

void DisItems::Update(float elapsedTime)
{
	//�����A�C�e�����Ƃ�����
	 
	//�A�C�e���摜������

	////�O�g�A�j���[�V����(�X�e�[�g�}�V�[��)
	//switch (state)
	//{
	//case SQUARE::NORMAL:

	//	break;
	//case SQUARE::BIG:
	//	Width += 10.0f * elapsedTime;
	//	Height += 10.0f * elapsedTime;

	//	break;
	//case SQUARE::SMOLE:
	//	Width -= 10.0f * elapsedTime;
	//	Height -= 10.0f * elapsedTime;

	//	break;
	//case SQUARE::NONE:

	//	break;
	//}




}

void DisItems::Render()
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
			0,
			1, 1, 1, 1
		);
	}
}
