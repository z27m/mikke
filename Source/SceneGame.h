#pragma once


#include "Player.h"
#include "CameraController.h"
#include "Scene.h"
#include "Graphics/Sprite.h"
#include "stageMain.h"

// ゲームシーン
class SceneGame:public Scene
{
public:
	SceneGame() {}
	~SceneGame() override{}

	// 初期化
	void Initialize() override;

	// 終了化
	void Finalize() override;

	// 更新処理
	void Update(float elapsedTime) override;

	// 描画処理
	void Render() override;

private:
	//エネミーHPゲージ描画
	void CheckFindObject(
		ID3D11DeviceContext* dc,
		const DirectX::XMFLOAT4X4& view,
		const DirectX::XMFLOAT4X4& projection
	);

private:
	
	Player* player = nullptr;
	CameraController* cameraController = nullptr;
	Sprite* gauge = nullptr;
	StageMain* stageMain;

	Effect* maru = nullptr;
	Effect* batu = nullptr;

	//int game_timer = 0;
};
