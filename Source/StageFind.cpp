#include "StageFind.h"


//コンストラクタ
StageFind::StageFind(const char* filename) {

    //m_findObjectType = FindObjectType::Find;


    //ステージモデルを読み込み
    model = new Model(filename);
    scale.x = scale.y = scale.z = 0.5f;
}

//行列更新処理
void StageFind::UpdateTransform() {

    //スケール行列を作成
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

    //回転行列を作成
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


//更新処理
void StageFind::Update(float elapsedTime) {

    UpdateTransform();

    model->UpdateTransform(transform);
}

StageFind::~StageFind() {
    //ステージモデルを破棄
    delete model;
}

//描画処理
void StageFind::Render(ID3D11DeviceContext* dc, Shader* shader) {
    //シェーダーにモデルを描画してもらう
    shader->Draw(dc, model);
}

//レイキャスト
bool StageFind::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
    if (Collision::IntersectRayVsModel(start, end, model, hit)) {

        hit.materialIndex = m_findObjectType;

        hit.findIndex = m_index;

        return true;
    }
    return false;
}