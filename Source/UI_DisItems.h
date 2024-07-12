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
	
	enum class SQUARE
	{
		NONE = -1,		//-1：消す
		NORMAL,			//0：通常
		BIG,			//1：大きく
		SMOLE,			//2：小さく
	};

private:
	Sprite* spr = nullptr;

	SQUARE state = SQUARE::NORMAL;
	float Width = 200;		//横表示サイズ(幅)
	float Height = 50;		//縦表示サイズ(高さ)

	float positionX = 5;	//表示位置
	float positionY = 5;	
};