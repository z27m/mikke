#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Character.h"
#include "ProjectileManager.h"
#include "Effect.h"

//プレイヤー
class Player : public Character {
public:
    Player();
    ~Player() override;

    //更新処理
    void Update(float elapsedTime);

    //描画処理
    void Render(ID3D11DeviceContext* dc, Shader* shader);


private:
    //スティック入力値から移動ベクトルを取得
    DirectX::XMFLOAT3 GetMoveVec() const;


    //移動入力処理
    void InputMove(float elapsedTime);


 

private:
    Model* model = nullptr;
    float moveSpeed = 50.0f;
    float turnSpeed = DirectX::XMConvertToRadians(720);


    ProjectileManager projectileManager;

    Effect* hitEffect = nullptr;
};
