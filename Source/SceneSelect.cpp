#include "Graphics/Graphics.h"
#include "SceneSelect.h"
#include "Camera.h"
#include "Input/Input.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "SceneGame.h"
#include "SceneGame2.h"



// ������
void SceneSelect::Initialize()
{
    Graphics& graphics = Graphics::Instance();

    // 2D���ӏ���������
    sprite = new Sprite("Data/Sprite/Title.png");

    // Start�X�v���C�g������
    start = new Sprite("Data/Sprite/start.png");

    // 3D���f��������
    model1 = new Model("Data/Model/Jammo/Jammo.mdl");
    model2 = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");

    // �l�p�̃X�v���C�g������
    button1 = new Sprite("Data/Sprite/migi.png");
    button2 = new Sprite("Data/Sprite/hidari.png");

    // �����ݒ�
    mode = Notice2D;
    currentModel = nullptr;

    //�J����������
    //Graphics& graphics = Graphics::Instance();
    Camera& camera = Camera::Instance();
    camera.SetLookAt(
        DirectX::XMFLOAT3(0, 1, -10),
        DirectX::XMFLOAT3(0, 1, 0),
        DirectX::XMFLOAT3(0, 1, 0)
    );
    camera.SetPerspectiveFov(
        DirectX::XMConvertToRadians(45),
        graphics.GetScreenWidth() / graphics.GetScreenHeight(),
        0.1f,
        1000.0f
    );
    scale.x = scale.y = scale.z = 0.03f;
}

// �I����
void SceneSelect::Finalize()
{
    // ���������
    if (sprite) { delete sprite; sprite = nullptr; }
    if (start) { delete start; start = nullptr; }
    if (model1) { delete model1; model1 = nullptr; }
    if (model2) { delete model2; model2 = nullptr; }
    if (button1) { delete button1; button1 = nullptr; }
    if (button2) { delete button2; button2 = nullptr; }
}

// �X�V����
void SceneSelect::Update(float elapsedTime)
{
    Mouse& mouse = Input::Instance().GetMouse();

    // �}�E�X�N���b�N�`�F�b�N
    if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
    {
        HandleClick(mouse.GetPositionX(), mouse.GetPositionY());
    }
#if false
    //B�{�^�������Ń����V���b�g�A�j���[�V�����Đ�
    GamePad& gamePad = Input::Instance().GetGamePad();
    if (gamePad.GetButtonDown() & GamePad::BTN_B)
    {
        model1->PlayAnimation(0, false, 0.1f);
    }
    //�����V���b�g�A�j���[�V�����Đ����I������烋�[�v�A�j���[�V�����Đ�
    if (!model1->IsPlayAnimation())
    {
        model1->PlayAnimation(5, true, 0.2f);
    }
#endif
    //���f���A�j���[�V�����X�V����
    model1->UpdateAnimation(elapsedTime);

    //���f���s��X�V
    model1->UpdateTransform(transform);
}

