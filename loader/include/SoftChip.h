/*******************************************************************************
 * SoftChip.h
 *
 * Copyright (c) 2009 Requiem (requiem@century-os.com)
 *
 * Distributed under the terms of the GNU General Public License (v3)
 * See http://www.gnu.org/licenses/gpl-3.0.txt for more info.
 *
 * Description:
 * -----------
 *
 ******************************************************************************/

#pragma once

//--------------------------------------
// Includes

//#include <ogcsys.h>
#include <ogc/ios.h>
#include <ogc/isfs.h>
#include <ogc/video.h>
#include <ogc/system.h>
#include <ogc/consol.h>
#include <ogc/ios.h>
#include <ogc/es.h>
#include <ogc/ipc.h>
#include <ogc/stm.h>
#include <ogc/color.h>
#include <ogc/cache.h>
#include <ogc/conf.h>
#include <ogc/consol.h>
#include <ogc/dvd.h>

#include "DIP.h"
#include "Input.h"
#include "Console.h"
#include "Storage.h"
#include "Configuration.h"
#include "Logger.h"

#define Phase_IOS				0
#define Phase_Menu				1
#define Phase_SelectIOS			2
#define Phase_Play				3
#define Phase_Show_Disclaimer	4

//--------------------------------------
// SoftChip Class

class SoftChip
{
protected:
	DIP*			DI;						// DIP interface
	Input*			Controls;				// Input
	Console*		Out;					// Console
	Configuration*	Cfg;					// Configuration
	Logger*			Log;					// Logger
	Storage*		SD;						// Storage

	// -- Logic
	int				NextPhase;				// Logic Step
	bool			Skip_AutoBoot;			// Force Menu
	dword			Cursor_IOS;				// IOS Position in Console
	dword			Cursor_Menu;			// Menu Position in Console
	// -- Flags
	bool			Standby_Flag;			// Flag is set when power button is pressed
	bool			Reset_Flag;				// Flag is set when reset button is pressed
	// -- Video
	GXRModeObj*		vmode;					// System Video Mode
	unsigned int	Video_Mode;				// System Video Mode (NTSC, PAL or MPAL)	
	void*			framebuffer;			// Framebuffer
	// -- IOS
	int				IOS_Version;			// Loaded IOS Version
	bool			IOS_Loaded;				// IOS Ok?	

public:
	void Run();							// Main Function

private:
	static void Standby();				// Put the console into standby
	static void Reboot();				// Return to system menu
	void VerifyFlags();					// Verify if the flags are set
	void Exit_Loader();					// Return to Loader or System Menu

	void	Load_IOS();												// Load the IOS
	void	Show_Menu();											// Show the Main Menu
	void	Show_IOSMenu();											// Show the Menu for selecting IOS
	void 	Load_Disc();											// Loads the disc
	void 	Determine_VideoMode(char Region);						// Determines which video mode to use based on current system settings
	void	Set_VideoMode();										// Set Video Mode
	bool	Set_GameLanguage(void *Address, int Size, char Region);// Patch Game's Language
	bool	Remove_002_Protection(void *Address, int Size);			// Remove the 002 protection
	bool	Patch_Country_Strings(void *Address, int Size, char discregion);

protected:
	SoftChip();
	SoftChip(const SoftChip&);
	SoftChip& operator= (const SoftChip&);

	virtual ~SoftChip();

public:
	inline static SoftChip* Instance()
	{
		static SoftChip instance;
		return &instance;
	}
};
