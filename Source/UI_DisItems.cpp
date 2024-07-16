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

	objs[0].position = { 0, 0, 0 };
	objs[1].position = { 100, 0, 0 };
	objs[2].position = { 200, 0, 0 };
	objs[3].position = { 300, 0, 0 };
	objs[4].position = { 400, 0, 0 };
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
	for (Object& obj : objs)
	{
		// �k�����x�̌v�Z
		obj.scale_velocity.y += gravity * elapsedTime * 60.0f;

		// �k������
		obj.scale.x += obj.scale_velocity.x;
		obj.scale.y += obj.scale_velocity.y;

		// �{�^����������Ă��Ȃ�������ŏ��l�� 1.0 �ɂ��Ă���
		if (obj.isPlay == false)
		{
			minScaling = 1.0f;
		}
		else
		{
			minScaling = 0.0f;
		}

		if (obj.scale.x < minScaling)
			obj.scale.x = minScaling;
		if (obj.scale.y < minScaling)
		{
			obj.scale.y = minScaling;
			if (obj.isPlay)
			{
				obj.exist = false;
			}
		}
	}
}

void DisItems::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();

	//���̎l�p
	spr->Render(dc,
		5, 5,
		500, 100,
		0, 0,
		static_cast<float>(spr->GetTextureWidth()),
		static_cast<float>(spr->GetTextureHeight()),
		0,
		0, 1, 1, 1
	);

	//2D�X�v���C�g�`��
	for (Object& obj : objs)
	{
		//�O�g
		spr_flame->Render(dc,
			obj.position.x + 10, obj.position.y + 15,
			80 * obj.scale.x, 80 * obj.scale.y,
			0, 0,
			static_cast<float>(spr_flame->GetTextureWidth()),
			static_cast<float>(spr_flame->GetTextureHeight()),
			0,
			1, 0, 1, 1
		);

		//�I�u�W�F�N�g�摜
		if (obj.exist)
		{
			spr_obj->Render(dc,
				obj.position.x + 23, obj.position.y + 30,
				50, 50,
				100, 100,
				static_cast<float>(spr_obj->GetTextureWidth()),
				static_cast<float>(spr_obj->GetTextureHeight()),
				0,
				1, 1, 0, 1
			);
		}
	}
}

void DisItems::Play(int index)
{
	Object& obj = objs[index];

	{		
		StartScaling(index, 2.0f);

		obj.isPlay = true;
	}
}


// �g��J�n�̊֐�
void DisItems::StartScaling(int index, float t)
{
	objs[index].scale_velocity.x = t;
	objs[index].scale_velocity.y = t;
}