// �`�揈��
#if false
void SceneSelect::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
    FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f }; // RGBA(0.0�`1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    if (mode == Notice2D)
    {
        // 2D�X�v���C�g�`��
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());

        // �^�C�g���X�v���C�g�`��
        sprite->Render(dc,
            screenWidth * 0.25f, screenHeight * 0.25f, screenWidth * 0.5f, screenHeight * 0.5f,
            0, 0, textureWidth, textureHeight,
            0, 1, 1, 1, 1);
    }
    else
    {
        // �X�P�[���s����쐬
        DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

        // ��]�s����쐬
        DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(angle.x);
        DirectX::XMMATRIX Y = DirectX::XMMatrixRotationY(angle.y);
        DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(angle.z);
        DirectX::XMMATRIX R = Z * X * Y;

        // �ʒu�s����쐬
        DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

        // 3�̍s���g�ݍ��킹�A���[���h�s����쐬
        DirectX::XMMATRIX W = S * R * T;

        // �v�Z�������[���h�s������o��
        DirectX::XMStoreFloat4x4(&transform, W);

        currentModel->UpdateTransform(transform);

        // 3D���f���`��
        RenderContext rc;
        rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f }; // ���C�g�����i�������j
        Camera& camera = Camera::Instance();
        rc.view = camera.GetView();
        rc.projection = camera.GetProjection();

        Shader* shader = graphics.GetShader();
        shader->Begin(dc, rc);

        if (currentModel)
        {
            shader->Draw(dc, currentModel);
        }

        shader->End(dc);

        // Start�X�v���C�g�`��
        if (start)
        {
            float startWidth = static_cast<float>(start->GetTextureWidth());
            float startHeight = static_cast<float>(start->GetTextureHeight());
            float screenWidth = static_cast<float>(graphics.GetScreenWidth());
            float screenHeight = static_cast<float>(graphics.GetScreenHeight());
            start->Render(dc,
                screenWidth * 0.45f - 30, screenHeight * 0.8f, startWidth * 0.1f + 100, startHeight * 0.1f + 20,
                0, 0, startWidth, startHeight,
                0, 1, 1, 1, 1);
        }
    }

    // �l�p�̃X�v���C�g�`��
    float buttonWidth = 50.0f;
    float buttonHeight = 50.0f;

    float screenWidth = static_cast<float>(graphics.GetScreenWidth());
    float screenHeight = static_cast<float>(graphics.GetScreenHeight());

    // �E�̎l�p
    float rightButtonX = screenWidth - buttonWidth - 20.0f; // ��ʉE�[����20�s�N�Z�������ɔz�u
    float rightButtonY = screenHeight - buttonHeight - 20.0f; // ��ʉ��[����20�s�N�Z����ɔz�u

    button1->Render(dc,
        rightButtonX, rightButtonY, buttonWidth, buttonHeight,
        0, 0, buttonWidth, buttonHeight,
        0, 1, 1, 1, 1);

    // ���̎l�p
    float leftButtonX = 20.0f; // ��ʍ��[����20�s�N�Z�������ɔz�u
    float leftButtonY = screenHeight - buttonHeight - 20.0f; // ��ʉ��[����20�s�N�Z����ɔz�u

    button2->Render(dc,
        leftButtonX, leftButtonY, buttonWidth, buttonHeight,
        0, 0, buttonWidth, buttonHeight,
        0, 1, 1, 1, 1);

    // �N���b�N����̈ʒu�ƃT�C�Y���X�V
    rightRect = { static_cast<LONG>(rightButtonX), static_cast<LONG>(rightButtonY), static_cast<LONG>(rightButtonX + buttonWidth), static_cast<LONG>(rightButtonY + buttonHeight) };
    leftRect = { static_cast<LONG>(leftButtonX), static_cast<LONG>(leftButtonY), static_cast<LONG>(leftButtonX + buttonWidth), static_cast<LONG>(leftButtonY + buttonHeight) };
}
#endif

