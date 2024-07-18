#include "Graphics/Graphics.h"
#include "SceneTitle.h"
#include "SceneSelect.h"
#include "SceneManager.h"
#include "Input/Input.h"
#include "SceneLoading.h"

// test

//初期化
void SceneTitle::Initialize()
{   
   //スプライト初期化
    sprite = new Sprite("Data/Sprite/title.png");

    //オーディオ初期化
    BGM_Title = Audio::Instance().LoadAudioSource("Data/Audio/title2.wav");
    SE_select = Audio::Instance().LoadAudioSource("Data/Audio/select.wav");
    BGM_Title->Play(true);
}

//終了化
void SceneTitle::Finalize()
{
    //スプライト終了化
    if (sprite != nullptr) {
        delete sprite;
        sprite = nullptr;
    }
    BGM_Title->Stop();
}

//更新処理
void SceneTitle::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    //何かボタンを押したらローディングシーンへ切り替え

    //const GamePadButton anyButton =
    //    GamePad::BTN_A
    //    | GamePad::BTN_B
    //    | GamePad::BTN_X
    //    | GamePad::BTN_Y
    //    | GamePad::BTN_START;

    //if (gamePad.GetButtonDown() & anyButton) {
    //    SE_select->Play(false);
    //    SceneManager::Instance().ChangeScene(new SceneLoading(new SceneSelect));
    //}


    Mouse& mouse = Input::Instance().GetMouse();

    // マウスクリックチェック
    if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
    {
        SE_select->Play(false);
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneSelect));
    }




    //GamePad& gamePad = Input::Instance().GetGamePad();

    ////何かボタンを押したらローディングシーンへ切り替え
    //const GamePadButton anyButton =
    //    GamePad::BTN_A
    //    | GamePad::BTN_B
    //    | GamePad::BTN_X
    //    | GamePad::BTN_Y;

    //bool padPush = (gamePad.GetButtonDown() & anyButton);

    //Mouse& mouse = Input::Instance().GetMouse();

    //// マウスクリックチェック
    //bool mousePush = (mouse.GetButtonDown() & Mouse::BTN_LEFT);

    //if (padPush || mousePush)
    //{
    //    SE_select->Play(false);
    //    SceneManager::Instance().ChangeScene(new SceneLoading(new SceneSelect));
    //}


    const GamePadButton anyButton =
        GamePad::BTN_A
        | GamePad::BTN_B
        | GamePad::BTN_X
        | GamePad::BTN_Y;

    if (gamePad.GetButtonDown() & anyButton) {
        SE_select->Play(false);
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneSelect));
    }

}


//描画処理
void SceneTitle::Render()
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
            0,0, screenWidth, screenHeight,
            0, 0, textureWidth, textureHeight,
            0, 1, 1, 1, 1);
    }
}
