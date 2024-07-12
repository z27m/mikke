#pragma once

#include "UI.h"

//左上見つけたもの欄UI
//DisItems＝Discovered Items：見つけたもの
class DisItems :public UI
{
public:
	//DisItems() {};
	DisItems() :state(SQUARE::NONE){};
	~DisItems()override {};

	//初期化
	void Initialize() override;

	//終了化
	void Finalize() override;

	//更新処理
	void Update(float elapsedTime) override;

	//描画処理
	void Render() override;

	//UIの入力処理関数
	void UIInput(float size,float elapsedTime);
	
	// 拡大開始の関数
	void StartScaling(float t);

	enum class SQUARE
	{
		NONE = -1,		//-1：消す
		NORMAL,			//0：通常
		BIG,			//1：大きく
		SMOLE,			//2：小さく
	};

private:
	Sprite* spr = nullptr;
	Sprite* spr_flame = nullptr;
	Sprite* spr_obj = nullptr;

	SQUARE state = SQUARE::NORMAL;
	float Width = 200;		//横表示サイズ(幅)
	float Height = 50;		//縦表示サイズ(高さ)

	float positionX = 5;	//表示位置
	float positionY = 5;	

	DirectX::XMFLOAT3		scale_velocity = { 0,0,0 };
	DirectX::XMFLOAT3		position = { 0,0,0 };
	DirectX::XMFLOAT3		angle = { 0,0,0 };
	DirectX::XMFLOAT3		scale = { 1,1,1 };
	//float size = 0;

	// 縮小係数（現状重力にしている）
	float gravity = -0.2f;

	// true...ボタンが押された
	bool isPushLeftButtonFlag = false;

	// スケーリングの最低値
	float minScaling = 1.0f;
};