void SceneSelect::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
    FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f }; // RGBA(0.0�`1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    if (mode == Notice2D)
    {
        // 2D�X�v���C�g�`��
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());

        // �^�C�g���X�v���C�g�`��
        sprite->Render(dc,
            screenWidth * 0.25f, screenHeight * 0.25f, screenWidth * 0.5f, screenHeight * 0.5f,
            0, 0, textureWidth, textureHeight,
            0, 1, 1, 1, 1);
    }
    else
    {
        // �X�P�[���s����쐬
        DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

        // ��]�s����쐬
        DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(angle.x);
        DirectX::XMMATRIX Y = DirectX::XMMatrixRotationY(angle.y);
        DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(angle.z);
        DirectX::XMMATRIX R = Z * X * Y;

        // �ʒu�s����쐬
        DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

        // 3�̍s���g�ݍ��킹�A���[���h�s����쐬
        DirectX::XMMATRIX W = S * R * T;

        // �v�Z�������[���h�s������o��
        DirectX::XMStoreFloat4x4(&transform, W);

        currentModel->UpdateTransform(transform);

        // 3D���f���`��
        RenderContext rc;
        rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f }; // ���C�g�����i�������j
        Camera& camera = Camera::Instance();
        rc.view = camera.GetView();
        rc.projection = camera.GetProjection();

        Shader* shader = graphics.GetShader();
        shader->Begin(dc, rc);

        if (currentModel)
        {
            shader->Draw(dc, currentModel);
        }

        shader->End(dc);

        // Start�X�v���C�g�`��
        if (start)
        {
            float startWidth = static_cast<float>(start->GetTextureWidth());
            float startHeight = static_cast<float>(start->GetTextureHeight());
            float screenWidth = static_cast<float>(graphics.GetScreenWidth());
            float screenHeight = static_cast<float>(graphics.GetScreenHeight());

            float startX = screenWidth * 0.45f - 30;
            float startY = screenHeight * 0.8f;
            float startRenderWidth = startWidth * 0.1f + 100;
            float startRenderHeight = startHeight * 0.1f + 20;

            start->Render(dc,
                startX, startY, startRenderWidth, startRenderHeight,
                0, 0, startWidth, startHeight,
                0, 1, 1, 1, 1);

            start->SetPosition(startX, startY, startRenderWidth, startRenderHeight);
        }
    }

    // �l�p�̃X�v���C�g�`��
    float buttonWidth = 50.0f;
    float buttonHeight = 50.0f;

    float screenWidth = static_cast<float>(graphics.GetScreenWidth());
    float screenHeight = static_cast<float>(graphics.GetScreenHeight());

    // �E�̎l�p
    float rightButtonX = screenWidth - buttonWidth - 20.0f; // ��ʉE�[����20�s�N�Z�������ɔz�u
    float rightButtonY = screenHeight - buttonHeight - 20.0f; // ��ʉ��[����20�s�N�Z����ɔz�u

    button1->Render(dc,
        rightButtonX, rightButtonY, buttonWidth, buttonHeight,
        0, 0, buttonWidth, buttonHeight,
        0, 1, 1, 1, 1);

    // ���̎l�p
    float leftButtonX = 20.0f; // ��ʍ��[����20�s�N�Z�������ɔz�u
    float leftButtonY = screenHeight - buttonHeight - 20.0f; // ��ʉ��[����20�s�N�Z����ɔz�u

    button2->Render(dc,
        leftButtonX, leftButtonY, buttonWidth, buttonHeight,
        0, 0, buttonWidth, buttonHeight,
        0, 1, 1, 1, 1);

    // �N���b�N����̈ʒu�ƃT�C�Y���X�V
    rightRect = { static_cast<LONG>(rightButtonX), static_cast<LONG>(rightButtonY), static_cast<LONG>(rightButtonX + buttonWidth), static_cast<LONG>(rightButtonY + buttonHeight) };
    leftRect = { static_cast<LONG>(leftButtonX), static_cast<LONG>(leftButtonY), static_cast<LONG>(leftButtonX + buttonWidth), static_cast<LONG>(leftButtonY + buttonHeight) };
}

// �N���b�N����

void SceneSelect::HandleClick(int x, int y)
{
    if (PtInRect(&rightRect, { x, y }))
    {
        switch (mode)
        {
        case Notice2D:
            mode = Model3D_1;
            currentModel = model1;
            model1->PlayAnimation(3, false, 0.1f); // �����ŃA�j���[�V�������J�n
            break;
        case Model3D_1:
            mode = Model3D_2;
            currentModel = model2;
            break;
        case Model3D_2:
            mode = Notice2D;
            currentModel = nullptr;
            break;
        }
    }
    else if (PtInRect(&leftRect, { x, y }))
    {
        switch (mode)
        {
        case Notice2D:
            mode = Model3D_2;
            currentModel = model2;
            break;
        case Model3D_1:
            mode = Notice2D;
            currentModel = nullptr;
            break;
        case Model3D_2:
            mode = Model3D_1;
            currentModel = model1;
            model1->PlayAnimation(3, false, 0.1f); // �����ŃA�j���[�V�������J�n
            break;
        }
    }
    // �V�����R�[�h�ǉ�: Start�X�v���C�g�̃N���b�N����
    if (mode == Model3D_1)
    {
        if (start->HitTest(x, y))
        {
            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame()));
        }
    }
    else if (mode == Model3D_2)
    {
        if (start->HitTest(x, y))
        {
            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame2())); // SceneGame2������������L����
        }
    }
}
