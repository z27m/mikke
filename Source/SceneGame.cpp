#include "Graphics/Graphics.h"
#include "SceneGame.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "EnemySlime.h"
#include "EffectManager.h"
#include "Input/Input.h"
#include "StageManager.h"
#include "StageMain.h"
#include "StageMoveFloor.h"
#include "StageFind.h"
#include "SceneManager.h"
#include "SceneResult.h"
#include "SceneLoading.h"
#include "Input/Input.h"

//UI関係ヘッダー
#include "UIManager.h"
#include "UI_Clock.h"
#include "UI_DisItems.h"

StageFind* stageFind[4] = { 0 };


//海ステージ
// 初期化
void SceneGame::Initialize()
{
	// 通常ステージ初期化
	StageManager& stageManager = StageManager::Instance();
	stageMain = new StageMain();
	stageMain->SetFindObjectType(FindObjectType::None);
	stageManager.Register(stageMain);

	// みつけだすステージの初期化
	stageFind[0] = new StageFind("Data/Model/team/cookie.mdl");
	stageFind[0]->SetFindObjectType(FindObjectType::Find);
	stageFind[0]->SetPosition({ 0, 50.0, 0});
	stageFind[0]->m_index = 0;
	stageManager.Register(stageFind[0]);

	//stageFind[1] = new StageFind("Data/Model/team/cookie.mdl");
	//stageFind[1]->SetFindObjectType(FindObjectType::Find);
	//stageFind[1]->SetPosition({ 0.0, -10.0, 0 });
	//stageManager.Register(stageFind[1]);

	//stageFind[2] = new StageFind("Data/Model/team/cookie.mdl");
	//stageFind[2]->SetFindObjectType(FindObjectType::Find);
	//stageFind[2]->SetPosition({ 0, -20.0, 0 });
	//stageManager.Register(stageFind[2]);

	//stageFind[3] = new StageFind("Data/Model/team/cookie.mdl");
	//stageFind[3]->SetFindObjectType(FindObjectType::Find);
	//stageFind[3]->SetPosition({ 50.0, 50.0, 0 });
	//stageManager.Register(stageFind[3]);

	stageFind[4] = new StageFind("Data/Model/team/cookie.mdl");
	stageFind[4]->SetFindObjectType(FindObjectType::Find);
	stageFind[4]->SetPosition({ -10.0, 0, 0 });
	stageFind[4]->m_index = 4;
	stageManager.Register(stageFind[4]);

	//エフェクト読み込み
	maru = new Effect("Data/Effect/maru.efkefc");
	batu = new Effect("Data/Effect/batu.efkefc");

	aka = new Sprite("Data/Sprite/aka.png");

	BGM_Sea = Audio::Instance().LoadAudioSource("Data/Audio/sea2.wav");
	BGM_Sea->Play(true);

#if false
	StageMoveFloor* stageMoveFloor = new StageMoveFloor();
	stageMoveFloor->SetStartPoint(DirectX::XMFLOAT3(0, 1, 3));
	stageMoveFloor->SetGoalPoint(DirectX::XMFLOAT3(10, 2, 3));
	stageMoveFloor->SetTorque(DirectX::XMFLOAT3(0, 1.0f, 0));
	stageManager.Register(stageMoveFloor);
#endif


	//プレイヤー初期化
	player = new Player();

	//カメラ初期設定
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAt(DirectX::XMFLOAT3(0, 10, -10),
		DirectX::XMFLOAT3(0, 0, 0),
		DirectX::XMFLOAT3(0, 1, 0)
	);

	camera.SetPerspectiveFov(DirectX::XMConvertToRadians(45),
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f, 1000.0f);

	//カメラコントローラー終了化
	cameraController = new CameraController;

	//タイマー設定
	//game_timer = 0;

	//ゲージスプライト
	gauge = new Sprite();

	//UI_Clock
	UIManager& uiManager = UIManager::Instance();
	clock = new Clock();
	clock->Initialize();
	uiManager.UIRegister(clock);

	//UI_DisItems
	disItems = new DisItems();
	disItems->Initialize();
	uiManager.UIRegister(disItems);

}

// 終了化
void SceneGame::Finalize()
{
	//ゲージスプライト終了化
	if (gauge != nullptr) {
		delete gauge;
		gauge = nullptr;
	}

	//カメラコントローラー終了化
	if (cameraController != nullptr) {
		delete cameraController;
		cameraController = nullptr;
	}


	//ステージ終了化
	StageManager::Instance().Clear();

	//プレイヤー終了化
	if (player != nullptr) {
		delete player;
		player = nullptr;
	}

	//UI終了化
	UIManager::Instance().Clear();

	BGM_Sea->Stop();
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	//カメラコントローラー更新処理
	DirectX::XMFLOAT3 target = stageMain->GetPosition();
	//target.y += 10.0f;
	//target.z -= 20.0f;
	cameraController->SetTarget(target);
	cameraController->Update(elapsedTime);


	//ステージ更新処理
	StageManager::Instance().Update(elapsedTime);

	//プレイヤー更新処理
	player->Update(elapsedTime);

	//UI更新処理
	UIManager::Instance().Update(elapsedTime);

	//エフェクト更新処理
	EffectManager::Instance().Update(elapsedTime);

	if (isMissFlag == true)
	{
		totalTime += elapsedTime;
		if (totalTime >= 0.2f)
		{
			isMissFlag = false;
			totalTime = 0.0f;
		}
	}


	

	if (checkCount>=2) {
		SceneManager::Instance().ChangeScene(new SceneLoading(new SceneResult));
	}
	
	

}

