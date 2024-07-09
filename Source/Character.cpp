#include "Character.h"
#include "StageManager.h"
#include "Mathf.h"

//�s��X�V����
void Character::UpdateTransform() {
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

//�ړ�����
void Character::Move(float vx, float vz, float speed) {
    //speed *= elapsedTime;
    //position.x += vx * speed;
    //position.z += vz * speed;

    //�ړ������x�N�g����ݒ�
    moveVecX = vx;
    moveVecZ = vz;

    //�ő呬�x�ݒ�
    maxMoveSpeed = speed;
}

//���񏈗�
void Character::Turn(float elapsedTime, float vx, float vz, float speed) {
    speed *= elapsedTime;

    //�i�s�x�N�g�����[���x�N�g���̏ꍇ�͏�������K�v�Ȃ�
    float length = sqrtf(vx * vx + vz * vz);
    if (length < 0.001f)return;
    //�i�s�x�N�g����P�ʃx�N�g����
    vx /= length;
    vz /= length;

    //���g�̉�]�l����O���������߂�
    float frontX = sinf(angle.y);    //float frontX = transform._31 
    float frontZ = cosf(angle.y);

    //��]�p�����߂邽�߁A�Q�̒P�ʃx�N�g���̓��ς��v�Z����
    float dot = (frontX * vx) + (frontZ * vz);

    //���ϒl��-1.0~1.0�ŕ\������Ă���A�Q�̒P�ʃx�N�g���̊p�x��
    //�������ق�1.0�ɋ߂Â��Ƃ��������𗘗p���ĉ�]���x�𒲐�����
    float rot = 1.0f - dot;
    if (rot > speed)rot = speed;

    //���E������s�����߂ɂQ�̒P�ʃx�N�g���̊O�ς��v�Z����
    float cross = (frontZ * vx) - (frontX * vz);

    //2D�̊O�ϒl�����̏ꍇ�����̏ꍇ�ɂ���č��E���肪�s����
    //���E������s�����Ƃɂ���č���]��I������
    if (cross < 0.0f) {
        angle.y -= rot;
    }
    else {
        angle.y += rot;
    }

}

//���͏����X�V
void Character::UpdateVelocity(float elapsedTime) {
    //�o�߃t���[��
    float elapsedFrame = 60.0f * elapsedTime;

    //�������͍X�V����
    UpdateVerticalVelocity(elapsedFrame);



    //�������͍X�V����
    UpdateHorizontalVelocity(elapsedFrame);

    //�����ړ��X�V����
    UpdateVerticalMove(elapsedTime);

    //�����ړ��X�V����
    UpdateHorizontalMove(elapsedTime);
}

//�������͍X�V����
void Character::UpdateVerticalVelocity(float elapsedFrame) {
    //�d�͏���
    //velocity.y += gravity * elapsedFrame; 
}

//�����ړ��X�V����
void Character::UpdateVerticalMove(float elapsedTime) {
   //���������̈ړ���
    float my = velocity.y * elapsedTime;

    slopeRate = 0.0f;

    //�L�����N�^�[��Y�������ƂȂ�@���x�N�g��
    DirectX::XMFLOAT3 normal = { 0,1,0 };

    //������
    if (my < 0.0f) {
        //���C�̊J�n�ʒu�͑�����菭����
        DirectX::XMFLOAT3 start = { position.x,position.y + stepOffset,position.z };
    
        //���C�̏I�_�ʒu�͈ړ���̈ʒu
        DirectX::XMFLOAT3 end = { position.x,position.y + my-0.1f,position.z };

        //���C�L���X�g�ɂ��n�ʔ���
        HitResult hit;
        if (StageManager::Instance().RayCast(start, end, hit)) {
            //�@���x�N�g���擾
            normal = hit.normal;

            //�n�ʂɐݒu���Ă���
            position.y = hit.position.y;

            //�X�Η��̌v�Z�i�|���S�����ǂꂮ�炢�΂߂��j
            //float normalLengthXZ = sqrtf(hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z);
            //slopeRate = 1.0f - (hit.normal.y / (normalLengthXZ + hit.normal.y));

            ////���n����
            //if (!isGround) {
            //    OnLanding();
            //}
            //isGround = true;
            //velocity.y = 0.0f;

        }
        else {
            //�󒆂ɕ����Ă���
            position.y += my;
            isGround = false;
        }
    
    
    }
    //�㏸��
    else if (my > 0.0f) {
        position.y += my;
        isGround = false;
    }

    //�n�ʂ̌����ɉ����悤��XZ����]
    {
        //Y�����@���x�N�g�������Ɍ����I�C���[�p��]���Z�o����
        float ax = atan2f(normal.z, normal.y);
        float az = -atan2f(normal.x, normal.y);
        //���`�⊮�Ŋ��炩�ɉ�]����
        angle.x = Mathf::Lerp(angle.x, ax, 0.2f);
        angle.z = Mathf::Lerp(angle.z, az, 0.2f);

    }


}

//�Ռ���^����
void Character::AddImpulse(const DirectX::XMFLOAT3& impulse) {
    //���͂ɗ͂�������
    velocity.x += impulse.x;
    velocity.y += impulse.y;
    velocity.z += impulse.z;
}

//�������͍X�V����
void Character::UpdateHorizontalVelocity(float elapsedFrame) {
    //XZ���ʂ̑��͂���������
    float length = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
    if (length > 0.0f) {
        //���C��
        float friction = this->friction * elapsedFrame;

        //�󒆂ɂ���Ƃ��͖��C�͂����炷
        friction += friction * airControl;

        //���C�ɂ�鉡�����̌�������
        if (length > friction) {

            //���͂�P�ʃx�N�g����
            float vx = velocity.x / length;
            float vz = velocity.z / length;
            //�P�ʃx�N�g�����������͂𖀎C�͕��X�P�[�����O�����l�𑬗͂������
            velocity.x -= vx * friction;
            velocity.z -= vz * friction;

        }//�������̑��͂����C�͈ȉ��ɂȂ����̂ő��͂𖳌���
        else {
            velocity.x = 0.0f;
            velocity.z = 0.0f;
        }
    }

    //XZ���ʂ̑��͂���������
    if (length <= maxMoveSpeed) {
        //�ړ��x�N�g�����[���x�N�g���łȂ��Ȃ��������
        float moveVecLength = sqrtf(moveVecX * moveVecX + moveVecZ * moveVecZ);
        if (moveVecLength > 0.0f) {
            //������
            float acceleration = this->acceleration * elapsedFrame;
            //�ړ��x�N�g���ɂ���������
            velocity.x += moveVecX * acceleration;
            velocity.z += moveVecZ * acceleration;

            //�󒆂ɂ���Ƃ��͉����͂����炷
            acceleration += acceleration * airControl;

            //�ő呬�x����
            float length = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
            if (length > maxMoveSpeed) {
                //���x�x�N�g���𐳋K��
                float vx = velocity.x / length;
                float vz = velocity.z / length;
                //�ő呬�����X�P�[�����O�����l�𑬓x�x�N�g���ɑ��
                velocity.x = vx * maxMoveSpeed;
                velocity.z = vz * maxMoveSpeed;
            }

            //�����ŃK�^�K�^���Ȃ��悤�ɂ���
            /*if (isGround && slopeRate > 0.0f) {
                velocity.y -= length * slopeRate * elapsedFrame;
            }*/


        }
    }
    //�ړ��x�N�g�������Z�b�g
    moveVecX = 0.0f;
    moveVecZ = 0.0f;
}

//�����ړ��X�V����
void Character::UpdateHorizontalMove(float elapsedTime) {
    //�ړ�����
    //position.x += velocity.x * elapsedTime;
    //position.z += velocity.z * elapsedTime;

    //�������͗ʌv�Z
    float velocityLengthXZ = sqrt(velocity.x * velocity.x + velocity.z * velocity.z);
    if (velocityLengthXZ > 0.0f) {
        //�����ړ��l
        float mx = velocity.x * elapsedTime;
        float mz = velocity.z * elapsedTime;

        //���C�̊J�n�ʒu�ƏI�_�ʒu
        DirectX::XMFLOAT3 start = { position.x,position.y + stepOffset,position.z };
        DirectX::XMFLOAT3 end = { position.x + mx, position.y + stepOffset, position.z + mz };

        //���C�̃L���X�g�ɂ��ǔ���
        HitResult hit;
        if (StageManager::Instance().RayCast(start, end, hit)) {
            //�ǂ܂ł̃x�N�g��
            DirectX::XMVECTOR Start = DirectX::XMLoadFloat3(&start);
            DirectX::XMVECTOR End = DirectX::XMLoadFloat3(&end);
            DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Start, End);

            //�ǂ̖@��
            DirectX::XMVECTOR Normal = DirectX::XMLoadFloat3(&hit.normal);

            //���˃x�N�g����@���Ɏˉe
            DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(Vec, Normal);

            //�␳�ʒu�̌v�Z
            //�@���x�N�g������Dot���X�P�[�����O����
            DirectX::XMVECTOR CollectPosition = DirectX::XMVectorMultiply(Normal, Dot);
            //CollectPosition��End�̈ʒu�𑫂����ʒu���ŏI�I�Ȉʒu
            DirectX::XMFLOAT3 collectPosition;
            DirectX::XMStoreFloat3(&collectPosition, DirectX::XMVectorAdd(End, CollectPosition));

            //hit.position���J�n�ʒu�Ƃ��AcollectPosition���I�_�ʒu�Ƃ��Ă���Ƀ��C�L���X�g
            HitResult hit2;
            
            if (StageManager::Instance().RayCast(hit.position, collectPosition, hit2)) {
                //�������ĂȂ�������

                //x��z�̐����̂ݔ��f
                position.x = collectPosition.x;
                position.z = collectPosition.z;
            }
            else {
                //�������Ă���hit2.position���ŏI�I�Ȉʒu�Ƃ��Ĕ��f
                position.x = hit2.position.x;
                position.z = hit2.position.z;
            }
        

        }
        else {
            //�ړ�
            position.x += mx;
            position.z += mz;
        }
    }
}

