#include "Graphics/Graphics.h"
#include "UI.h"
#include "UI_DisItems.h"
#include "SceneGame.h"
#include <Input/Input.h>
#include <Input/Mouse.h>

void DisItems::Initialize()
{
	//スプライト初期化
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
	//スプライト終了化
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
		// 縮小速度の計算
		obj.scale_velocity.x += gravity * elapsedTime * 100.0f;
		obj.scale_velocity.y += gravity * elapsedTime * 100.0f;

		// 縮小処理
		obj.scale.x += obj.scale_velocity.x * elapsedTime;
		obj.scale.y += obj.scale_velocity.y * elapsedTime;

		// ボタンを押されていなかったら最小値を 1.0 にしておく
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

	//下の四角
	spr->Render(dc,
		0, 0,
		550, 120,
		0, 0,
		static_cast<float>(spr->GetTextureWidth()),
		static_cast<float>(spr->GetTextureHeight()),
		0,
		1, 1, 1, 1
	);

	//2Dスプライト描画
	for (Object& obj : objs)
	{
		//外枠
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
			//オブジェクト画像
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

// 拡大開始の関数
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


