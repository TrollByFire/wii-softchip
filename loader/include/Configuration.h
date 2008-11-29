/*******************************************************************************
 * Configuration.h
 *
 * Copyright (c) 2008 SoftChip Team
 *
 * Distributed under the terms of the GNU General Public License (v3)
 * See http://www.gnu.org/licenses/gpl-3.0.txt for more info.
 *
 * Description:
 * -----------
 *	Contains definition of a class to load config from SD
 *
 ******************************************************************************/

#pragma once

//--------------------------------------
// Includes

#include <stdio.h>
#include <sys/dir.h>

#include "Memory_Map.h"

#define Default_IOS 36

//--------------------------------------
// ConfigData

namespace ConfigData
{
	const byte LastVersion = 2;
	const char Signature[] = "B5662343D78AD6D";
	const char DefaultFolder[] = "/SoftChip";
	const char DefaultFile[] = "/SoftChip/Default.cfg";

	struct Ver2
	{
		char		IOS;
		signed char	Language;
		bool		SysVMode;
		bool		AutoBoot;
		bool		Silent;
		bool		Logging;
	} __attribute__((packed));

	struct Ver1
	{
		char		IOS;
		signed char	Language;
		bool		SysVMode;
		bool		AutoBoot;
	} __attribute__((packed));
}

//--------------------------------------
// Default Configuration Class

class Configuration
{
public:
	bool CreateFolder(const char* Path);
	bool Read(const char* Path);
	bool Save(const char* Path);

	ConfigData::Ver2 Data;

protected:
	virtual bool Parse(FILE *fp);

	Configuration();
	Configuration(const Configuration&);
	Configuration& operator= (const Configuration&);

	virtual ~Configuration();

public:
	inline static Configuration* Instance()
	{
		static Configuration instance;
		return &instance;
	}
};

//--------------------------------------
// Derived Configurations

class ConfigVer2 : public Configuration
{
protected:
	bool Parse(FILE *fp);
};

class ConfigVer1 : public Configuration
{
protected:
	bool Parse(FILE *fp);
};

