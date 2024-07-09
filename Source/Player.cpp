#include <imgui.h>
#include "Player.h"
#include "Input/Input.h"
#include "Camera.h"
#include "Graphics/Graphics.h"
#include "EnemyManager.h"
#include "Collision.h"
#include "ProjectileStraight.h"
#include "ProjectileHoming.h"

//�R���X�g���N�^
Player::Player() {
    model = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");

    //���f�����傫���̂ŃX�P�[�����O
    scale.x = scale.y = scale.z = 0.01f;

    //�q�b�g�G�t�F�N�g�ǂݍ���
    //hitEffect = new Effect("Data/Effect/Hit.efk");
}

//�f�X�g���N�^
Player::~Player() {

    //delete hitEffect;
    delete model;
}

// �X�V����
void Player::Update(float elapsedTime)
{
    //���͏����X�V
    UpdateVelocity(elapsedTime);

    //�I�u�W�F�N�g�s����X�V
    UpdateTransform();
    //���f���s��X�V
    model->UpdateTransform(transform);

}


//�ړ����͏���
void Player::InputMove(float elapsedTime) {
    //�i�s�x�N�g���擾
    DirectX::XMFLOAT3 moveVec = GetMoveVec();


    //���񏈗�
    Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);
}



//�`�揈��
void Player::Render(ID3D11DeviceContext* dc, Shader* shader) {
    shader->Draw(dc, model);

    
}


//�X�e�B�b�N���͒l����ړ��x�N�g�����擾
DirectX::XMFLOAT3 Player::GetMoveVec() const {
    //���͏����擾
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisLX();
    float ay = gamePad.GetAxisLY();

    //�J���������ƃX�e�B�b�N�̓��͒l�ɂ���Đi�s�������v�Z����
    Camera& camera = Camera::Instance();
    const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
    const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

    //�ړ��x�N�g����XZ���ʂɐ����ȃx�N�g���ɂȂ�悤�ɂ���

    //�J�����E�����x�N�g����XZ�P�ʃx�N�g���ɕϊ�
    float cameraRightX = cameraRight.x;
    float cameraRightZ = cameraRight.z;
    float cameraRightLength = sqrtf(cameraRightX * cameraRightX +
        cameraRightZ * cameraRightZ);
    if (cameraRightLength > 0.0f) {
        //�P�ʃx�N�g����
        cameraRightX /= cameraRightLength;
        cameraRightZ /= cameraRightLength;
    }

    //�J�����O�����x�N�g����XZ�P�ʃx�N�g���ɕϊ�
    float cameraFrontX = cameraFront.x;
    float cameraFrontZ = cameraFront.z;
    float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX +
        cameraFrontZ * cameraFrontZ);

    if (cameraFrontLength > 0.0f) {
        //�P�ʃx�N�g����
        cameraFrontX /= cameraFrontLength;
        cameraFrontZ /= cameraFrontLength;
    }

    //�X�e�b�N�������͒l���J�����E�����ɔ��f��
    //�X�e�b�N�������͒l���J�����O�����ɔ��f��
    //�i�s�x�N�g������͂���
    DirectX::XMFLOAT3 vec;
    vec.x = (cameraRightX * ax) + (cameraFrontX * ay);
    vec.z = (cameraRightZ * ax) + (cameraFrontZ * ay);

    //Y�������ɂ͈ړ����Ȃ�
    vec.y = 0.0f;

    return vec;

}
