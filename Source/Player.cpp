#include <imgui.h>
#include "Player.h"
#include "Input/Input.h"
#include "Camera.h"
#include "Graphics/Graphics.h"
#include "EnemyManager.h"
#include "Collision.h"
#include "ProjectileStraight.h"
#include "ProjectileHoming.h"

//コンストラクタ
Player::Player() {
    model = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");

    //モデルが大きいのでスケーリング
    scale.x = scale.y = scale.z = 0.01f;

    //ヒットエフェクト読み込み
    //hitEffect = new Effect("Data/Effect/Hit.efk");
}

//デストラクタ
Player::~Player() {

    //delete hitEffect;
    delete model;
}

// 更新処理
void Player::Update(float elapsedTime)
{
    //速力処理更新
    UpdateVelocity(elapsedTime);

    //オブジェクト行列を更新
    UpdateTransform();
    //モデル行列更新
    model->UpdateTransform(transform);

}


//移動入力処理
void Player::InputMove(float elapsedTime) {
    //進行ベクトル取得
    DirectX::XMFLOAT3 moveVec = GetMoveVec();


    //旋回処理
    Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);
}



//描画処理
void Player::Render(ID3D11DeviceContext* dc, Shader* shader) {
    shader->Draw(dc, model);

    
}


//スティック入力値から移動ベクトルを取得
DirectX::XMFLOAT3 Player::GetMoveVec() const {
    //入力情報を取得
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisLX();
    float ay = gamePad.GetAxisLY();

    //カメラ方向とスティックの入力値によって進行方向を計算する
    Camera& camera = Camera::Instance();
    const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
    const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

    //移動ベクトルはXZ平面に水平なベクトルになるようにする

    //カメラ右方向ベクトルをXZ単位ベクトルに変換
    float cameraRightX = cameraRight.x;
    float cameraRightZ = cameraRight.z;
    float cameraRightLength = sqrtf(cameraRightX * cameraRightX +
        cameraRightZ * cameraRightZ);
    if (cameraRightLength > 0.0f) {
        //単位ベクトル化
        cameraRightX /= cameraRightLength;
        cameraRightZ /= cameraRightLength;
    }

    //カメラ前方向ベクトルをXZ単位ベクトルに変換
    float cameraFrontX = cameraFront.x;
    float cameraFrontZ = cameraFront.z;
    float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX +
        cameraFrontZ * cameraFrontZ);

    if (cameraFrontLength > 0.0f) {
        //単位ベクトル化
        cameraFrontX /= cameraFrontLength;
        cameraFrontZ /= cameraFrontLength;
    }

    //ステック水平入力値をカメラ右方向に反映し
    //ステック垂直入力値をカメラ前方向に反映し
    //進行ベクトルを入力する
    DirectX::XMFLOAT3 vec;
    vec.x = (cameraRightX * ax) + (cameraFrontX * ay);
    vec.z = (cameraRightZ * ax) + (cameraFrontZ * ay);

    //Y軸方向には移動しない
    vec.y = 0.0f;

    return vec;

}
