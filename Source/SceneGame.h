#pragma once


#include "Player.h"
#include "CameraController.h"
#include "Scene.h"
#include "Graphics/Sprite.h"
#include "stageMain.h"
#include "UI_Clock.h"
#include "UI_DisItems.h"
#include "Audio/Audio.h"
#include <vector>

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
	
	Clock* clock = nullptr;
	DisItems* disItems = nullptr;
	//int game_timer = 0;

	std::unique_ptr<AudioSource>	BGM_Sea;

	// true...�Ԉ�������̂��N���b�N����
	bool isMissFlag = false;
	// �Ԉ�������̂��N���b�N�������Ƃ̐Ԕw�i���\������Ă��鎞�Ԃ̌o�ߎ��Ԃ̍��v
	float totalTime = 0.0f;

	int delItem = -1;

	// �`�F�b�N���� StageFind �̃C���f�b�N�X���X�g
	std::vector<int> m_checkList;

	// �`�F�b�N���鐔�i���ꂪ�K�v���B������N���A�j
	int checkCount = 0;

private:
	enum DisItemNum
	{
		ObjNone = -1,
		Obj0,
		Obj1,
		Obj2,
		Obj3,
		Obj4,
		Obj5
	};
protected:
	DirectX::XMFLOAT3 scale = { 1,1,1 };
};
