#include "UIManager.h"

void UIManager::Update(float elapsedTime)
{
	for (UI* ui : uies)
	{
		ui->Update(elapsedTime);
	}

	//”pŠüˆ—
	for (UI* ui : removes)
	{
		std::vector<UI*>::iterator it = std::find(uies.begin(), uies.end(), ui);
		if (it != uies.end())
		{
			uies.erase(it);
		}
		ui->Finalize();
		delete ui;
	}
	removes.clear();
}

void UIManager::Render()
{
	for (UI* ui : uies)
	{
		ui->Render();
	}
}

void UIManager::UIRegister(UI* ui)
{
	uies.emplace_back(ui);
}

void UIManager::Clear()
{
	for (UI* ui : uies)
	{
		ui->Finalize();
		delete ui;
	}
	uies.clear();
}

void UIManager::Remove(UI* ui)
{
	removes.insert(ui);
}