#include "Character.h"
#include "StageManager.h"
#include "Mathf.h"

//行列更新処理
void Character::UpdateTransform() {
    //スケール行列を作成
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

    //回転行列を作成
    //DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

    DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(angle.x);
    DirectX::XMMATRIX Y = DirectX::XMMatrixRotationY(angle.y);
    DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(angle.z);
    DirectX::XMMATRIX R = Y * X * Z;


    //位置行列を作成
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

    //3つの行列を組み合わせ、ワールド行列を作成
    DirectX::XMMATRIX W = S * R * T;

    //計算したワールド行列を取り出す
    DirectX::XMStoreFloat4x4(&transform, W);
}

//移動処理
void Character::Move(float vx, float vz, float speed) {
    //speed *= elapsedTime;
    //position.x += vx * speed;
    //position.z += vz * speed;

    //移動方向ベクトルを設定
    moveVecX = vx;
    moveVecZ = vz;

    //最大速度設定
    maxMoveSpeed = speed;
}

//旋回処理
void Character::Turn(float elapsedTime, float vx, float vz, float speed) {
    speed *= elapsedTime;

    //進行ベクトルがゼロベクトルの場合は処理する必要なし
    float length = sqrtf(vx * vx + vz * vz);
    if (length < 0.001f)return;
    //進行ベクトルを単位ベクトル化
    vx /= length;
    vz /= length;

    //自身の回転値から前方向を求める
    float frontX = sinf(angle.y);    //float frontX = transform._31 
    float frontZ = cosf(angle.y);

    //回転角を求めるため、２つの単位ベクトルの内積を計算する
    float dot = (frontX * vx) + (frontZ * vz);

    //内積値は-1.0~1.0で表現されており、２つの単位ベクトルの角度が
    //小さいほど1.0に近づくという性質を利用して回転速度を調整する
    float rot = 1.0f - dot;
    if (rot > speed)rot = speed;

    //左右判定を行うために２つの単位ベクトルの外積を計算する
    float cross = (frontZ * vx) - (frontX * vz);

    //2Dの外積値が正の場合か負の場合によって左右判定が行える
    //左右判定を行うことによって左回転を選択する
    if (cross < 0.0f) {
        angle.y -= rot;
    }
    else {
        angle.y += rot;
    }

}

//速力処理更新
void Character::UpdateVelocity(float elapsedTime) {
    //経過フレーム
    float elapsedFrame = 60.0f * elapsedTime;

    //垂直速力更新処理
    UpdateVerticalVelocity(elapsedFrame);



    //水中速力更新処理
    UpdateHorizontalVelocity(elapsedFrame);

    //垂直移動更新処理
    UpdateVerticalMove(elapsedTime);

    //水中移動更新処理
    UpdateHorizontalMove(elapsedTime);
}

//垂直速力更新処理
void Character::UpdateVerticalVelocity(float elapsedFrame) {
    //重力処理
    //velocity.y += gravity * elapsedFrame; 
}

//垂直移動更新処理
void Character::UpdateVerticalMove(float elapsedTime) {
   //垂直方向の移動量
    float my = velocity.y * elapsedTime;

    slopeRate = 0.0f;

    //キャラクターのY軸方向となる法線ベクトル
    DirectX::XMFLOAT3 normal = { 0,1,0 };

    //落下中
    if (my < 0.0f) {
        //レイの開始位置は足元より少し上
        DirectX::XMFLOAT3 start = { position.x,position.y + stepOffset,position.z };
    
        //レイの終点位置は移動後の位置
        DirectX::XMFLOAT3 end = { position.x,position.y + my-0.1f,position.z };

        //レイキャストによる地面判定
        HitResult hit;
        if (StageManager::Instance().RayCast(start, end, hit)) {
            //法線ベクトル取得
            normal = hit.normal;

            //地面に設置している
            position.y = hit.position.y;

            //傾斜率の計算（ポリゴンがどれぐらい斜めか）
            //float normalLengthXZ = sqrtf(hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z);
            //slopeRate = 1.0f - (hit.normal.y / (normalLengthXZ + hit.normal.y));

            ////着地した
            //if (!isGround) {
            //    OnLanding();
            //}
            //isGround = true;
            //velocity.y = 0.0f;

        }
        else {
            //空中に浮いている
            position.y += my;
            isGround = false;
        }
    
    
    }
    //上昇中
    else if (my > 0.0f) {
        position.y += my;
        isGround = false;
    }

    //地面の向きに沿うようにXZ軸回転
    {
        //Y軸が法線ベクトル方向に向くオイラー角回転を算出する
        float ax = atan2f(normal.z, normal.y);
        float az = -atan2f(normal.x, normal.y);
        //線形補完で滑らかに回転する
        angle.x = Mathf::Lerp(angle.x, ax, 0.2f);
        angle.z = Mathf::Lerp(angle.z, az, 0.2f);

    }


}

