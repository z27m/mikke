#include "Graphics/Graphics.h"
#include "UI.h"
#include "UI_Clock.h"

void Clock::Initialize()
{
	//スプライト初期化
	spr_base = new Sprite("Data/Sprite/clock_base.png");
	spr_hands = new Sprite("Data/Sprite/clock_hands.png");
}

void Clock::Finalize()
{
	//スプライト終了化
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
		//360°回ったときの処理
	}
}

void Clock::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();

	// 描画処理
	RenderContext rc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ライト方向（下方向）

	//2Dスプライト描画
	{

		//時計地盤描画
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

		//時計針描画
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

