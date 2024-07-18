#pragma once

#include "Scene.h"
#include "Graphics/Sprite.h"
#include "Graphics/Model.h"
#include <DirectXMath.h>

//// シーン選択クラス
class SceneSelect : public Scene
{
public:
    SceneSelect() {}
    ~SceneSelect() override {}

    // 初期化
    void Initialize() override;

    // 終了化
    void Finalize() override;

    // 更新処理
    void Update(float elapsedTime) override;

    // 描画処理
    void Render() override;

    // 他のメンバ関数や変数
    //bool HitTest(int x, int y); // クリック判定のための関数を追加

private:
    // モード（2D注意書き、3Dモデル1、3Dモデル2）
    enum Mode
    {
        Notice2D,
        Model3D_1,
        Model3D_2
    };

    DirectX::XMFLOAT3     position = { 0,-1,0 };
    DirectX::XMFLOAT3     angle = { 0,135,0 };
    DirectX::XMFLOAT3     scale = { 1,1,1 };
    //XMFLOAT4X4を使うために<DirectXMath.h>が必要
    DirectX::XMFLOAT4X4   transform =
    {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };

    void HandleClick(int x, int y);
public:
    Mode mode = Notice2D;
    Model* model1 = nullptr;
    Model* model2 = nullptr;
    Model* currentModel = nullptr;
    Sprite* sprite = nullptr;
    Sprite* start = nullptr;
    Sprite* button1 = nullptr;  // 四角のスプライト
    Sprite* button2 = nullptr;  // 四角のスプライト
    RECT leftRect;
    RECT rightRect;
};