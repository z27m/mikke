#include "Graphics/Graphics.h"
#include "UI.h"
#include "UI_DisItems.h"
#include "SceneGame.h"
#include <Input/Input.h>
#include <Input/Mouse.h>

void DisItems::Initialize()
{
	//�X�v���C�g������
	spr = new Sprite("Data/Sprite/spr.png");
	spr_flame = new Sprite("Data/Sprite/flame.png");
	spr_obj = new Sprite("Data/Sprite/test_UI.png");

	objs[0].position = { 40 + 23, 40 + 5, 0 };
	objs[1].position = { 140 + 23,40 + 5, 0 };
	objs[2].position = { 240 + 23,40 + 5, 0 };
	objs[3].position = { 340 + 23,40 + 5, 0 };
	objs[4].position = { 440 + 23,40 + 5, 0 };
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
		obj.scale_velocity.x += gravity * elapsedTime * 100.0f;
		obj.scale_velocity.y += gravity * elapsedTime * 100.0f;

		// �k������
		obj.scale.x += obj.scale_velocity.x * elapsedTime;
		obj.scale.y += obj.scale_velocity.y * elapsedTime;

		// �{�^����������Ă��Ȃ�������ŏ��l�� 1.0 �ɂ��Ă���
		if (obj.isPlay == false)
		{
			minScaling = 1.0f;
		}
		else
		{
			minScaling = 0.0f;
		}

		if (obj.scale.y < minScaling ||
			obj.scale.x < minScaling)
		{
			obj.scale.y = minScaling;
			obj.scale.x = minScaling;
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
		0, 0,
		550, 120,
		0, 0,
		static_cast<float>(spr->GetTextureWidth()),
		static_cast<float>(spr->GetTextureHeight()),
		0,
		1, 1, 1, 1
	);

	//2D�X�v���C�g�`��
	for (Object& obj : objs)
	{
		//�O�g
		if (obj.exist)
		{
			float sizeW = 80 * obj.scale.x;
			float sizeH = 80 * obj.scale.y;

			spr_flame->Render(dc,
				obj.position.x + 10 - sizeW / 2, obj.position.y + 15 - sizeH / 2,
				sizeW, sizeH,
				0, 0,
				static_cast<float>(spr_flame->GetTextureWidth()),
				static_cast<float>(spr_flame->GetTextureHeight()),
				0,
				1, 1, 1, 1
			);
			//�I�u�W�F�N�g�摜
			if (!obj.isPlay)
			{
				spr_obj->Render(dc,
					obj.position.x-15, obj.position.y-8 ,
					50, 50,
					100, 100,
					static_cast<float>(spr_obj->GetTextureWidth()),
					static_cast<float>(spr_obj->GetTextureHeight()),
					0,
					0, 0, 0, 1
				);
			}
		}

	}
}

// �g��J�n�̊֐�
void DisItems::StartScaling(int index, float t)
{
	objs[index].scale_velocity.x = t;
	objs[index].scale_velocity.y = t;
}

void DisItems::Play(int index)
{
	Object& obj = objs[index];

	{		
		StartScaling(index, 4.0f);

		obj.isPlay = true;
	}
}