//衝撃を与える
void Character::AddImpulse(const DirectX::XMFLOAT3& impulse) {
    //速力に力を加える
    velocity.x += impulse.x;
    velocity.y += impulse.y;
    velocity.z += impulse.z;
}

//水平速力更新処理
void Character::UpdateHorizontalVelocity(float elapsedFrame) {
    //XZ平面の速力を減速する
    float length = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
    if (length > 0.0f) {
        //摩擦力
        float friction = this->friction * elapsedFrame;

        //空中にいるときは摩擦力を減らす
        friction += friction * airControl;

        //摩擦による横方向の減速処理
        if (length > friction) {

            //速力を単位ベクトル化
            float vx = velocity.x / length;
            float vz = velocity.z / length;
            //単位ベクトル化した速力を摩擦力分スケーリングした値を速力から引く
            velocity.x -= vx * friction;
            velocity.z -= vz * friction;

        }//横方向の速力が摩擦力以下になったので速力を無効化
        else {
            velocity.x = 0.0f;
            velocity.z = 0.0f;
        }
    }

    //XZ平面の速力を加速する
    if (length <= maxMoveSpeed) {
        //移動ベクトルがゼロベクトルでないなら加速する
        float moveVecLength = sqrtf(moveVecX * moveVecX + moveVecZ * moveVecZ);
        if (moveVecLength > 0.0f) {
            //加速力
            float acceleration = this->acceleration * elapsedFrame;
            //移動ベクトルによる加速処理
            velocity.x += moveVecX * acceleration;
            velocity.z += moveVecZ * acceleration;

            //空中にいるときは加速力を減らす
            acceleration += acceleration * airControl;

            //最大速度制限
            float length = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
            if (length > maxMoveSpeed) {
                //速度ベクトルを正規化
                float vx = velocity.x / length;
                float vz = velocity.z / length;
                //最大速さ分スケーリングした値を速度ベクトルに代入
                velocity.x = vx * maxMoveSpeed;
                velocity.z = vz * maxMoveSpeed;
            }

            //下り坂でガタガタしないようにする
            /*if (isGround && slopeRate > 0.0f) {
                velocity.y -= length * slopeRate * elapsedFrame;
            }*/


        }
    }
    //移動ベクトルをリセット
    moveVecX = 0.0f;
    moveVecZ = 0.0f;
}

//水中移動更新処理
void Character::UpdateHorizontalMove(float elapsedTime) {
    //移動処理
    //position.x += velocity.x * elapsedTime;
    //position.z += velocity.z * elapsedTime;

    //水平速力量計算
    float velocityLengthXZ = sqrt(velocity.x * velocity.x + velocity.z * velocity.z);
    if (velocityLengthXZ > 0.0f) {
        //水平移動値
        float mx = velocity.x * elapsedTime;
        float mz = velocity.z * elapsedTime;

        //レイの開始位置と終点位置
        DirectX::XMFLOAT3 start = { position.x,position.y + stepOffset,position.z };
        DirectX::XMFLOAT3 end = { position.x + mx, position.y + stepOffset, position.z + mz };

        //レイのキャストによる壁判定
        HitResult hit;
        if (StageManager::Instance().RayCast(start, end, hit)) {
            //壁までのベクトル
            DirectX::XMVECTOR Start = DirectX::XMLoadFloat3(&start);
            DirectX::XMVECTOR End = DirectX::XMLoadFloat3(&end);
            DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Start, End);

            //壁の法線
            DirectX::XMVECTOR Normal = DirectX::XMLoadFloat3(&hit.normal);

            //入射ベクトルを法線に射影
            DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(Vec, Normal);

            //補正位置の計算
            //法線ベクト方向にDot分スケーリングする
            DirectX::XMVECTOR CollectPosition = DirectX::XMVectorMultiply(Normal, Dot);
            //CollectPositionにEndの位置を足した位置が最終的な位置
            DirectX::XMFLOAT3 collectPosition;
            DirectX::XMStoreFloat3(&collectPosition, DirectX::XMVectorAdd(End, CollectPosition));

            //hit.positionを開始位置とし、collectPositionを終点位置としてさらにレイキャスト
            HitResult hit2;
            
            if (StageManager::Instance().RayCast(hit.position, collectPosition, hit2)) {
                //当たってなかったら

                //xとzの成分のみ反映
                position.x = collectPosition.x;
                position.z = collectPosition.z;
            }
            else {
                //当たってたらhit2.positionを最終的な位置として反映
                position.x = hit2.position.x;
                position.z = hit2.position.z;
            }
        

        }
        else {
            //移動
            position.x += mx;
            position.z += mz;
        }
    }
}

