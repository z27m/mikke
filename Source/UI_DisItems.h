#pragma once

#include "UI.h"

//左上見つけたもの欄UI
//DisItems＝Discovered Items：見つけたもの
class DisItems :public UI
{
public:

	//DisItems() {};
	DisItems() {};
	~DisItems()override {};

	//初期化
	void Initialize() override;

	//終了化
	void Finalize() override;

	//更新処理
	void Update(float elapsedTime) override;

	//描画処理
	void Render() override;

	//アニメーション再生
	void Play(int index);
//	bool IsFinish() const { return isPushLeftButtonFlag && !isPlay; }
	
	// 拡大開始の関数
	void StartScaling(int index, float t);


	struct LoadImage
	{
		const char* filename;
		float tx, ty;
	};



	int stageNo;



private:
	Sprite* spr = nullptr;
	Sprite* spr_flame = nullptr;
	//Sprite* spr_obj = nullptr;


	struct Object
	{
		DirectX::XMFLOAT3		scale_velocity = { 0,0,0 };
		DirectX::XMFLOAT3		position = { 0,0,0 };
		DirectX::XMFLOAT3		angle = { 0,0,0 };
		DirectX::XMFLOAT3		scale = { 0,0,0 };
		bool	exist = true;
		bool	isPlay = false;

		Sprite* spr_obj = nullptr;
		float tx, ty;
	};
	Object		objs[5];
	


	// 縮小係数（現状重力にしている）
	float gravity = -0.2f;

	// スケーリングの最低値
	float minScaling = 0.5f;

	// true...ボタンが押された
//	bool isPushLeftButtonFlag = false;
//	bool isPlay = false;
};