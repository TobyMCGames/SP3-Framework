#pragma once
#include "SingletonPattern.h"

class CLogRoot : public SingletonPattern<CLogRoot>
{
	friend SingletonPattern<CLogRoot>;
public:

	// File information
	char* logl_root;	// Root directory for loading digital assets;
protected:

	CLogRoot(void);
	~CLogRoot(void);
};