#pragma once

#include "Graphics/Model.h"
#include "Stage.h"



//メインステージ
class StageMain2 :public Stage {
public:
    StageMain2();
    ~StageMain2() override;

    //行列更新処理
    void UpdateTransform();

    //更新処理
    void Update(float elapsedTime) override;

    //描画処理
    void Render(ID3D11DeviceContext* dc, Shader* shader) override;

    //レイキャスト
    bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit) override;

    const DirectX::XMFLOAT3& GetPosition() const { return position; }


private:
    Model* model = nullptr;
    DirectX::XMFLOAT3 position = { 0,40,0 };
    DirectX::XMFLOAT3 angle = { 0,0,0 };
    DirectX::XMFLOAT3 scale = { 1,1,1 };
    DirectX::XMFLOAT4X4 transform = {
         1,0,0,0,
         0,1,0,0,
         0,0,1,0,
         0,0,0,1
    };


};