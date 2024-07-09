#pragma once

#include "Graphics/Model.h"
#include "Stage.h"

//�ړ����X�e�[�W
class StageMoveFloor :public Stage {
public:
    StageMoveFloor();
    ~StageMoveFloor();

    //�X�V����
    void Update(float elapsedTime) override;

    //�`�揈��
    void Render(ID3D11DeviceContext* dc, Shader* shader) override;

    //���C�L���X�g
    bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)override;

    //�X�^�[�g�ʒu�ݒ�
    void SetStartPoint(const DirectX::XMFLOAT3& start) { this->start = start; }

    //�S�[���ʒu�ݒ�
    void SetGoalPoint(const DirectX::XMFLOAT3& goal) { this->goal = goal; }

    //�g���N�ݒ�
    void SetTorque(const DirectX::XMFLOAT3& torque) { this->torque = torque; }

private:
    //�s��X�V����
    void UpdateTransform();

private:
    Model* model = nullptr;
    DirectX::XMFLOAT3 position = { 0,0,0 };
    DirectX::XMFLOAT3 angle = { 0,0,0 };
    DirectX::XMFLOAT3 scale = { 1,1,1 };
    //DirectX::XMFLOAT3 scale = { 0.3f,0.3f,0.3f };
    DirectX::XMFLOAT4X4 transform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
    DirectX::XMFLOAT4X4 oldTransform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };

    DirectX::XMFLOAT3 torque = { 0,0,0 };
    DirectX::XMFLOAT3 start = { 0,0,0 };
    DirectX::XMFLOAT3 goal = { 0,0,0 };

    float moveSpeed = 2.0f;
    float moveRate = 0.0f;
};
