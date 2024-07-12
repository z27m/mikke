#pragma once

#include <Graphics/Sprite.h>

class UI
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	UI() {}
	virtual ~UI() {}
	
	// ������
	virtual void Initialize() = 0;

	// �I����
	virtual void Finalize() = 0;

	// �X�V����
	virtual void Update(float elapsedTime) = 0;

	// �`�揈��
	virtual void Render() = 0;



private:
	Sprite* clock = nullptr;


	//std::vector<Sprite*>
};