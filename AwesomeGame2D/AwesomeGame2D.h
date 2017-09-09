#pragma once
#include <Debug.h>
#include <HXApp.h>
#include <Component.h>
#include <MeshComponent.h>
#include <GameObject.h>

#include <GameObjectScript.h>

class myScript : public GameObjectScript {
public:
	explicit myScript(const STRING& name) : GameObjectScript(name) 
	{
		Debug::ConsoleLog("WHAT ARE YOU LOOKING AT MOTHERFUCKER?");
	}

	~myScript() {}

	bool UpdateScript(GameObject* gameObject, const float _timeStep) final {
		//Debug::ConsoleLog("WUBBA LUBBA DUB DUB!!!!!!!!!!!!");
		return true;
	}
};

class AwesomeGame2D : public HXApp {
public:
	AwesomeGame2D() 
		: HXApp(), myModel(nullptr)
	{
		HXApp::_hXAppInstance = this;
	}

	~AwesomeGame2D() {
		if (myModel)
			delete myModel;

		myModel = nullptr;
	}

	bool InitGame() final {
		myModel = new GameObject("FreakinTriangle");
		
		myScript* getSwifty = new myScript("getSwifty");

		myModel->AddScript(getSwifty);

		//myScript* copy = myModel->GetScript<myScript>();
		MeshComponent* h = new MeshComponent(myModel, _graphics->GetDevice());

		MeshComponent* copy = myModel->GetComponent<MeshComponent>();

		if (copy)
			Debug::ConsoleLog("FIRST TRY!!!!!!!!!!");

		return true;
	}
	void Update(const float _dt) override {
		myModel->Update(_dt);
		return;
	}
	void Render(const float _dt) final {
		return;
	}

public:
	GameObject* myModel;
};
