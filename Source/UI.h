#pragma once

#include <Graphics/Sprite.h>

class UI
{
public:
	//コンストラクタ・デストラクタ
	UI() {}
	virtual ~UI() {}
	
	// 初期化
	virtual void Initialize() = 0;

	// 終了化
	virtual void Finalize() = 0;

	// 更新処理
	virtual void Update(float elapsedTime) = 0;

	// 描画処理
	virtual void Render() = 0;



private:
	Sprite* clock = nullptr;


	//std::vector<Sprite*>
};