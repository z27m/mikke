#include "Graphics/Graphics.h"
#include "UI.h"
#include "UI_DisItems.h"
#include "SceneGame.h"
#include <Input/Input.h>
#include <Input/Mouse.h>

void DisItems::Initialize()
{
	//�X�v���C�g������
	spr = new Sprite("Data/Sprite/test_UI.png");
	spr_flame = new Sprite("Data/Sprite/test_UI.png");
	spr_obj = new Sprite("Data/Sprite/test_UI.png");
}

void DisItems::Finalize()
{
	//�X�v���C�g�I����
	if (spr != nullptr)
	{
		delete spr;
		spr = nullptr;
	}
	
	if (spr_flame != nullptr)
	{
		delete spr_flame;
		spr_flame = nullptr;
	}
	
	if (spr_obj != nullptr)
	{
		delete spr_obj;
		spr_obj = nullptr;
	}
}

void DisItems::Update(float elapsedTime)
{
	// �k�����x�̌v�Z
	scale_velocity.y += gravity * elapsedTime * 60.0f;

	// �k������
	scale.x += scale_velocity.x;
	scale.y += scale_velocity.y;

	// �{�^����������Ă��Ȃ�������ŏ��l�� 1.0 �ɂ��Ă���
	if (isPushLeftButtonFlag == false)
	{
		minScaling = 1.0f;
	}
	else
	{
		minScaling = 0.0f;
	}

	if (scale.x < minScaling)
		scale.x = minScaling;
	if (scale.y < minScaling)
		scale.y = minScaling;
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
		//���̎l�p
		spr->Render(dc,
			positionX, positionY,
			Width, Height,
			0, 0,
			static_cast<float>(spr->GetTextureWidth()),
			static_cast<float>(spr->GetTextureHeight()),
			0,
			1, 1, 1, 1
		);

		//�O�g
		spr_flame->Render(dc,
			positionX, positionY,
			Width, Height,
			0, 0,
			static_cast<float>(spr->GetTextureWidth()),
			static_cast<float>(spr->GetTextureHeight()),
			0,
			1, 1, 1, 1
		);

		//�I�u�W�F�N�g�摜
		spr_obj->Render(dc,
			positionX, positionY,
			Width, Height,
			0, 0,
			static_cast<float>(spr->GetTextureWidth()),
			static_cast<float>(spr->GetTextureHeight()),
			0,
			1, 1, 0, 1
		);
	}
}

void DisItems::UIInput(float size, float elapsedTime)
{
	Mouse& mouse = Input::Instance().GetMouse();
	if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
	{		
		StartScaling(2.0f);

		isPushLeftButtonFlag = true;

#if false
		if (my > 0.0f)
		{
			position.y += my;
			position.x += my;
		}
		else
		{

		}
#endif

	}
}


// �g��J�n�̊֐�
void DisItems::StartScaling(float t)
{
	scale_velocity.y = t;
}

