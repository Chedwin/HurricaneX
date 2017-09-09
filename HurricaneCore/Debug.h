//*******************************//
//
// Name:			Debug.h
// Description:		I/O streams for debugging.
//					Opens a debug file for writing.
//
// Author:			Edwin Chen
// Special Thanks:	Scott Fielder
//
// Created:			Jan 31, 2016
// Last updated:	May 20, 2017
//
//*******************************//

#ifndef _DEBUG_H
#define _DEBUG_H

#include "Macro.h"

/// This enum is a simple 8-bit unsigned int
enum class EMessageType : unsigned short {
	INFO = 0,
	WARNING,
	ERR,
	FATAL_ERR
};

class Debug {
private:
	/// New in C++ 11: this deletes the automatic constructor from being formed if no other constructor is decleared 
	Debug() = delete;

	/// Let's kill any default constructors the complier makes for us
	Debug(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator=(const Debug&) = delete;
	Debug& operator=(Debug&&) = delete;

public:
	static void Init();

	// File I/O
	static void Log(const EMessageType MsgType, const STRING& comments);
	static void Log(const EMessageType MsgType, const STRING& Class, const STRING& Method, const STRING& timestamp, const STRING& file, const int& line, const STRING& comments);

	// Standard console logging 
	static void ConsoleLog(const STRING& _msg);
	static void ConsoleLog(float _msg);
	static void ConsoleLog(int _msg);
	static void ConsoleLog(double _msg);
	static void ConsoleLog(const char* _msg);
	
	// Error console logging
	static void ConsoleError(const STRING& _msg);
	static void ConsoleError(float _msg);
	static void ConsoleError(int _msg);
	static void ConsoleError(double _msg);
	static void ConsoleError(const char* _msg);
};


#endif