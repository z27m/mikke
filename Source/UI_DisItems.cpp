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
	// 縮小速度の計算
	scale_velocity.y += gravity * elapsedTime * 60.0f;

	// 縮小処理
	scale.x += scale_velocity.x;
	scale.y += scale_velocity.y;

	// ボタンを押されていなかったら最小値を 1.0 にしておく
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

	// 描画処理
	RenderContext rc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ライト方向（下方向）

	//2Dスプライト描画
	{
		//下の四角
		spr->Render(dc,
			positionX, positionY,
			Width, Height,
			0, 0,
			static_cast<float>(spr->GetTextureWidth()),
			static_cast<float>(spr->GetTextureHeight()),
			0,
			1, 1, 1, 1
		);

		//外枠
		spr_flame->Render(dc,
			positionX, positionY,
			Width, Height,
			0, 0,
			static_cast<float>(spr->GetTextureWidth()),
			static_cast<float>(spr->GetTextureHeight()),
			0,
			1, 1, 1, 1
		);

		//オブジェクト画像
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


// 拡大開始の関数
void DisItems::StartScaling(float t)
{
	scale_velocity.y = t;
}

