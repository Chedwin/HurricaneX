#ifndef _LEVEL_H
#define _LEVEL_H


class Level {
public:
	bool isLoading = false;

public:
	Level() {}
	virtual ~Level() {}

	virtual void Load()   = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
};

#endif