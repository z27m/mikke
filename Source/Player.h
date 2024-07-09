#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Character.h"
#include "ProjectileManager.h"
#include "Effect.h"

//�v���C���[
class Player : public Character {
public:
    Player();
    ~Player() override;

    //�X�V����
    void Update(float elapsedTime);

    //�`�揈��
    void Render(ID3D11DeviceContext* dc, Shader* shader);


private:
    //�X�e�B�b�N���͒l����ړ��x�N�g�����擾
    DirectX::XMFLOAT3 GetMoveVec() const;


    //�ړ����͏���
    void InputMove(float elapsedTime);


 

private:
    Model* model = nullptr;
    float moveSpeed = 50.0f;
    float turnSpeed = DirectX::XMConvertToRadians(720);


    ProjectileManager projectileManager;

    Effect* hitEffect = nullptr;
};
