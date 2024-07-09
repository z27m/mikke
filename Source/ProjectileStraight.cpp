#include "ProjectileStraight.h"
#include <Collision.h>
#include <StageManager.h>
#include <Character.h>


//コンストラクタ
ProjectileStraight::ProjectileStraight(ProjectileManager* manager):Projectile(manager)
{
    model = new Model("Data/Model/Sword/Sword.mdl");

    //表示サイズを調整
    scale.x = scale.y = scale.z = 3.0f;
}

//デストラクタ
ProjectileStraight::~ProjectileStraight()
{
    delete model;
}

//更新処理
void ProjectileStraight::Update(float elapsedTime)
{
    //寿命処理
    lifeTimer -= elapsedTime;
    if (lifeTimer <= 0) {
        Destroy();
    }


    //移動
    float speed = this->speed * elapsedTime;

#if false
    //位置+=前方向*高さ
    position.x += direction.x * speed;
    position.y += direction.y * speed;
    position.z += direction.z * speed;
#endif

    float mx = direction.x * speed;
    float my = direction.y * speed;
    float mz = direction.z * speed;

    //反射の処理
    {
        //レイの開始位置と終点位置
        DirectX::XMFLOAT3 start = { position.x, position.y, position.z };
        DirectX::XMFLOAT3 end = { position.x + mx, position.y, position.z + mz };

        //レイキャストによる壁の判定
        HitResult hit;
        if (StageManager::Instance().RayCast(start, end, hit)) {
            //壁までのベクトル
            DirectX::XMVECTOR Start = DirectX::XMLoadFloat3(&hit.position);   //壁の衝突位置
            DirectX::XMVECTOR End = DirectX::XMLoadFloat3(&end);              //レイの終点位置
            DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(End, Start);

            //壁の法線ベクトル
            DirectX::XMVECTOR Normal = DirectX::XMLoadFloat3(&hit.normal);

            //壁の衝突位置までのベクトルを法線に射影
            DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(Vec, Normal);
            float dot = DirectX::XMVectorGetX(Dot);   //射影の単一の値

            //壁の法線ベクトルをdotの２倍分スケーリングし（XMVectorScale）
            DirectX::XMVECTOR CollectPosition = DirectX::XMVectorScale(Normal, 2.0f * dot);
            //Endの位置からCollectPosition分のベクトルを足す
            DirectX::XMVECTOR ReflectPosition = DirectX::XMVectorSubtract(End, CollectPosition);

            //ReflectPosition引くhit.positionで反射ベクトルを計算
            DirectX::XMVECTOR ReflectVec = DirectX::XMVectorSubtract(ReflectPosition, Start);
            //反射ベクトルを正規化
            ReflectVec = DirectX::XMVector3Normalize(ReflectVec);

            //floatに変換
            DirectX::XMFLOAT3 reflectVec;
            DirectX::XMStoreFloat3(&reflectVec, ReflectVec);

            //位置のxとzの成分をhit.positionに上書き
            position.x = hit.position.x;
            position.z = hit.position.z;
           
            //directionのxとzの成分を上書き
            direction.x = reflectVec.x * speed;
            direction.z = reflectVec.z * speed;

        }
        else {
            position.x += mx;
            position.z += mz;
        }
    }

    
    position.y += my;
    

    //オブジェクト行列を更新
    UpdateTransform();

    //モデル行列更新
    model->UpdateTransform(transform);
}

//描画処理
void ProjectileStraight::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    shader->Draw(dc, model);
}

//発射
void ProjectileStraight::Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position)
{
    this->direction = direction;
    this->position = position;
}


