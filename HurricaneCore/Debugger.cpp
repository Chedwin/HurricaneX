#include "Debugger.h"

using namespace HurricaneEngine;

void Debugger::Init() {
	OFSTREAM out;

	// During this Init, we're going to either:
	// 1) Create "Log.txt" if it doesn't already exist, or
	// 2) Append to it if it exist
	out.open("Debugger.txt", IOS::app | IOS::out);

	out.close();
}




void Debugger::DocumentLog(const EMessageType MsgType, const STRING& comments)
{
	std::ofstream out;
	out.open("Debugger.txt", IOS::app); // this will either create a new debug file or append to it

	switch (MsgType) {
	case EMessageType::INFO:
		out << "INFO: " << comments << ENDL;
		break;
	case EMessageType::WARNING:
		out << "WARNING: " << comments << ENDL;
		break;
	case EMessageType::ERR:
		out << "ERROR: " << comments << ENDL;
		break;
	case EMessageType::FATAL_ERR:
		out << "FATAL ERROR: " << comments << ENDL;
		break;
	}

	out.close(); // close the debug file
}

void Debugger::DocumentLog(const EMessageType MsgType, const STRING & Class, const STRING & Method, const STRING & timestamp, const STRING & file, const int & line, const STRING & comments)
{
	std::ofstream out;
	out.open("DebugLog.txt", IOS::app); // this will either create a new debug file or append to it

	switch (MsgType) {
	case EMessageType::INFO:
		out << timestamp << file << line << ENDL << "INFO: " << Class << "::" << Method << "()" << ENDL << "Notes: " << comments << ENDL << ENDL;
		break;
	case EMessageType::WARNING:
		out << timestamp << file << line << ENDL << "WARNING: " << Class << "::" << Method << "()" << ENDL << "Notes: " << comments << ENDL << ENDL;
		break;
	case EMessageType::ERR:
		out << timestamp << file << line << ENDL << "ERROR: " << Class << "::" << Method << "()" << ENDL << "Notes: " << comments << ENDL << ENDL;
		break;
	case EMessageType::FATAL_ERR:
		out << timestamp << file << line << ENDL << "FATAL ERROR: " << Class << "::" << Method << "()" << ENDL << "Notes: " << comments << ENDL << ENDL;
		break;
	}

	out.close(); // close the debug file
}


////////////////////////////////////////////////////////////////////////

void Debugger::Log(const STRING& _msg)
{
	//  application
	COUT << _msg << ENDL;
}

void Debugger::Log(float _msg)
{
	COUT << _msg << ENDL;
}

void Debugger::Log(int _msg)
{
	COUT << _msg << ENDL;
}

void Debugger::Log(double _msg)
{
	COUT << _msg << ENDL;
}

void Debugger::Log(const char* _msg)
{
	COUT << _msg << ENDL;
}


////////////////////////////////////////////////////////////////////////

void Debugger::Error(const STRING& _msg)
{
	//  application
	CERR << "ERROR: " << _msg << ENDL;
}

void Debugger::Error(float _msg)
{
	CERR << "ERROR: " << _msg << ENDL;
}

void Debugger::Error(int _msg)
{
	CERR << "ERROR: " << _msg << ENDL;
}

void Debugger::Error(double _msg)
{
	CERR << "ERROR: " << _msg << ENDL;
}

void Debugger::Error(const char* _msg)
{
	CERR << "ERROR: " << _msg << ENDL;
}
