#ifndef _UTILITY_H
#define _UTILITY_H

static class Utility {
public:
	static void ReleaseCom(ComObject& x) {
		if (x != null) {
			x.Dispose();
			x = null;
		}
	}
	static int LowWord(this int i) {
		return i & 0xFFFF;
	}
	static int HighWord(this int i) {
		return (i >> 16) & 0xFFFF;
	}
};

#endif