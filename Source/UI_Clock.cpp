#include "Graphics/Graphics.h"
#include "UI.h"
#include "UI_Clock.h"

void Clock::Initialize()
{
	//スプライト初期化
	spr = new Sprite("Data/Sprite/test_UI.png");

}

void Clock::Finalize()
{
	//スプライト終了化
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
		//ここで表示位置を変える
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

