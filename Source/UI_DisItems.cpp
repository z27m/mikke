#include "Graphics/Graphics.h"
#include "UI.h"
#include "UI_DisItems.h"
#include "SceneGame.h"
#include <Input/Input.h>
#include <Input/Mouse.h>



DisItems::LoadImage stage1Images[5] =
{
	{"Data/Sprite/hook.png", 100, 100},		//かぎづめ
	{"Data/Sprite/key.png", 50, 90},		//鍵
	{"Data/Sprite/ring.png", 50, 90},		//本
	{"Data/Sprite/lock.png", 30, 30},		//南京錠
	{"Data/Sprite/beal.png",  50, 90},		//ビール
};
DisItems::LoadImage stage2Images[5] =
{
	{"Data/Sprite/bird.png", 90, 60},			//鳥
	{"Data/Sprite/butterfly.png", 90, 60},		//蝶々
	{"Data/Sprite/cookie.png", 90, 60},			//クッキー
	{"Data/Sprite/karasu.png",  90, 60},		//カラス
	{"Data/Sprite/tentoumushi.png", 90, 60},	//テントウムシ
	
};

DisItems::LoadImage* stageImages[2] =
{
	stage1Images,
	stage2Images
};


void DisItems::Initialize()
{
	//スプライト初期化
	spr = new Sprite("Data/Sprite/spr.png");
	spr_flame = new Sprite("Data/Sprite/flame.png");
	//spr_obj = new Sprite("Data/Sprite/ring.png");
	//spr_obj = new Sprite("Data/Sprite/beal.png");
	//spr_obj = new Sprite("Data/Sprite/lock.png");
	//spr_obj = new Sprite("Data/Sprite/key.png");
	//spr_obj = new Sprite("Data/Sprite/book.png");

	objs[0].position = { 40 + 23, 40 + 5, 0 };
	objs[1].position = { 140 + 23,40 + 5, 0 };
	objs[2].position = { 240 + 23,40 + 5, 0 };
	objs[3].position = { 340 + 23,40 + 5, 0 };
	objs[4].position = { 440 + 23,40 + 5, 0 };
	//objs[0].spr_obj = new Sprite("Data/Sprite/ring.png");
	//objs[1].spr_obj = new Sprite("Data/Sprite/beal.png");
	//objs[2].spr_obj = new Sprite("Data/Sprite/lock.png");
	//objs[3].spr_obj = new Sprite("Data/Sprite/key.png");
	//objs[4].spr_obj = new Sprite("Data/Sprite/book.png");
	//objs[4].tx = 50;
	//objs[4].ty = 90;

	for (int i=0; i<5; ++i)
	{
		objs[i].spr_obj = new Sprite(stageImages[stageNo][i].filename);
		objs[i].tx = stageImages[stageNo][i].tx;
		objs[i].ty = stageImages[stageNo][i].ty;
	}
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
	
	for (Object& obj : objs)
		if (obj.spr_obj != nullptr)
		{
			delete obj.spr_obj;
			obj.spr_obj = nullptr;
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

		}
		//オブジェクト画像
		if (!obj.isPlay)
		{
			obj.spr_obj->Render(dc,
				obj.position.x - 30, obj.position.y - 15,
				100, 100,
				obj.tx, obj.ty,
				static_cast<float>(obj.spr_obj->GetTextureWidth()),
				static_cast<float>(obj.spr_obj->GetTextureHeight()),
				0,
				1, 1, 1, 1
			);
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


