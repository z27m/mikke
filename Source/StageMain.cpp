#include "StageMain.h"


//�R���X�g���N�^
StageMain::StageMain() {

    m_findObjectType = FindObjectType::None;

    //�X�e�[�W���f����ǂݍ���
    //model = new Model("Data/Model/ExampleStage/ExampleStage.mdl");
    model = new Model("Data/Model/team/test_sea.mdl");
    scale.x = scale.y = scale.z = 0.2f;
}

//�s��X�V����
void StageMain::UpdateTransform() {

    //�X�P�[���s����쐬
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
    
    

    //��]�s����쐬
    //DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

    DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(angle.x);
    DirectX::XMMATRIX Y = DirectX::XMMatrixRotationY(angle.y);
    DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(angle.z);
    DirectX::XMMATRIX R = Y * X * Z;

    //�ʒu�s����쐬
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

    //3�̍s���g�ݍ��킹�A���[���h�s����쐬
    DirectX::XMMATRIX W = S * R * T;

    //�v�Z�������[���h�s������o��
    DirectX::XMStoreFloat4x4(&transform, W);
}


//�X�V����
void StageMain::Update(float elapsedTime) {
    
    UpdateTransform();

    model->UpdateTransform(transform);

   


}

StageMain::~StageMain() {
    //�X�e�[�W���f����j��
    delete model;
}

//�`�揈��
void StageMain::Render(ID3D11DeviceContext* dc, Shader* shader) {
    //�V�F�[�_�[�Ƀ��f����`�悵�Ă��炤
    shader->Draw(dc, model);
}

//���C�L���X�g
bool StageMain::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
    if (Collision::IntersectRayVsModel(start, end, model, hit)) {
        
        hit.materialIndex = m_findObjectType;
        
        return true;
    }
    return false;
}

