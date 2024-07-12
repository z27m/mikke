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

	//void RenderClock();

private:
	Sprite* spr = nullptr;

	const float ToRadian = 6.0f;
	float angle = 90;

	float Width = 1100;		//横表示サイズ(幅)
	float Height = 100;		//縦表示サイズ(高さ)

	float positionX = 200;	//表示位置
	float positionY = 50;

};