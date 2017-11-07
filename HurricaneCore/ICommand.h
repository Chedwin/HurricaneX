//*******************************//
//
// Name:			ICommand.h
// Description:		
//
// Author:			Edwin Chen
// Special Thanks:	 
//
// Created:			Nov 06, 2017
// Last updated:	Nov 06, 2017
//
//*******************************//


#ifndef _ICOMMAND_H
#define _ICOMMAND_H

#include "Macro.h"

namespace HurricaneEngine 
{
	class ICommand {
	protected:
		FUNCTION(void) _execFunc;

	public:
		ICommand() {}
		virtual ~ICommand() = 0;

		void Execute() 
		{
			//if (_execFunc)
			//	_execFunc;
		}

		void SetExecFunc(const FUNCTION(void)& _func) 
		{
			_execFunc = nullptr;
			_execFunc = _func;
		}
	};

} // end namespace HurricaneEngine

#endif 