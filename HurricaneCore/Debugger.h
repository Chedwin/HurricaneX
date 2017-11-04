//*******************************//
//
// Name:			Debugger.h
// Description:		I/O streams for debugging.
//					Opens a debug file for writing.
//
// Author:			Edwin Chen
// Special Thanks:	Scott Fielder
//
// Created:			Jan 31, 2016
// Last updated:	Oct 31, 2017
//
//*******************************//

#ifndef _DEBUGGER_H
#define _DEBUGGER_H

#include "Macro.h"

namespace HurricaneEngine
{

	/// This enum is a simple 8-bit unsigned int
	enum class EMessageType : unsigned short {
		INFO = 0,
		WARNING,
		ERR,
		FATAL_ERR
	};

	class Debugger {
	private:
		/// New in C++ 11: this deletes the automatic constructor from being formed if no other constructor is decleared 
		Debugger() = delete;

		/// Let's kill any default constructors the complier makes for us
		Debugger(const Debugger&) = delete;
		Debugger(Debugger&&) = delete;
		Debugger& operator=(const Debugger&) = delete;
		Debugger& operator=(Debugger&&) = delete;

	public:
		static void Init();

		// File I/O
		static void DocumentLog(const EMessageType MsgType, const STRING& comments);
		static void DocumentLog(const EMessageType MsgType, const STRING& Class, const STRING& Method, const STRING& timestamp, const STRING& file, const int& line, const STRING& comments);

		// Standard console logging 
		static void Log(const STRING& _msg);
		static void Log(float _msg);
		static void Log(int _msg);
		static void Log(double _msg);
		static void Log(const char* _msg);

		// Error console logging
		static void Error(const STRING& _msg);
		static void Error(float _msg);
		static void Error(int _msg);
		static void Error(double _msg);
		static void Error(const char* _msg);
	};

} // end namespace Hurricane

#endif