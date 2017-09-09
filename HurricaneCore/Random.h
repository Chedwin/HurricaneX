//*******************************//
//
// Name:			Random.h
// Description:		Generate random floating pointing numbers if required.
//
// Authors:			Mathieu Violette
//					James Sholdice
//					Nathan Senter
//
// Created:			Apr 19, 2016
// Last updated:	Sep 08, 2017
//
//*******************************//


#ifndef _RANDOM_H
#define _RANDOM_H

#include "Macro.h"

class Random {
private:
	static int		seed;
	static long		ran1idnum;
	static int		qd2idnum;
public:
	Random();
	~Random();

	static double	rand(double low, double high);
	static int		rand(int low, int high);
	static double	ran1();
	static float	box_muller(float m, float s);

	static inline double ranqd2() {
		unsigned long itemp;
		static unsigned long jflone = 0x3f800000;
		static unsigned long jflmsk = 0x007fffff;

		qd2idnum = 1664525L * qd2idnum + 1013904223L;
		itemp = jflone | (jflmsk & qd2idnum);
		return (double)(*(float*)&itemp) - 1.0;
	}

};


#endif