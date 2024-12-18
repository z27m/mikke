#include "CameraController.h"
#include "Camera.h"
#include "Input/Input.h"

//更新処理
void CameraController::Update(float elapsedTime) {
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisLX();
    float ay = gamePad.GetAxisLY();

    //カメラの回転速度
    float speed = rollSpeed * elapsedTime;

    //スティックの入力値に合わせてX軸とY軸を回転
    //angle.x += ay * speed;
    angle.y += ax * speed;



    ////カメラ回転値を回転行列に変換
    DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);


    //回転行列から前方向ベクトルを取り出す
    DirectX::XMVECTOR Front = Transform.r[2];
    DirectX::XMFLOAT3 front;
    DirectX::XMStoreFloat3(&front, Front);

    //マウスホイールで拡大縮小
    float zDelta = Input::Instance().GetMouse().GetWheel() * 0.01f;

    range = range + -zDelta;

    if (range > 60) {
        range = 60;
    }
    if (range < 20) {
        range = 20;
    }

    angle.x = 40.0f;


    //注視点から後ろベクトル方向に一定距離離れたカメラ視点を求める
    DirectX::XMFLOAT3 eye;
    eye.x = target.x - front.x * range;
    eye.y = target.y - front.y * range;
    eye.z = target.z - front.z * range;

    //カメラの視点と注視点を設定
    Camera::Instance().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
    

}