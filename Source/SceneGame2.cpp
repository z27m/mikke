#include "Graphics/Graphics.h"
#include "SceneGame2.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "EnemySlime.h"
#include "EffectManager.h"
#include "Input/Input.h"
#include "StageManager.h"
#include "StageMain2.h"
#include "StageMoveFloor.h"
#include "StageFind.h"
#include "SceneManager.h"
#include "SceneResult.h"
#include "SceneLoading.h"
#include "Input/Input.h"

//UI�֌W�w�b�_�[
#include "UIManager.h"
#include "UI_Clock.h"
#include "UI_DisItems.h"
#include <Audio/Audio.h>

StageFind* stageFind2[4] = { 0 };

//���َq�̉ƃX�e�[�W
// ������
void SceneGame2::Initialize()
{
	// �ʏ�X�e�[�W������
	StageManager& stageManager = StageManager::Instance();
	stageMain2 = new StageMain2();
	stageMain2->SetFindObjectType(FindObjectType::None);
	stageManager.Register(stageMain2);

	// �݂������X�e�[�W�̏�����
	stageFind2[0] = new StageFind("Data/Model/team/cookie.mdl");
	stageFind2[0]->SetFindObjectType(FindObjectType::Find);
	stageFind2[0]->SetPosition({ 0, -10.0, 0 });
	stageFind2[0]->m_index = 0;
	stageManager.Register(stageFind2[0]);


	//�G�t�F�N�g�ǂݍ���
	maru = new Effect("Data/Effect/maru.efkefc");
	batu = new Effect("Data/Effect/batu.efkefc");

	aka = new Sprite("Data/Sprite/aka.png");

	BGM_House = Audio::Instance().LoadAudioSource("Data/Audio/house2.wav");
	SE_yes = Audio::Instance().LoadAudioSource("Data/Audio/yes.wav");
	SE_not = Audio::Instance().LoadAudioSource("Data/Audio/not.wav");
	BGM_House->Play(true);
#if false
	StageMoveFloor* stageMoveFloor = new StageMoveFloor();
	stageMoveFloor->SetStartPoint(DirectX::XMFLOAT3(0, 1, 3));
	stageMoveFloor->SetGoalPoint(DirectX::XMFLOAT3(10, 2, 3));
	stageMoveFloor->SetTorque(DirectX::XMFLOAT3(0, 1.0f, 0));
	stageManager.Register(stageMoveFloor);
#endif


	//�v���C���[������
	player = new Player();

	//�J���������ݒ�
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAt(DirectX::XMFLOAT3(0, 10, -10),
		DirectX::XMFLOAT3(0, 0, 0),
		DirectX::XMFLOAT3(0, 1, 0)
	);

	camera.SetPerspectiveFov(DirectX::XMConvertToRadians(45),
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f, 1000.0f);

	//�J�����R���g���[���[�I����
	cameraController = new CameraController;

	//�^�C�}�[�ݒ�
	//game_timer = 0;

	//�Q�[�W�X�v���C�g
	gauge = new Sprite();

	//UI_Clock
	UIManager& uiManager = UIManager::Instance();
	Clock* clock = new Clock();
	clock->Initialize();
	uiManager.UIRegister(clock);

	//UI_DisItems
	disItems = new DisItems();
	disItems->stageNo = 1;
	disItems->Initialize();
	uiManager.UIRegister(disItems);

}

// �I����
void SceneGame2::Finalize()
{
	//�Q�[�W�X�v���C�g�I����
	if (gauge != nullptr) {
		delete gauge;
		gauge = nullptr;
	}

	//�J�����R���g���[���[�I����
	if (cameraController != nullptr) {
		delete cameraController;
		cameraController = nullptr;
	}


	//�X�e�[�W�I����
	StageManager::Instance().Clear();

	//�v���C���[�I����
	if (player != nullptr) {
		delete player;
		player = nullptr;
	}

	//UI�I����
	UIManager::Instance().Clear();

	BGM_House->Stop();
}

// �X�V����
void SceneGame2::Update(float elapsedTime)
{
	//�J�����R���g���[���[�X�V����
	DirectX::XMFLOAT3 target = stageMain2->GetPosition();
	//target.y += 10.0f;
	//target.z -= 20.0f;
	cameraController->SetTarget(target);
	cameraController->Update(elapsedTime);


	//�X�e�[�W�X�V����
	StageManager::Instance().Update(elapsedTime);

	//�v���C���[�X�V����
	player->Update(elapsedTime);

	//UI�X�V����
	UIManager::Instance().Update(elapsedTime);

	//�G�t�F�N�g�X�V����
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

	
	if (checkCount >= 1) {
		SceneManager::Instance().ChangeScene(new SceneLoading(new SceneResult));
	}
}

