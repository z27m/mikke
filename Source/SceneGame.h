#pragma once


#include "Player.h"
#include "CameraController.h"
#include "Scene.h"
#include "Graphics/Sprite.h"
#include "stageMain.h"
#include "UI_Clock.h"
#include "UI_DisItems.h"
#include "Audio/Audio.h"
#include <vector>

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

	Sprite* aka = nullptr;
	
	Clock* clock = nullptr;
	DisItems* disItems = nullptr;
	//int game_timer = 0;

	std::unique_ptr<AudioSource>	BGM_Sea;

	// true...間違ったものをクリックした
	bool isMissFlag = false;
	// 間違ったものをクリックしたあとの赤背景が表示されている時間の経過時間の合計
	float totalTime = 0.0f;

	int delItem = -1;

	// チェックした StageFind のインデックスリスト
	std::vector<int> m_checkList;

	// チェックする数（これが必要数達したらクリア）
	int checkCount = 0;

private:
	enum DisItemNum
	{
		ObjNone = -1,
		Obj0,
		Obj1,
		Obj2,
		Obj3,
		Obj4,
		Obj5
	};
protected:
	DirectX::XMFLOAT3 scale = { 1,1,1 };
};
