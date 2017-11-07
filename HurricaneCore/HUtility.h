//*******************************//
//
// Name:			HUtility.h
// Description:		Static utility class mainly for template comparison operations
//					Types used must be COMPARABLE 
//						(w/ appropriate overloaded operators)
//
// Author:			Edwin Chen
// Special Thanks:	 
//
// Created:			Nov 05, 2017
// Last updated:	Nov 06, 2017
//
//*******************************//

#ifndef _H_UTILITY_H
#define _H_UTILITY_H

#include "Macro.h"
#include "Debugger.h"

namespace HurricaneEngine 
{
	class HUtility {
	private:
		HUtility() {}
		~HUtility() {}
	public:

		// InRange() - Inclusive
		// Specify a type T variable w/ min and max boundaries to test if T is in bounds
		template<typename T> 
		static bool InRange(const T& _data, const T& _min, const T& _max) 
		{
			if (_min > _max) 
			{
				Debugger::Error("Supplied Min is greater than Max");
				return false;
			}

			bool min = (_min  <= _data);
			bool max = (_data <= _max);

			if (min && max)
				return true;

			return false;
		}
		
		// Max()
		template<typename T>
		static const T& Max(const T& _A, const T& _B)
		{
			return (_A > _B) ? _A : _B;
		}

		// Min()
		template<typename T>
		static const T& Min(const T& _A, const T& _B)
		{
			return (_A < _B) ? _A : _B;
		}

		// Swap()
		template<typename T>
		static void Swap(T& _A, T& _B)
		{
			T temp = _B;
			_B = _A;
			_A = temp;
		}

		// Convert LPCWSTR to std::string
		//static const STRING& ConvertToString(const LPCWSTR& _text)
		//{
		//	const int BUFFER_SIZE = 128;
		//	char* c = (char *)malloc(BUFFER_SIZE);
		//	size_t t;
		//	wcstombs_s(&t, c, (size_t)BUFFER_SIZE, (const wchar_t*)_text, (size_t)BUFFER_SIZE);
		//	const STRING& temp = STRING(c);

		//	if (c)
		//		free(c);

		//	return temp;
		//}

	};

} // end namespace HurricaneEngine

#endif