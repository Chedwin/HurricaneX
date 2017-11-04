#ifndef _IGAMESTATE_H
#define _IGAMESTATE_H

#include "Macro.h"
#include "IState.h"

namespace HurricaneEngine 
{
	class IHGame;

	enum class ScreenState {
		NONE,
		RUNNING,
		EXIT_APPLICATION,
		CHANGE_NEXT,
		CHANGE_PREVIOUS
	};

	class IGameScreen {
	protected:
		STRING _screenName;
		IHGame* _mainGame = nullptr;

	public:
		IGameScreen(IHGame* _hg) { setParentGame(_hg); }
		virtual ~IGameScreen() {}

		// Called at beginning and end of application
		virtual void Build() = 0;
		virtual void Destroy() = 0;

		// Called when a screen enters and exits focus
		virtual void OnEntry() = 0;
		virtual void OnExit() = 0;

		virtual void Update(const float _deltaTime) = 0;
		virtual void Render() = 0;

		/// Sets m_game to the parent game
		inline void setParentGame(IHGame* game) {
			_mainGame = game;
		}

		inline void SetScreenName(const STRING& _n) {
			_screenName = _n;
		}
	
	};

}

#endif