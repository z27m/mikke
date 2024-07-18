#pragma once

#include "UI.h"

//右上時計UI
class Clock :public UI
{
public:
	Clock() {};
	~Clock()override {};

	//初期化
	void Initialize() override;

	//終了化
	void Finalize() override;

	//更新処理
	void Update(float elapsedTime) override;

	//描画処理
	void Render() override;


	void Miss(float amount)
	{
		angle += amount;
	}

private:
	Sprite* spr_hands = nullptr;
	Sprite* spr_base = nullptr;

	const float ToRadian = 6.0f;
	//const float ToRadian = 30.0f;
	float angle = 0;

	float Width = 200;		//横表示サイズ(幅)
	float Height = 200;		//縦表示サイズ(高さ)

	float positionX = 1050;	//表示位置
	float positionY = 10;
};