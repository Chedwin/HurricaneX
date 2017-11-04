#pragma once

#include <Macro.h>
#include <IHGame.h>


class TestGame : public HurricaneEngine::IHGame {
	friend DEFAULT_DELETE(TestGame);
protected:
	static UNIQUE_PTR(TestGame) _instance;

protected:
	TestGame();
	~TestGame() final;

	bool InitGame() final;
	void Update(const float _deltaTime) override;
	void OnExit()   final;

public:
	static TestGame* GetInstance();
};
