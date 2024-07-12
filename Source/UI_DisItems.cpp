#include "Graphics/Graphics.h"
#include "UI.h"
#include "UI_DisItems.h"

void DisItems::Initialize()
{
	//スプライト初期化
	spr = new Sprite("Data/Sprite/test_UI.png");
}

void DisItems::Finalize()
{
	//スプライト終了化
	if (spr != nullptr)
	{
		delete spr;
		spr = nullptr;
	}
}

void DisItems::Update(float elapsedTime)
{
	//もしアイテムをとったら
	 
	//アイテム画像を消す

	////外枠アニメーション(ステートマシーン)
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
			0,
			1, 1, 1, 1
		);
	}
}
