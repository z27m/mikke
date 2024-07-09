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



// 初期化
void SceneGame::Initialize()
{
	// 通常ステージ初期化
	StageManager& stageManager = StageManager::Instance();
	stageMain = new StageMain();
	stageMain->SetFindObjectType(FindObjectType::None);
	stageManager.Register(stageMain);

	// みつけだすステージの初期化
	StageFind* stageFind = new StageFind("Data/Model/team/cookie.mdl");
	stageFind->SetFindObjectType(FindObjectType::Find);
	stageFind->SetPosition({ 0, 50.0, 0});
	stageManager.Register(stageFind);

	//stageFind = new StageFind("Data/Model/team/cookie.mdl");
	//stageFind->SetFindObjectType(FindObjectType::Find);
	//stageFind->SetPosition({ -10.0, 0, 0 });
	//stageManager.Register(stageFind);



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

	

	//ゲージスプライト
	gauge = new Sprite();
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


	//エフェクト更新処理
	EffectManager::Instance().Update(elapsedTime);
}

// 描画処理
void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// 画面クリア＆レンダーターゲット設定
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0〜1.0)
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
				//不正解エフェクト（？）再生

				//一瞬画面を揺らす　or　画面を薄い赤にする

				//残り秒数を減らす



				int a;
				a = 100;

			}
			else if (hit.materialIndex == FindObjectType::Find)
			{
				//デバッグ用）当たったら画面の色を変える　　　　　　　　　　正解エフェクト（？）再生

				//UIの削除

				int a;
				a = 100;
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