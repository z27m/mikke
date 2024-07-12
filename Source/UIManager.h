#pragma once

#include <vector>
#include <set>
#include "Graphics/Shader.h"
#include "UI.h"

class UIManager
{
private:
	UIManager() {};
	~UIManager() {};

public:
	//�C���X�^���X�擾
	static UIManager& Instance()
	{
		static UIManager instance;
		return instance;
	}

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render();

	//UI�S�N���A
	void Clear();

	//UI�擾
	UI* GetUI(int index) { return uies.at(index); }

	//UI�폜
	void Remove(UI* ui);

	//UI�o�^
	void UIRegister(UI* ui);


private:
	std::vector<UI*>uies;
	std::set<UI*>removes;
};