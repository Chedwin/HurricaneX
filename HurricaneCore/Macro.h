//*******************************//
//
// Name:			Macro.h
// Description:		Macro defines all the types and keys in Hurricane
//					Most of them are std macros
//					Include this header to access any external dependencies provided by the system
//					A general goal of this header file to avoid some dependencies being repeadily loaded into the compiler
//
// Author:			Edwin Chen
// Created:			Apr 05, 2016
// Last updated:	Nov 06, 2017
//
//*******************************//

#ifndef _MACRO_H
#define _MACRO_H

////// WINDOWS STUFF /////
#define WIN32_LEAN_AND_MEAN // only include Win32 stuff we need (no networking, etc.)

#pragma region INCLUDE SYSTEM HEADERS

// Windows
#include <Windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>


/////// Include files ///////
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

#include <sstream>
#include <cstddef>

#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>

#include <memory>
#include <algorithm>

#include <cassert>
#include <iterator>

#include <time.h>

#include <typeinfo>

#include <functional>

#include <mmsystem.h>

#include <chrono>

#pragma endregion

/////////////////////////////////////////////////////////////////////////

#pragma region MACRO DEFINES & METHODS

// iostream
#define COUT std::cout
#define CIN  std::cin
#define ENDL std::endl
#define CERR std::cerr

#define STOI std::stoi // string to int
#define STOF std::stof // string to float

// pair
#define PAIR(A, B) std::pair<A, B>

// ofstream
#define OFSTREAM std::ofstream
// ifstream
#define IFSTREAM std::ifstream

// getline
#define GETLINE std::getline

// string
#define STRING std::string
// to_string conversion
#define TO_STRING(A) std::to_string(A)

// ios
#define IOS std::ios


// stdio.h
#define PRINTF std::printf
#define GETCHAR std::getchar

// sstream
#define STRINGSTREAM std::stringstream 

// WSTRING
#define WSTRING std::wstring

// functional
#define FUNCTION(U) std::function<U>

// list
#define LIST(T) std::list<T>
// vector
#define VECTOR(X) std::vector<X>
// stack
#define STACK(P) std::stack<P>
// queue
#define QUEUE(L) std::queue<L>
// map
#define MAP(K, V) std::map<K, V>
// unordered map
#define UNORDERED_MAP(N, M) std::unordered_map<N, M>


// memory - smart pointers
#define UNIQUE_PTR(A)		std::unique_ptr<A>
#define SHARED_PTR(B)		std::shared_ptr<B>
#define DEFAULT_DELETE(C)	std::default_delete<C>
#define WEAK_PTR(D)			std::weak_ptr<D>
#define MAKE_UNIQUE(E)		std::make_unique<E>

#pragma endregion

/////////////////////////////////////////////////////////////////////////

#pragma region CUSTOM MACRO DEFINE FUNCTIONS

#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }
#define SHOWERROR(s,f,l) char buf[1024]; sprintf( buf, "File: %s\nLine: %d\n%s",f,l,s); MessageBox( 0, buf, "Error", 0 );

#pragma endregion

/////////////////////////////////////////////////////////////////////////
#endif // _MACRO_H