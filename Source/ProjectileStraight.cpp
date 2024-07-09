#include "ProjectileStraight.h"
#include <Collision.h>
#include <StageManager.h>
#include <Character.h>


//�R���X�g���N�^
ProjectileStraight::ProjectileStraight(ProjectileManager* manager):Projectile(manager)
{
    model = new Model("Data/Model/Sword/Sword.mdl");

    //�\���T�C�Y�𒲐�
    scale.x = scale.y = scale.z = 3.0f;
}

//�f�X�g���N�^
ProjectileStraight::~ProjectileStraight()
{
    delete model;
}

//�X�V����
void ProjectileStraight::Update(float elapsedTime)
{
    //��������
    lifeTimer -= elapsedTime;
    if (lifeTimer <= 0) {
        Destroy();
    }


    //�ړ�
    float speed = this->speed * elapsedTime;

#if false
    //�ʒu+=�O����*����
    position.x += direction.x * speed;
    position.y += direction.y * speed;
    position.z += direction.z * speed;
#endif

    float mx = direction.x * speed;
    float my = direction.y * speed;
    float mz = direction.z * speed;

    //���˂̏���
    {
        //���C�̊J�n�ʒu�ƏI�_�ʒu
        DirectX::XMFLOAT3 start = { position.x, position.y, position.z };
        DirectX::XMFLOAT3 end = { position.x + mx, position.y, position.z + mz };

        //���C�L���X�g�ɂ��ǂ̔���
        HitResult hit;
        if (StageManager::Instance().RayCast(start, end, hit)) {
            //�ǂ܂ł̃x�N�g��
            DirectX::XMVECTOR Start = DirectX::XMLoadFloat3(&hit.position);   //�ǂ̏Փˈʒu
            DirectX::XMVECTOR End = DirectX::XMLoadFloat3(&end);              //���C�̏I�_�ʒu
            DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(End, Start);

            //�ǂ̖@���x�N�g��
            DirectX::XMVECTOR Normal = DirectX::XMLoadFloat3(&hit.normal);

            //�ǂ̏Փˈʒu�܂ł̃x�N�g����@���Ɏˉe
            DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(Vec, Normal);
            float dot = DirectX::XMVectorGetX(Dot);   //�ˉe�̒P��̒l

            //�ǂ̖@���x�N�g����dot�̂Q�{���X�P�[�����O���iXMVectorScale�j
            DirectX::XMVECTOR CollectPosition = DirectX::XMVectorScale(Normal, 2.0f * dot);
            //End�̈ʒu����CollectPosition���̃x�N�g���𑫂�
            DirectX::XMVECTOR ReflectPosition = DirectX::XMVectorSubtract(End, CollectPosition);

            //ReflectPosition����hit.position�Ŕ��˃x�N�g�����v�Z
            DirectX::XMVECTOR ReflectVec = DirectX::XMVectorSubtract(ReflectPosition, Start);
            //���˃x�N�g���𐳋K��
            ReflectVec = DirectX::XMVector3Normalize(ReflectVec);

            //float�ɕϊ�
            DirectX::XMFLOAT3 reflectVec;
            DirectX::XMStoreFloat3(&reflectVec, ReflectVec);

            //�ʒu��x��z�̐�����hit.position�ɏ㏑��
            position.x = hit.position.x;
            position.z = hit.position.z;
           
            //direction��x��z�̐������㏑��
            direction.x = reflectVec.x * speed;
            direction.z = reflectVec.z * speed;

        }
        else {
            position.x += mx;
            position.z += mz;
        }
    }

    
    position.y += my;
    

    //�I�u�W�F�N�g�s����X�V
    UpdateTransform();

    //���f���s��X�V
    model->UpdateTransform(transform);
}

//�`�揈��
void ProjectileStraight::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    shader->Draw(dc, model);
}

//����
void ProjectileStraight::Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position)
{
    this->direction = direction;
    this->position = position;
}