// 描画処理
void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// 画面クリア＆レンダーターゲット設定
	FLOAT color[] = { 0.8f, 1.0f, 1.0f, 1.0f };	// RGBA(0.0～1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// 描画処理
	RenderContext rc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ライト方向（下方向）

	//カメラパラメータ設定
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();

#if 0
	if (disItems != nullptr)
	{
		// UI削除演出が終わったのでUI削除
		if (disItems->IsFinish())
		{
			UIManager::Instance().Remove(disItems);
			disItems = nullptr;
		}
	}
#endif
	
	// FindObject をクリックしたかどうかをチェック
	CheckFindObject(dc, rc.view, rc.projection);



	// 3Dモデル描画
	{
		Shader* shader = graphics.GetShader();
		shader->Begin(dc, rc);

		//ステージ描画
		StageManager::Instance().Render(dc, shader);

		//プレイヤー描画
		player->Render(dc, shader);
		shader->End(dc);

	}

	//3Dエフェクト描画
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}

	// 2Dスプライト描画
	{
		/*RenderEnemyGauge(dc, rc.view, rc.projection);*/


		if (isMissFlag == true)
		{
			
			//画面に薄い赤を出す
			aka->Render(dc, 0, 0, 1280, 720, 0, 0, 0, 0, 0, 1, 0, 0, 1);
		}

		UIManager::Instance().Render();
	}


}


void SceneGame::CheckFindObject(ID3D11DeviceContext* dc, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection){
#if 1

	//ビューポート
	D3D11_VIEWPORT viewport;
	UINT numViewports = 1;
	dc->RSGetViewports(&numViewports, &viewport);

	//変換行列
	DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&view);
	DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&projection);
	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();

	//マウスで選択、正誤判定処理
	Mouse& mouse = Input::Instance().GetMouse();
	if (mouse.GetButtonDown() & Mouse::BTN_LEFT) {
		//マウスカーソル座標を取得
		DirectX::XMFLOAT3 screenPosition;
		screenPosition.x = static_cast<float>(mouse.GetPositionX());
		screenPosition.y = static_cast<float>(mouse.GetPositionY());

		DirectX::XMVECTOR ScreenPosition, WorldPosition;

		//レイの始点を計算
		screenPosition.z = 0.0f;  //ビューポートの深度を0.0に設定
		//ScreenPositionをXMVECTORに変換9								
		ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
		//始点を2Dから3Dに変換
		WorldPosition = DirectX::XMVector3Unproject
		(ScreenPosition,
			viewport.TopLeftX,   //0.0f
			viewport.TopLeftY,   //0.0f
			viewport.Width,
			viewport.Height,
			viewport.MinDepth,   //0.0f,																																																																						
			viewport.MaxDepth,   //1.0f,
			Projection,  //DirectX::XMLoadFloat4x4(&projection),
			View,        //DirectX::XMLoadFloat4x4(&view),
			World
		);

		//ワールド空間上でのレイの始点（WorldPositionをXMFLOAT3に変換）
		DirectX::XMFLOAT3 rayStart;
		DirectX::XMStoreFloat3(&rayStart, WorldPosition);

		//レイの終点を算出
		screenPosition.z = 1.0f;//ビューポートの深度を1.0に設定
		//screenPositionをXMVECTORに変換
		ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
		//始点を2Dから3Dに変換
		WorldPosition = DirectX::XMVector3Unproject
		(ScreenPosition,
			viewport.TopLeftX,   //0.0f,
			viewport.TopLeftY,   //0.0f,
			viewport.Width,
			viewport.Height,
			viewport.MinDepth,   //0.0f,																																																																						
			viewport.MaxDepth,   //1.0f,
			Projection,  //DirectX::XMLoadFloat4x4(&projection),
			View,        //DirectX::XMLoadFloat4x4(&view),
			World
		);
		//ワールド空間上でのレイの終点（WorldPositionをXMFLOAT3に変換）
		DirectX::XMFLOAT3 rayEnd;
		DirectX::XMStoreFloat3(&rayEnd, WorldPosition);

		//レイキャスト(上で作ったレイとステージとの衝突）
		HitResult hit;
		if (StageManager::Instance().RayCast(rayStart,rayEnd,hit)) {
 
			if (hit.materialIndex == FindObjectType::None)
			{
				// ミスを押した
				isMissFlag = true;

				//残り秒数を減らす(何度減らすか)
				clock->Miss(10);

				//不正解エフェクト再生
				batu->Play(hit.position);
				
			}
			else if (hit.materialIndex == FindObjectType::Find)
			{
				for (int index : m_checkList) {
					if (index == hit.findIndex)
						return;
				}


				//正解エフェクト再生
				maru->Play(hit.position);

				//UIの削除演出開始
				//if (disItems != nullptr)
				//{
				//	disItems->Play(0);
				//}

#if 1		//それぞれのアイテムのUI削除演出
				switch (disItems != nullptr || FindObjectType::Find)
				{
				case DisItemNum::Obj0:


					
				case DisItemNum::Obj1:
					disItems->Play(0);

					break;
				case DisItemNum::Obj2:
					disItems->Play(1);

					break;
				case DisItemNum::Obj3:
					disItems->Play(2);

					break;
				case DisItemNum::Obj4:
					disItems->Play(3);

					break;
				}
#endif // 0

				checkCount++;

				m_checkList.push_back(hit.findIndex);
			}
 
			//敵を配置（敵を生成）
			//EnemySlime* slime = new EnemySlime();
			//敵の位置をレイがヒットした位置に設定
			//slime->SetPosition(hit.position);
			//敵管理に登録
			//EnemyManager::Instance().Register(slime);
		}
	}

#endif
	}