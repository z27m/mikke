#include "Graphics/Graphics.h"
#include "SceneSelect.h"
#include "Camera.h"
#include "Input/Input.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "SceneGame.h"
#include "SceneGame2.h"



// 初期化
void SceneSelect::Initialize()
{
    Graphics& graphics = Graphics::Instance();

    // 2D注意書き初期化
    sprite = new Sprite("Data/Sprite/Title.png");

    // Startスプライト初期化
    start = new Sprite("Data/Sprite/start.png");

    // 3Dモデル初期化
    model1 = new Model("Data/Model/Jammo/Jammo.mdl");
    model2 = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");

    // 四角のスプライト初期化
    button1 = new Sprite("Data/Sprite/migi.png");
    button2 = new Sprite("Data/Sprite/hidari.png");

    // 初期設定
    mode = Notice2D;
    currentModel = nullptr;

    //カメラ初期化
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

// 終了化
void SceneSelect::Finalize()
{
    // メモリ解放
    if (sprite) { delete sprite; sprite = nullptr; }
    if (start) { delete start; start = nullptr; }
    if (model1) { delete model1; model1 = nullptr; }
    if (model2) { delete model2; model2 = nullptr; }
    if (button1) { delete button1; button1 = nullptr; }
    if (button2) { delete button2; button2 = nullptr; }
}

// 更新処理
void SceneSelect::Update(float elapsedTime)
{
    Mouse& mouse = Input::Instance().GetMouse();

    // マウスクリックチェック
    if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
    {
        HandleClick(mouse.GetPositionX(), mouse.GetPositionY());
    }
#if false
    //Bボタン押下でワンショットアニメーション再生
    GamePad& gamePad = Input::Instance().GetGamePad();
    if (gamePad.GetButtonDown() & GamePad::BTN_B)
    {
        model1->PlayAnimation(0, false, 0.1f);
    }
    //ワンショットアニメーション再生が終わったらループアニメーション再生
    if (!model1->IsPlayAnimation())
    {
        model1->PlayAnimation(5, true, 0.2f);
    }
#endif
    //モデルアニメーション更新処理
    model1->UpdateAnimation(elapsedTime);

    //モデル行列更新
    model1->UpdateTransform(transform);
}

// 描画処理
#if false
void SceneSelect::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // 画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f }; // RGBA(0.0～1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    if (mode == Notice2D)
    {
        // 2Dスプライト描画
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());

        // タイトルスプライト描画
        sprite->Render(dc,
            screenWidth * 0.25f, screenHeight * 0.25f, screenWidth * 0.5f, screenHeight * 0.5f,
            0, 0, textureWidth, textureHeight,
            0, 1, 1, 1, 1);
    }
    else
    {
        // スケール行列を作成
        DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

        // 回転行列を作成
        DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(angle.x);
        DirectX::XMMATRIX Y = DirectX::XMMatrixRotationY(angle.y);
        DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(angle.z);
        DirectX::XMMATRIX R = Z * X * Y;

        // 位置行列を作成
        DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

        // 3つの行列を組み合わせ、ワールド行列を作成
        DirectX::XMMATRIX W = S * R * T;

        // 計算したワールド行列を取り出す
        DirectX::XMStoreFloat4x4(&transform, W);

        currentModel->UpdateTransform(transform);

        // 3Dモデル描画
        RenderContext rc;
        rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f }; // ライト方向（下方向）
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

        // Startスプライト描画
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

    // 四角のスプライト描画
    float buttonWidth = 50.0f;
    float buttonHeight = 50.0f;

    float screenWidth = static_cast<float>(graphics.GetScreenWidth());
    float screenHeight = static_cast<float>(graphics.GetScreenHeight());

    // 右の四角
    float rightButtonX = screenWidth - buttonWidth - 20.0f; // 画面右端から20ピクセル内側に配置
    float rightButtonY = screenHeight - buttonHeight - 20.0f; // 画面下端から20ピクセル上に配置

    button1->Render(dc,
        rightButtonX, rightButtonY, buttonWidth, buttonHeight,
        0, 0, buttonWidth, buttonHeight,
        0, 1, 1, 1, 1);

    // 左の四角
    float leftButtonX = 20.0f; // 画面左端から20ピクセル内側に配置
    float leftButtonY = screenHeight - buttonHeight - 20.0f; // 画面下端から20ピクセル上に配置

    button2->Render(dc,
        leftButtonX, leftButtonY, buttonWidth, buttonHeight,
        0, 0, buttonWidth, buttonHeight,
        0, 1, 1, 1, 1);

    // クリック判定の位置とサイズを更新
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

    // 画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f }; // RGBA(0.0～1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    if (mode == Notice2D)
    {
        // 2Dスプライト描画
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());

        // タイトルスプライト描画
        sprite->Render(dc,
            screenWidth * 0.25f, screenHeight * 0.25f, screenWidth * 0.5f, screenHeight * 0.5f,
            0, 0, textureWidth, textureHeight,
            0, 1, 1, 1, 1);
    }
    else
    {
        // スケール行列を作成
        DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

        // 回転行列を作成
        DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(angle.x);
        DirectX::XMMATRIX Y = DirectX::XMMatrixRotationY(angle.y);
        DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(angle.z);
        DirectX::XMMATRIX R = Z * X * Y;

        // 位置行列を作成
        DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

        // 3つの行列を組み合わせ、ワールド行列を作成
        DirectX::XMMATRIX W = S * R * T;

        // 計算したワールド行列を取り出す
        DirectX::XMStoreFloat4x4(&transform, W);

        currentModel->UpdateTransform(transform);

        // 3Dモデル描画
        RenderContext rc;
        rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f }; // ライト方向（下方向）
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

        // Startスプライト描画
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

    // 四角のスプライト描画
    float buttonWidth = 50.0f;
    float buttonHeight = 50.0f;

    float screenWidth = static_cast<float>(graphics.GetScreenWidth());
    float screenHeight = static_cast<float>(graphics.GetScreenHeight());

    // 右の四角
    float rightButtonX = screenWidth - buttonWidth - 20.0f; // 画面右端から20ピクセル内側に配置
    float rightButtonY = screenHeight - buttonHeight - 20.0f; // 画面下端から20ピクセル上に配置

    button1->Render(dc,
        rightButtonX, rightButtonY, buttonWidth, buttonHeight,
        0, 0, buttonWidth, buttonHeight,
        0, 1, 1, 1, 1);

    // 左の四角
    float leftButtonX = 20.0f; // 画面左端から20ピクセル内側に配置
    float leftButtonY = screenHeight - buttonHeight - 20.0f; // 画面下端から20ピクセル上に配置

    button2->Render(dc,
        leftButtonX, leftButtonY, buttonWidth, buttonHeight,
        0, 0, buttonWidth, buttonHeight,
        0, 1, 1, 1, 1);

    // クリック判定の位置とサイズを更新
    rightRect = { static_cast<LONG>(rightButtonX), static_cast<LONG>(rightButtonY), static_cast<LONG>(rightButtonX + buttonWidth), static_cast<LONG>(rightButtonY + buttonHeight) };
    leftRect = { static_cast<LONG>(leftButtonX), static_cast<LONG>(leftButtonY), static_cast<LONG>(leftButtonX + buttonWidth), static_cast<LONG>(leftButtonY + buttonHeight) };
}

// クリック処理

void SceneSelect::HandleClick(int x, int y)
{
    if (PtInRect(&rightRect, { x, y }))
    {
        switch (mode)
        {
        case Notice2D:
            mode = Model3D_1;
            currentModel = model1;
            model1->PlayAnimation(3, false, 0.1f); // ここでアニメーションを開始
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
            model1->PlayAnimation(3, false, 0.1f); // ここでアニメーションを開始
            break;
        }
    }
    // 新しいコード追加: Startスプライトのクリック判定
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
            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame2())); // SceneGame2が完成したら有効化
        }
    }
}
