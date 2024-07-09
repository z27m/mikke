#pragma once

#include "Graphics/Shader.h"
#include "Collision.h"

// �T���ׂ��I�u�W�F�N�g�̃^�C�v
enum FindObjectType {

    // �ʏ�̂Ȃ�ł��Ȃ��I�u�W�F�N�g�i�X�e�[�W�j
    None,

    // �T���o�����I�u�W�F�N�g
    Find,
};

//�X�e�[�W
class Stage {
public:
    Stage() {}
    virtual ~Stage() {}

    //�X�V����
    virtual void Update(float elapsedTime) = 0;

    //�`�揈��
    virtual void Render(ID3D11DeviceContext* dc, Shader* shader) = 0;

    //���C�L���X�g
    virtual bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit) = 0;

    void SetFindObjectType(FindObjectType type) { m_findObjectType = type; }

    FindObjectType GetFindObjectType() { return m_findObjectType; }

protected:
    FindObjectType m_findObjectType;
};
