#include <EnemyManager.h>
#include "Collision.h"



//�X�V����
void EnemyManager::Update(float elapsedTime) {
    for (Enemy* enemy : enemies) {
        enemy->Update(elapsedTime);
    }

    //�j������
    for (Enemy* enemy : removes) {
        
        std::vector<Enemy*>::iterator it =
            std::find(enemies.begin(),
                enemies.end(), enemy);

        if (it != enemies.end()) {
            enemies.erase(it);
        }

        //�e�ۂ̔j������
        delete enemy;
    }

    //�j�����X�g���N���A
    removes.clear();

    //�G���m�̏Փˏ���
    CollisionEnemyVsEnemies();

}

//�G�l�~�[���m�̏Փˏ���
void EnemyManager::CollisionEnemyVsEnemies() {
    //�G�̐����擾
    
    //�͔͉𓚂���
    size_t enemyCount = enemies.size();

    //�G�̐����񂷁@�i�J�E���^�[i�j
    for (int i = 0; i < GetEnemyCount(); ++i) {
        //�GA���擾
        Enemy* enemyA = enemies.at(i);
        //�G�̐��Ԃ�񂷁@�i�J�E���^�[���j
        for (int j = i+1; j < GetEnemyCount(); ++j) {
            //�G�a���擾
            Enemy* enemyB = enemies.at(j);
            //�����o����̈ʒu
            DirectX::XMFLOAT3 outPosition;
            //�Փˏ����@if��
            if (Collision::IntersectCylinderVsCylinder( //CylinderVsCylinder SphereVsSphere
                enemyA->GetPosition(), //�G�`�̈ʒu
                enemyA->GetRadius(),//�G�`�̔��a
                enemyA->GetHeight(),
                enemyB->GetPosition(),//�G�a�̈ʒu
                enemyB->GetRadius(),//�G�a�̔��a
                enemyB->GetHeight(),
                outPosition//�����o����̈ʒu
                )) 
             {
                //�G�a�ɉ����o����̈ʒu��ݒ�
                enemyB->SetPosition(outPosition);
             }
            
        }
    }
}

//�`�揈��
void EnemyManager :: Render(ID3D11DeviceContext* context, Shader* shader) {
    for (Enemy* enemy : enemies) {
        enemy->Render(context, shader);
    }
}



//�f�o�b�O�v���~�e�B�u�`��
void EnemyManager::DrawDebugPrimitive() {
    for (Enemy* enemy : enemies) {
        enemy->DrawDebugPrimitive();
    }
}

//�G�l�~�[�o�^
void EnemyManager::Register(Enemy* enemy) {
    enemies.emplace_back(enemy);
}

//�G�l�~�[�폜
void EnemyManager::Remove(Enemy* enemy) {
    //�j�����X�g�ɒǉ�
    removes.insert(enemy);
}


//�G�l�~�[�S�폜
void EnemyManager::Clear() {
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
}

