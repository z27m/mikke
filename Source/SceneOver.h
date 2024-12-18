#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"

//タイトルシーン
class SceneOver :public Scene {
public:
    SceneOver() {}
    ~SceneOver() override {}

    //初期化
    void Initialize() override;

    //終了化
    void Finalize() override;

    //更新処理
    void Update(float elapsedTime) override;

    //描画処理
    void Render() override;

private:
    Sprite* sprite = nullptr;
};
