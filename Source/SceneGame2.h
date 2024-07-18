#pragma once

#include "Player.h"
#include "CameraController.h"
#include "Scene.h"
#include "Graphics/Sprite.h"
#include "stageMain2.h"
#include "UI_DisItems.h"
#include <Audio/AudioSource.h>
#include <vector>

// ゲームシーン
class SceneGame2 :public Scene
{
public:
	SceneGame2() {}
	~SceneGame2() override {}

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
	StageMain2* stageMain2;

	Effect* maru = nullptr;
	Effect* batu = nullptr;

	Sprite* aka = nullptr;

	DisItems* disItems = nullptr;
	//int game_timer = 0;

	std::unique_ptr<AudioSource>	BGM_House;
	std::unique_ptr<AudioSource>	SE_yes;
	std::unique_ptr<AudioSource>	SE_not;

	// true...間違ったものをクリックした
	bool isMissFlag = false;
	// 間違ったものをクリックしたあとの赤背景が表示されている時間の経過時間の合計
	float totalTime = 0.0f;

	// チェックした StageFind のインデックスリスト
	std::vector<int> m_checkList;

	// チェックする数（これが必要数達したらクリア）
	int checkCount = 0;

protected:
	DirectX::XMFLOAT3 scale = { 1,1,1 };
};
