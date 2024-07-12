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
	//インスタンス取得
	static UIManager& Instance()
	{
		static UIManager instance;
		return instance;
	}

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render();

	//UI全クリア
	void Clear();

	//UI取得
	UI* GetUI(int index) { return uies.at(index); }

	//UI削除
	void Remove(UI* ui);

	//UI登録
	void UIRegister(UI* ui);


private:
	std::vector<UI*>uies;
	std::set<UI*>removes;
};