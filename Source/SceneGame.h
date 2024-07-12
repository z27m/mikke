#pragma once


#include "Player.h"
#include "CameraController.h"
#include "Scene.h"
#include "Graphics/Sprite.h"
#include "stageMain.h"

// �Q�[���V�[��
class SceneGame:public Scene
{
public:
	SceneGame() {}
	~SceneGame() override{}

	// ������
	void Initialize() override;

	// �I����
	void Finalize() override;

	// �X�V����
	void Update(float elapsedTime) override;

	// �`�揈��
	void Render() override;

private:
	//�G�l�~�[HP�Q�[�W�`��
	void CheckFindObject(
		ID3D11DeviceContext* dc,
		const DirectX::XMFLOAT4X4& view,
		const DirectX::XMFLOAT4X4& projection
	);

private:
	
	Player* player = nullptr;
	CameraController* cameraController = nullptr;
	Sprite* gauge = nullptr;
	StageMain* stageMain;

	Effect* maru = nullptr;
	Effect* batu = nullptr;

	Sprite* aka = nullptr;

	//int game_timer = 0;

	// true...�Ԉ�������̂��N���b�N����
	bool isMissFlag = false;
	// �Ԉ�������̂��N���b�N�������Ƃ̐Ԕw�i���\������Ă��鎞�Ԃ̌o�ߎ��Ԃ̍��v
	float totalTime = 0.0f;
};
