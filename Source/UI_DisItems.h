#pragma once

#include "UI.h"

//���㌩�������̗�UI
//DisItems��Discovered Items�F����������
class DisItems :public UI
{
public:

	//DisItems() {};
	DisItems() {};
	~DisItems()override {};

	//������
	void Initialize() override;

	//�I����
	void Finalize() override;

	//�X�V����
	void Update(float elapsedTime) override;

	//�`�揈��
	void Render() override;

	//�A�j���[�V�����Đ�
	void Play(int index);
//	bool IsFinish() const { return isPushLeftButtonFlag && !isPlay; }
	
	// �g��J�n�̊֐�
	void StartScaling(int index, float t);


	struct LoadImage
	{
		const char* filename;
		float tx, ty;
	};



	int stageNo;



private:
	Sprite* spr = nullptr;
	Sprite* spr_flame = nullptr;
	//Sprite* spr_obj = nullptr;


	struct Object
	{
		DirectX::XMFLOAT3		scale_velocity = { 0,0,0 };
		DirectX::XMFLOAT3		position = { 0,0,0 };
		DirectX::XMFLOAT3		angle = { 0,0,0 };
		DirectX::XMFLOAT3		scale = { 0,0,0 };
		bool	exist = true;
		bool	isPlay = false;

		Sprite* spr_obj = nullptr;
		float tx, ty;
	};
	Object		objs[5];
	


	// �k���W���i����d�͂ɂ��Ă���j
	float gravity = -0.2f;

	// �X�P�[�����O�̍Œ�l
	float minScaling = 0.5f;

	// true...�{�^���������ꂽ
//	bool isPushLeftButtonFlag = false;
//	bool isPlay = false;
};