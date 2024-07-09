#include "Enemy.h"
#include "Graphics/Graphics.h"
#include "EnemyManager.h"



//�f�o�b�O�v���~�e�B�u�`��
void Enemy::DrawDebugPrimitive() {
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

    //�Փ˔���p�̃f�o�b�O����`��
    //debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));

    //�Փ˔���p�̃f�o�b�O�~����`��
    debugRenderer->DrawCylinder(position, radius, height,DirectX::XMFLOAT4(0, 0, 0, 1));
}

//�������g��j��
void Enemy::Destroy() {
    //�G�}�l�[�W���[�̍폜�Ɏ������g�̃A�h���X��n��
    EnemyManager::Instance().Remove(this);
}

