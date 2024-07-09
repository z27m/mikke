#include "StageManager.h"

//�X�V����
void StageManager::Update(float elapsedTime)
{
    for (Stage* stage : stages) {
        stage->Update(elapsedTime);
    }
}

//�`�揈��
void StageManager::Render(ID3D11DeviceContext* context, Shader* shader)
{
    for (Stage* stage : stages) {
        stage->Render(context, shader);
    }

}

//�X�e�[�W�o�^
void StageManager::Register(Stage* stage)
{
    stages.emplace_back(stage);

}

//�X�e�[�W�S�폜
void StageManager::Clear()
{
    for (Stage* stage : stages) {
        delete stage;
    }
    //�C�e���[�^�[���N���A�ɂ���
    stages.clear();
}

bool StageManager::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
    bool result = false;

    hit.distance = FLT_MAX;

    for (Stage* stage : stages) {
        HitResult tmp;
        if (stage->RayCast(start, end, tmp)) {
            if (hit.distance > tmp.distance) {
                hit = tmp;
                result = true;
            }
        }

    }


    return result;
}


