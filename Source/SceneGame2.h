#pragma once

#include "Player.h"
#include "CameraController.h"
#include "Scene.h"
#include "Graphics/Sprite.h"
#include "stageMain2.h"
#include "UI_DisItems.h"
#include <Audio/AudioSource.h>
#include <vector>

// �Q�[���V�[��
class SceneGame2 :public Scene
{
public:
	SceneGame2() {}
	~SceneGame2() override {}

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
	StageMain2* stageMain2;

	Effect* maru = nullptr;
	Effect* batu = nullptr;

	Sprite* aka = nullptr;

	DisItems* disItems = nullptr;
	//int game_timer = 0;

	std::unique_ptr<AudioSource>	BGM_House;
	std::unique_ptr<AudioSource>	SE_yes;
	std::unique_ptr<AudioSource>	SE_not;

	// true...�Ԉ�������̂��N���b�N����
	bool isMissFlag = false;
	// �Ԉ�������̂��N���b�N�������Ƃ̐Ԕw�i���\������Ă��鎞�Ԃ̌o�ߎ��Ԃ̍��v
	float totalTime = 0.0f;

	// �`�F�b�N���� StageFind �̃C���f�b�N�X���X�g
	std::vector<int> m_checkList;

	// �`�F�b�N���鐔�i���ꂪ�K�v���B������N���A�j
	int checkCount = 0;

protected:
	DirectX::XMFLOAT3 scale = { 1,1,1 };
};
