#include "Graphics/Graphics.h"
#include "SceneOver.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "Input/Input.h"
#include "SceneLoading.h"

// test

//初期化
void SceneOver::Initialize()
{
    //スプライト初期化
    sprite = new Sprite("Data/Sprite/aka.png");
}

//終了化
void SceneOver::Finalize()
{
    //スプライト終了化
    if (sprite != nullptr) {
        delete sprite;
        sprite = nullptr;
    }
}

//更新処理
void SceneOver::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    //何かボタンを押したらローディングシーンへ切り替え
    const GamePadButton anyButton =
        GamePad::BTN_A
        | GamePad::BTN_B
        | GamePad::BTN_X
        | GamePad::BTN_Y
        | GamePad::BTN_START;

    if (gamePad.GetButtonDown() & anyButton) {
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
    }


}

//描画処理
void SceneOver::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    //画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f,0.0f,0.5f,1.0f };
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    //2Dスプライト描画
    {
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());
        //タイトルスプライト描画
        sprite->Render(dc,
            screenWidth * 0.25f, screenHeight * 0.25f, screenWidth * 0.5f, screenHeight * 0.5f,
            0, 0, textureWidth, textureHeight,
            0, 1, 1, 1, 1);


    }
}