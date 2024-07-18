#pragma once

#include "Scene.h"
#include "Graphics/Sprite.h"
#include "Graphics/Model.h"
#include <DirectXMath.h>

//// �V�[���I���N���X
class SceneSelect : public Scene
{
public:
    SceneSelect() {}
    ~SceneSelect() override {}

    // ������
    void Initialize() override;

    // �I����
    void Finalize() override;

    // �X�V����
    void Update(float elapsedTime) override;

    // �`�揈��
    void Render() override;

    // ���̃����o�֐���ϐ�
    //bool HitTest(int x, int y); // �N���b�N����̂��߂̊֐���ǉ�

private:
    // ���[�h�i2D���ӏ����A3D���f��1�A3D���f��2�j
    enum Mode
    {
        Notice2D,
        Model3D_1,
        Model3D_2
    };

    DirectX::XMFLOAT3     position = { 0,-1,0 };
    DirectX::XMFLOAT3     angle = { 0,135,0 };
    DirectX::XMFLOAT3     scale = { 1,1,1 };
    //XMFLOAT4X4���g�����߂�<DirectXMath.h>���K�v
    DirectX::XMFLOAT4X4   transform =
    {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };

    void HandleClick(int x, int y);
public:
    Mode mode = Notice2D;
    Model* model1 = nullptr;
    Model* model2 = nullptr;
    Model* currentModel = nullptr;
    Sprite* sprite = nullptr;
    Sprite* start = nullptr;
    Sprite* button1 = nullptr;  // �l�p�̃X�v���C�g
    Sprite* button2 = nullptr;  // �l�p�̃X�v���C�g
    RECT leftRect;
    RECT rightRect;
};