#include "Graphics/Graphics.h"
#include "UI.h"
#include "UI_DisItems.h"
#include "SceneGame.h"
#include <Input/Input.h>
#include <Input/Mouse.h>

void DisItems::Initialize()
{
	//スプライト初期化
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
		obj.scale_velocity.y += gravity * elapsedTime * 60.0f;

		// 縮小処理
		obj.scale.x += obj.scale_velocity.x;
		obj.scale.y += obj.scale_velocity.y;

		// ボタンを押されていなかったら最小値を 1.0 にしておく
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

	//下の四角
	spr->Render(dc,
		5, 5,
		500, 100,
		0, 0,
		static_cast<float>(spr->GetTextureWidth()),
		static_cast<float>(spr->GetTextureHeight()),
		0,
		0, 1, 1, 1
	);

	//2Dスプライト描画
	for (Object& obj : objs)
	{
		//外枠
		spr_flame->Render(dc,
			obj.position.x + 10, obj.position.y + 15,
			80 * obj.scale.x, 80 * obj.scale.y,
			0, 0,
			static_cast<float>(spr_flame->GetTextureWidth()),
			static_cast<float>(spr_flame->GetTextureHeight()),
			0,
			1, 0, 1, 1
		);

		//オブジェクト画像
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


// 拡大開始の関数
void DisItems::StartScaling(int index, float t)
{
	objs[index].scale_velocity.x = t;
	objs[index].scale_velocity.y = t;
}