// �`�揈��
void SceneGame2::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
	FLOAT color[] = { 1.0f, 0.8f, 1.0f, 1.0f };	// RGBA(0.0�`1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// �`�揈��
	RenderContext rc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ���C�g�����i�������j

	//�J�����p�����[�^�ݒ�
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();

#if 0
	if (disItems != nullptr)
	{
		// UI�폜���o���I������̂�UI�폜
		if (disItems->IsFinish())
		{
			UIManager::Instance().Remove(disItems);
			disItems = nullptr;
		}
	}
#endif

	// FindObject ���N���b�N�������ǂ������`�F�b�N
	CheckFindObject(dc, rc.view, rc.projection);



	// 3D���f���`��
	{
		Shader* shader = graphics.GetShader();
		shader->Begin(dc, rc);

		//�X�e�[�W�`��
		StageManager::Instance().Render(dc, shader);

		//�v���C���[�`��
		player->Render(dc, shader);
		shader->End(dc);

	}

	//3D�G�t�F�N�g�`��
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}

	// 2D�X�v���C�g�`��
	{
		/*RenderEnemyGauge(dc, rc.view, rc.projection);*/


		if (isMissFlag == true)
		{

			//��ʂɔ����Ԃ��o��
			aka->Render(dc, 0, 0, 1280, 720, 0, 0, 0, 0, 0, 1, 0, 0, 1);
		}

		UIManager::Instance().Render();
	}


}


void SceneGame2::CheckFindObject(ID3D11DeviceContext* dc, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection) {
#if 1

	//�r���[�|�[�g
	D3D11_VIEWPORT viewport;
	UINT numViewports = 1;
	dc->RSGetViewports(&numViewports, &viewport);

	//�ϊ��s��
	DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&view);
	DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&projection);
	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();

	//�}�E�X�őI���A���딻�菈��
	Mouse& mouse = Input::Instance().GetMouse();
	if (mouse.GetButtonDown() & Mouse::BTN_LEFT) {
		//�}�E�X�J�[�\�����W���擾
		DirectX::XMFLOAT3 screenPosition;
		screenPosition.x = static_cast<float>(mouse.GetPositionX());
		screenPosition.y = static_cast<float>(mouse.GetPositionY());

		DirectX::XMVECTOR ScreenPosition, WorldPosition;

		//���C�̎n�_���v�Z
		screenPosition.z = 0.0f;  //�r���[�|�[�g�̐[�x��0.0�ɐݒ�
		//ScreenPosition��XMVECTOR�ɕϊ�9								
		ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
		//�n�_��2D����3D�ɕϊ�
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

		//���[���h��ԏ�ł̃��C�̎n�_�iWorldPosition��XMFLOAT3�ɕϊ��j
		DirectX::XMFLOAT3 rayStart;
		DirectX::XMStoreFloat3(&rayStart, WorldPosition);

		//���C�̏I�_���Z�o
		screenPosition.z = 1.0f;//�r���[�|�[�g�̐[�x��1.0�ɐݒ�
		//screenPosition��XMVECTOR�ɕϊ�
		ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
		//�n�_��2D����3D�ɕϊ�
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
		//���[���h��ԏ�ł̃��C�̏I�_�iWorldPosition��XMFLOAT3�ɕϊ��j
		DirectX::XMFLOAT3 rayEnd;
		DirectX::XMStoreFloat3(&rayEnd, WorldPosition);

		//���C�L���X�g(��ō�������C�ƃX�e�[�W�Ƃ̏Փˁj
		HitResult hit;
		if (StageManager::Instance().RayCast(rayStart, rayEnd, hit)) {

			if (hit.materialIndex == FindObjectType::None)
			{
				// �~�X��������
				isMissFlag = true;

				//�s�����G�t�F�N�g�Đ�
				batu->Play(hit.position);

				//�c��b�������炷
				if (batu->Play(hit.position))
				{
					//Clock::Update()
				}

				SE_not->Play(false);

			}
			else if (hit.materialIndex == FindObjectType::Find)
			{
				for (int index : m_checkList) {
					if (index == hit.findIndex)
						return;
				}

				//�����G�t�F�N�g�Đ�
				maru->Play(hit.position);

				SE_yes->Play(false);

				//UI�̍폜���o�J�n
				if (disItems != nullptr)
				{
					disItems->Play(0);
				}

				checkCount++;

				m_checkList.push_back(hit.findIndex);
			}

			//�G��z�u�i�G�𐶐��j
			//EnemySlime* slime = new EnemySlime();
			//�G�̈ʒu�����C���q�b�g�����ʒu�ɐݒ�
			//slime->SetPosition(hit.position);
			//�G�Ǘ��ɓo�^
			//EnemyManager::Instance().Register(slime);
		}
	}

#endif
}