#include "CameraController.h"
#include "Camera.h"
#include "Input/Input.h"

//�X�V����
void CameraController::Update(float elapsedTime) {
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisLX();
    float ay = gamePad.GetAxisLY();

    //�J�����̉�]���x
    float speed = rollSpeed * elapsedTime;

    //�X�e�B�b�N�̓��͒l�ɍ��킹��X����Y������]
    //angle.x += ay * speed;
    angle.y += ax * speed;



    ////�J������]�l����]�s��ɕϊ�
    DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);


    //��]�s�񂩂�O�����x�N�g�������o��
    DirectX::XMVECTOR Front = Transform.r[2];
    DirectX::XMFLOAT3 front;
    DirectX::XMStoreFloat3(&front, Front);

    //�}�E�X�z�C�[���Ŋg��k��
    float zDelta = Input::Instance().GetMouse().GetWheel() * 0.01f;

    range = range + -zDelta;

    if (range > 50) {
        range = 50;
    }
    if (range < 10) {
        range = 10;
    }

    angle.x = 40.0f;


    //�����_������x�N�g�������Ɉ�苗�����ꂽ�J�������_�����߂�
    DirectX::XMFLOAT3 eye;
    eye.x = target.x - front.x * range;
    eye.y = target.y - front.y * range;
    eye.z = target.z - front.z * range;

    //�J�����̎��_�ƒ����_��ݒ�
    Camera::Instance().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
    

}