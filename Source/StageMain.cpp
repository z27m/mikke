#include "StageMain.h"


//コンストラクタ
StageMain::StageMain() {

    m_findObjectType = FindObjectType::None;

    //ステージモデルを読み込み
    //model = new Model("Data/Model/ExampleStage/ExampleStage.mdl");
    model = new Model("Data/Model/team/test_sea.mdl");
    scale.x = scale.y = scale.z = 0.2f;
}

//行列更新処理
void StageMain::UpdateTransform() {

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


//更新処理
void StageMain::Update(float elapsedTime) {
    
    UpdateTransform();

    model->UpdateTransform(transform);

   


}

StageMain::~StageMain() {
    //ステージモデルを破棄
    delete model;
}

//描画処理
void StageMain::Render(ID3D11DeviceContext* dc, Shader* shader) {
    //シェーダーにモデルを描画してもらう
    shader->Draw(dc, model);
}

//レイキャスト
bool StageMain::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
    if (Collision::IntersectRayVsModel(start, end, model, hit)) {
        
        hit.materialIndex = m_findObjectType;
        
        return true;
    }
    return false;
}

