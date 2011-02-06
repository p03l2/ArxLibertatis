/*
===========================================================================
ARX FATALIS GPL Source Code
Copyright (C) 1999-2010 Arkane Studios SA, a ZeniMax Media company.

This file is part of the Arx Fatalis GPL Source Code ('Arx Fatalis Source Code'). 

Arx Fatalis Source Code is free software: you can redistribute it and/or modify it under the terms of the GNU General Public 
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Arx Fatalis Source Code is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Arx Fatalis Source Code.  If not, see 
<http://www.gnu.org/licenses/>.

In addition, the Arx Fatalis Source Code is also subject to certain additional terms. You should have received a copy of these 
additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Arx 
Fatalis Source Code. If not, please request a copy in writing from Arkane Studios at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing Arkane Studios, c/o 
ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.
===========================================================================
*/
//////////////////////////////////////////////////////////////////////////////////////
//   @@        @@@        @@@                @@                           @@@@@     //
//   @@@       @@@@@@     @@@     @@        @@@@                         @@@  @@@   //
//   @@@       @@@@@@@    @@@    @@@@       @@@@      @@                @@@@        //
//   @@@       @@  @@@@   @@@  @@@@@       @@@@@@     @@@               @@@         //
//  @@@@@      @@  @@@@   @@@ @@@@@        @@@@@@@    @@@            @  @@@         //
//  @@@@@      @@  @@@@  @@@@@@@@         @@@@ @@@    @@@@@         @@ @@@@@@@      //
//  @@ @@@     @@  @@@@  @@@@@@@          @@@  @@@    @@@@@@        @@ @@@@         //
// @@@ @@@    @@@ @@@@   @@@@@            @@@@@@@@@   @@@@@@@      @@@ @@@@         //
// @@@ @@@@   @@@@@@@    @@@@@@           @@@  @@@@   @@@ @@@      @@@ @@@@         //
// @@@@@@@@   @@@@@      @@@@@@@@@@      @@@    @@@   @@@  @@@    @@@  @@@@@        //
// @@@  @@@@  @@@@       @@@  @@@@@@@    @@@    @@@   @@@@  @@@  @@@@  @@@@@        //
//@@@   @@@@  @@@@@      @@@      @@@@@@ @@     @@@   @@@@   @@@@@@@    @@@@@ @@@@@ //
//@@@   @@@@@ @@@@@     @@@@        @@@  @@      @@   @@@@   @@@@@@@    @@@@@@@@@   //
//@@@    @@@@ @@@@@@@   @@@@             @@      @@   @@@@    @@@@@      @@@@@      //
//@@@    @@@@ @@@@@@@   @@@@             @@      @@   @@@@    @@@@@       @@        //
//@@@    @@@  @@@ @@@@@                          @@            @@@                  //
//            @@@ @@@                           @@             @@        STUDIOS    //
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
// ARX_Menu
//////////////////////////////////////////////////////////////////////////////////////
//
// Description:
//		ARX Menu Management
//
// Updates: (date) (person) (update)
//
// Code: Cyril Meynier
//
// Copyright (c) 1999-2000 ARKANE Studios SA. All rights reserved
//////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdlib.h>
#include <fstream>

#include "gui/Menu.h"
#include "scene/ChangeLevel.h"
#include "scene/GameSound.h"
#include "graphics/particle/Particle.h"
#include "graphics/particle/ParticleManager.h"
#include "graphics/particle/ParticleParams.h"
#include "core/Localization.h"
#include "gui/MenuWidgets.h"
#include "gui/Text.h"
#include "core/Time.h"
#include "game/Equipment.h"
#include "scene/LoadLevel.h"
#include "gui/ViewImage.h"

#include "core/Application.h"
#include "graphics/Draw.h"
#include "graphics/Math.h"
#include "scene/Object.h"

#include "io/IO.h"
#include "io/PakManager.h"

//-----------------------------------------------------------------------------
extern TextManager * pTextManage;
extern CDirectInput * pGetInfoDirectInput;
extern CMenuConfig * pMenuConfig;
extern EERIE_3D ePlayerAngle;
extern float Xratio, Yratio;
extern long Book_Mode;
extern long GAME_EDITOR;
extern long START_NEW_QUEST;
extern long INTRO_NOT_LOADED;
extern long LASTBOOKBUTTON;
extern long BOOKBUTTON;
extern long OLD_FLYING_OVER;
extern long FINAL_RELEASE;
extern long FLYING_OVER;
extern long BOOKZOOM;
extern long FRAME_COUNT;
extern float ARXTimeMenu;
extern float ARXOldTimeMenu;
extern long NEED_SPECIAL_RENDEREND;
extern bool bFadeInOut;
extern bool bFade;
extern int iFadeAction;
extern float fFadeInOut;
extern char SKIN_MOD;
extern char QUICK_MOD;

extern float PROGRESS_BAR_TOTAL;
extern float OLD_PROGRESS_BAR_COUNT;
extern float PROGRESS_BAR_COUNT;

extern float ARXTimeMenu;
extern float ARXOldTimeMenu;
extern float ARXDiffTimeMenu;

extern TextureContainer * pTextureLoad;


bool bQuickGenFirstClick = true;
ARX_MENU_DATA ARXmenu;
long ARXmenu_lastmode = -1;
long REFUSE_GAME_RETURN = 0;
unsigned long ARXmenu_starttick = 0;

extern bool bRenderInterList;
long SP_HEAD = 0;
//-----------------------------------------------------------------------------
bool MENU_NoActiveWindow();
void ClearGame();
void ClearGameDEVICE();

//-----------------------------------------------------------------------------
void ARX_Menu_Release_Text(void * a)
{
	if (a)
	{
		free(a);
		a = NULL;
	}
}

//-----------------------------------------------------------------------------
#define ARX_MENU_SIZE_Y 24

 
long save_c(0), save_p(0);
std::vector<SaveGame> save_l;

//-----------------------------------------------------------------------------
void CreateSaveGameList()
{
	char path[512] = "";
	HANDLE h;

	sprintf(path, "save%s\\save*", LOCAL_SAVENAME);

	save_l.resize( save_l.size() + 1 );

	save_l[0].name = "New";
	save_c = 1;

	char tTemp[sizeof(WIN32_FIND_DATA)+2];
	WIN32_FIND_DATA * fdata = (WIN32_FIND_DATA *)tTemp;

	if ((h = FindFirstFile(path, fdata)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (fdata->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && fdata->cFileName[0] != '.')
			{
				// Make another save game slot at the end
				save_l.resize( save_l.size() +1 );

				std::string text = fdata->cFileName + 4;
				save_l[save_c].num = atoi(text.c_str());
				std::stringstream ss;
				ss << "save" << LOCAL_SAVENAME << "\\" << fdata->cFileName << "\\";
				text = ss.str();
				//sprintf(text, "%ssave%s\\%s\\", Project.workingdir, LOCAL_SAVENAME, fdata->cFileName);
				unsigned long pouet;

				if (ARX_CHANGELEVEL_GetInfo(text, save_l[save_c].name, save_l[save_c].version, save_l[save_c].level, pouet) != -1)
				{
					SYSTEMTIME stime;
					FILETIME fTime;
					FileTimeToLocalFileTime(&fdata->ftLastWriteTime, &fTime);
					FileTimeToSystemTime(&fTime, &stime);
					save_l[save_c].stime = stime;

					save_c++;
				}
			}
		}
		while (FindNextFile(h, fdata));

		FindClose(h);
	}
}

//-----------------------------------------------------------------------------
void FreeSaveGameList()
{
	save_l.clear();
	save_c = 0;
	save_p = 0;
}

//-----------------------------------------------------------------------------
void UpdateSaveGame(const long & i)
{

	//i == 0 -> new save game
	//i >  0 -> erase old savegame save_l[i].name
	if (i <= 0) ARX_CHANGELEVEL_Save(i, save_l[0].name);
	else
	{
		ARX_CHANGELEVEL_Save(save_l[i].num, save_l[i].name);
	}
}

//-----------------------------------------------------------------------------
void ARX_MENU_CLICKSOUND()
{
	ARX_SOUND_PlayMenu(SND_MENU_CLICK);
}

//-----------------------------------------------------------------------------
void LoadSaveGame(const long & i)
{
	ARX_MENU_CLICKSOUND();
	INTRO_NOT_LOADED = 1;
	LoadLevelScreen();	
	PROGRESS_BAR_TOTAL = 238;
	OLD_PROGRESS_BAR_COUNT = PROGRESS_BAR_COUNT = 0;
	PROGRESS_BAR_COUNT += 1.f;
	LoadLevelScreen(GDevice, save_l[i].level);
	DanaeClearLevel();
	ARX_CHANGELEVEL_Load(save_l[i].num);
	REFUSE_GAME_RETURN = 0;
	NEED_SPECIAL_RENDEREND = 1;
	ARX_MENU_Clicked_QUIT();
}

//-----------------------------------------------------------------------------
// Menu Sounds
//-----------------------------------------------------------------------------

void ARX_MENU_LaunchAmb(char * _lpszAmb)
{
	ARX_SOUND_PlayMenuAmbiance(_lpszAmb);
}

//-----------------------------------------------------------------------------
void ARX_Menu_Resources_Create(LPDIRECT3DDEVICE7 m_pd3dDevice)
{
	if (ARXmenu.mda)
	{
		delete ARXmenu.mda;
		ARXmenu.mda = NULL;
	}

	ARXmenu.mda = new MENU_DYNAMIC_DATA();
	ARXmenu.mda->pTexCredits = MakeTCFromFile("Graph\\Interface\\menus\\Menu_credits.bmp");
	ARXmenu.mda->BookBackground = MakeTCFromFile("Graph\\Interface\\book\\character_sheet\\Char_creation_Bg.BMP");

	ARX_Allocate_Text(ARXmenu.mda->flyover[BOOK_STRENGTH],              "system_charsheet_strength");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BOOK_MIND],                  "system_charsheet_intel");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BOOK_DEXTERITY],             "system_charsheet_Dex");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BOOK_CONSTITUTION],          "system_charsheet_consti");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BOOK_STEALTH],               "system_charsheet_stealth");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BOOK_MECANISM],              "system_charsheet_mecanism");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BOOK_INTUITION],             "system_charsheet_intuition");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BOOK_ETHERAL_LINK],          "system_charsheet_etheral_link");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BOOK_OBJECT_KNOWLEDGE],      "system_charsheet_objknoledge");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BOOK_CASTING],               "system_charsheet_casting");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BOOK_PROJECTILE],            "system_charsheet_projectile");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BOOK_CLOSE_COMBAT],          "system_charsheet_closecombat");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BOOK_DEFENSE],               "system_charsheet_defense");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BUTTON_QUICK_GENERATION],    "system_charsheet_quickgenerate");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BUTTON_DONE],                "system_charsheet_done");
	ARX_Allocate_Text(ARXmenu.mda->flyover[BUTTON_SKIN],                "system_charsheet_skin");
	ARX_Allocate_Text(ARXmenu.mda->flyover[WND_ATTRIBUTES],             "system_charsheet_atributes");
	ARX_Allocate_Text(ARXmenu.mda->flyover[WND_SKILLS],                 "system_charsheet_skills");
	ARX_Allocate_Text(ARXmenu.mda->flyover[WND_STATUS],                 "system_charsheet_status");
	ARX_Allocate_Text(ARXmenu.mda->flyover[WND_LEVEL],                  "system_charsheet_level");
	ARX_Allocate_Text(ARXmenu.mda->flyover[WND_XP],                     "system_charsheet_xpoints");
	ARX_Allocate_Text(ARXmenu.mda->flyover[WND_HP],                     "system_charsheet_hp");
	ARX_Allocate_Text(ARXmenu.mda->flyover[WND_MANA],                   "system_charsheet_mana");
	ARX_Allocate_Text(ARXmenu.mda->flyover[WND_AC],                     "system_charsheet_AC");
	ARX_Allocate_Text(ARXmenu.mda->flyover[WND_RESIST_MAGIC],           "system_charsheet_res_magic");
	ARX_Allocate_Text(ARXmenu.mda->flyover[WND_RESIST_POISON],          "system_charsheet_res_poison");
	ARX_Allocate_Text(ARXmenu.mda->flyover[WND_DAMAGE],                 "system_charsheet_damage");

	ARX_Allocate_Text(ARXmenu.mda->str_button_quickgen,                 "system_charsheet_button_quickgen");
	ARX_Allocate_Text(ARXmenu.mda->str_button_skin,                     "system_charsheet_button_skin");
	ARX_Allocate_Text(ARXmenu.mda->str_button_done,                     "system_charsheet_button_done");

	
	char szFileName[256];
	sprintf(szFileName, "Localisation\\ucredits_%s.txt", Project.localisationpath.c_str());

	// TODO: BROKEN ACCESS OOB
	/*
	size_t siz;
	ARXmenu.mda->str_cre_credits = (_TCHAR*) PAK_FileLoadMalloc(szFileName, siz);
	if (!ARXmenu.mda->str_cre_credits.empty() && ARXmenu.mda->str_cre_credits[(siz>>1)-1] != 0)
	{
		_TCHAR * pTxt = (_TCHAR *)malloc(siz + 2);
		memcpy(pTxt, ARXmenu.mda->str_cre_credits.c_str(), siz);
		pTxt[(siz>>1)] = 0;
		ARXmenu.mda->str_cre_credits = pTxt;
	}
	*/
	ARXmenu.mda->str_cre_credits.clear();

	CreateSaveGameList();
}

//-----------------------------------------------------------------------------
void ARX_Menu_Resources_Release(bool _bNoSound)
{
	if (pMenuConfig)
		pMenuConfig->SaveAll();

	if (ARXmenu.mda == NULL)
		return;

	if (ARXmenu.mda->Background != NULL)
	{
		D3DTextr_KillTexture(ARXmenu.mda->Background);
		ARXmenu.mda->Background = NULL;
	}

	if (ARXmenu.mda->BookBackground != NULL)
	{
		D3DTextr_KillTexture(ARXmenu.mda->BookBackground);
		ARXmenu.mda->BookBackground = NULL;
	}
/*
	for (long i = 0; i < MAX_FLYOVER; i++)
	{
		if ( !ARXmenu.mda->flyover[i].empty() )
			ARX_Menu_Release_Text(ARXmenu.mda->flyover[i]);
	}*/
/*
	ARX_Menu_Release_Text(ARXmenu.mda->str_cre_credits);

	ARX_Menu_Release_Text(ARXmenu.mda->str_button_quickgen);
	ARX_Menu_Release_Text(ARXmenu.mda->str_button_skin);
	ARX_Menu_Release_Text(ARXmenu.mda->str_button_done);
*/
	if (ARXmenu.mda)
	{
		free(ARXmenu.mda);
		ARXmenu.mda = NULL;
	}

	free(ARXmenu.mda);
	ARXmenu.mda = NULL;

	//Synchronize game mixers with menu mixers and switch between them
	if (_bNoSound)
	{
		ARX_SOUND_MixerSwitch(ARX_SOUND_MixerMenu, ARX_SOUND_MixerGame);

		ARX_SOUND_MixerSetVolume(ARX_SOUND_MixerGame, ARX_SOUND_MixerGetVolume(ARX_SOUND_MixerMenu));
		ARX_SOUND_MixerSetVolume(ARX_SOUND_MixerGameSample, ARX_SOUND_MixerGetVolume(ARX_SOUND_MixerMenuSample));
		ARX_SOUND_MixerSetVolume(ARX_SOUND_MixerGameSpeech, ARX_SOUND_MixerGetVolume(ARX_SOUND_MixerMenuSpeech));
		ARX_SOUND_MixerSetVolume(ARX_SOUND_MixerGameAmbiance, ARX_SOUND_MixerGetVolume(ARX_SOUND_MixerMenuAmbiance));
	}

	if (pTextureLoad)
	{
		D3DTextr_KillTexture(pTextureLoad);
		pTextureLoad = NULL;
	}
}

extern long NO_TIME_INIT;
//-----------------------------------------------------------------------------
void ARX_MENU_Clicked_QUIT()
{
	if (REFUSE_GAME_RETURN) return;

	if (INTRO_NOT_LOADED == 2) return;

	ARX_Menu_Resources_Release();
	ARXmenu.currentmode = AMCM_OFF;

	if (!NO_TIME_INIT)
		ARX_TIME_UnPause();
}
long CAN_REPLAY_INTRO = 1;
//-----------------------------------------------------------------------------
void ARX_MENU_Clicked_NEWQUEST()
{
	CAN_REPLAY_INTRO = 0;
	ARX_TIME_UnPause();

	if (FINAL_RELEASE)
	{
		REFUSE_GAME_RETURN = 1;
	}

	ARX_PLAYER_Start_New_Quest();
	Book_Mode = 0;
	player.skin = 0;
	ePlayerAngle.b = -25.f;
	ARX_PLAYER_Restore_Skin();
	ARXmenu.currentmode = AMCM_NEWQUEST;
}

//-----------------------------------------------------------------------------
void ARX_MENU_NEW_QUEST_Clicked_QUIT()
{
	INTRO_NOT_LOADED = 1;
	START_NEW_QUEST = 1;
	REFUSE_GAME_RETURN = 0;
	NEED_SPECIAL_RENDEREND = 1;
	ARX_MENU_Clicked_QUIT();
}

//-----------------------------------------------------------------------------
void ARX_MENU_Clicked_CREDITS()
{
	ARXmenu.currentmode = AMCM_CREDITS;
	ARXmenu.mda->creditstart = ARX_TIME_Get();
	ARX_MENU_LaunchAmb(AMB_CREDITS);
}
extern long FINAL_COMMERCIAL_DEMO;
bool ARX_IsSteam();

//-----------------------------------------------------------------------------
void ARX_MENU_Clicked_QUIT_GAME()
{
	if (GAME_EDITOR)
		ARX_MENU_Clicked_QUIT();
	else
	{
		if	(FINAL_COMMERCIAL_DEMO)
		{
			StartImageDemo();
		}

		ARX_Menu_Resources_Release();
		ARXmenu.currentmode = AMCM_OFF;
		ARX_TIME_UnPause();

		ClearGameDEVICE();

		danaeApp.Cleanup3DEnvironment();
		exit(0);
	}
}

//-----------------------------------------------------------------------------
void ARX_MENU_Launch(LPDIRECT3DDEVICE7 m_pd3dDevice)
{
	ARX_TIME_Pause();

	//Synchronize menu mixers with game mixers and switch between them
	ARX_SOUND_MixerSwitch(ARX_SOUND_MixerGame, ARX_SOUND_MixerMenu);

	ARX_SOUND_PlayMenuAmbiance(AMB_MENU);
	ARX_MENU_CLICKSOUND();

	ARXmenu.currentmode = AMCM_MAIN;
	ARX_Menu_Resources_Create(m_pd3dDevice);
}

//-----------------------------------------------------------------------------
// ARX Menu Management Func
//-----------------------------------------------------------------------------
void ARX_Menu_Manage(LPDIRECT3DDEVICE7 m_pd3dDevice)
{
	// looks for keys for each mode.
	switch (ARXmenu.currentmode)
	{
		case AMCM_OFF:
			/* Checked in Danae.cpp now ! */
			return;
			break;
		case AMCM_NEWQUEST:
		{
			if (pGetInfoDirectInput->IsVirtualKeyPressedNowUnPressed(DIK_ESCAPE)
					&&	! bFadeInOut // XS: Disabling ESC capture while fading in or out.
			   )
			{
				ARX_MENU_CLICKSOUND();
				ARXmenu.currentmode = AMCM_MAIN;
			}
		}
		break;
		case AMCM_MAIN:

			if (pGetInfoDirectInput->IsVirtualKeyPressedNowUnPressed(DIK_ESCAPE))
			{
				if ((MENU_NoActiveWindow())  && (!REFUSE_GAME_RETURN))
				{
					ARX_TIME_UnPause();
					ARX_MENU_Clicked_QUIT();
				}
			}

			break;
		case AMCM_CREDITS:

			if ((pGetInfoDirectInput->IsVirtualKeyPressedNowUnPressed(DIK_ESCAPE))
					|| (pGetInfoDirectInput->IsVirtualKeyPressedNowUnPressed(DIK_SPACE)))
			{
				ARX_MENU_CLICKSOUND();
				bFadeInOut = true;	//fade out
				bFade = true;			//active le fade
				iFadeAction = AMCM_MAIN;

				ARX_MENU_LaunchAmb(AMB_MENU);
			}

			break;
		default:
			break;
	}
}
extern long PLAYER_INTERFACE_HIDE_COUNT;
extern long SPLASH_THINGS_STAGE;
long NEED_INTRO_LAUNCH = 0;
//-----------------------------------------------------------------------------
// ARX Menu Rendering Func
// returns false if no menu needs to be displayed
//-----------------------------------------------------------------------------
bool ARX_Menu_Render(LPDIRECT3DDEVICE7 m_pd3dDevice)
{
	// Auto-Launch Demo after 60 sec idle on Main Menu
	if ((ARXmenu.currentmode == AMCM_MAIN) && CAN_REPLAY_INTRO)
	{
		if ((ARXmenu_lastmode != AMCM_MAIN) || (pGetInfoDirectInput && (pGetInfoDirectInput->bTouch || pGetInfoDirectInput->bMouseMove)))
		{
			ARXmenu_starttick = ARX_TIME_GetUL(); //treat warning C4244 conversion from 'float' to 'unsigned long'
		}

		unsigned long tim = ARX_TIME_GetUL() - ARXmenu_starttick; //treat warning C4244 conversion from 'float' to 'unsigned long'

		if ((tim > 180000) && (REFUSE_GAME_RETURN))
		{
			NEED_INTRO_LAUNCH = 1;
		}
	}
	else
		ARXmenu_starttick = ARX_TIME_GetUL(); //treat warning C4244 conversion from 'float' to 'unsigned long'

	ARXmenu_lastmode = ARXmenu.currentmode;

	if (ARXmenu.currentmode == AMCM_OFF)
	{
		return false;
	}

	FRAME_COUNT = 0;

	bool br = Menu2_Render();

	if (br)
	{
		return br;
	}

	if (ARXmenu.currentmode == AMCM_OFF)
	{
		return false;
	}

	if (pGetInfoDirectInput->GetMouseButton(DXI_BUTTON0))
	{
		EERIEMouseButton = 1;
		LastMouseClick = 1;
	}
	else if (pGetInfoDirectInput->GetMouseButton(DXI_BUTTON1))
	{
		EERIEMouseButton = 2;
		LastMouseClick = 2;
	}
	else
	{
		EERIEMouseButton = 0;
	}

	if (!danaeApp.DANAEStartRender())
	{
		return true;
	}

	GDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0L);
	long posx;
	posx = DANAESIZX >> 1;

	
	FLYING_OVER = 0;

	//-------------------------------------------------------------------------

	if ((ARXmenu.currentmode == AMCM_NEWQUEST) && (ARXmenu.mda))
	{
		if (ITC.Get("questbook") == NULL)
		{
			ARX_Menu_Resources_Release(false);
			ARX_Menu_Resources_Create(m_pd3dDevice);

			ITC.Set("playerbook", "Graph\\Interface\\book\\character_sheet\\char_sheet_book.bmp");
			ITC.Set("ic_casting", "Graph\\Interface\\book\\character_sheet\\buttons_carac\\icone_casting.bmp");
			ITC.Set("ic_close_combat", "Graph\\Interface\\book\\character_sheet\\buttons_carac\\icone_close_combat.bmp");
			ITC.Set("ic_constitution", "Graph\\Interface\\book\\character_sheet\\buttons_carac\\icone_constit.bmp");
			ITC.Set("ic_defense", "Graph\\Interface\\book\\character_sheet\\buttons_carac\\icone_defense.bmp");
			ITC.Set("ic_dexterity", "Graph\\Interface\\book\\character_sheet\\buttons_carac\\icone_dext.bmp");
			ITC.Set("ic_etheral_link", "Graph\\Interface\\book\\character_sheet\\buttons_carac\\icone_etheral_link.bmp");
			ITC.Set("ic_mind", "Graph\\Interface\\book\\character_sheet\\buttons_carac\\icone_intel.bmp");
			ITC.Set("ic_intuition", "Graph\\Interface\\book\\character_sheet\\buttons_carac\\icone_intuition.bmp");
			ITC.Set("ic_mecanism", "Graph\\Interface\\book\\character_sheet\\buttons_carac\\icone_mecanism.bmp");
			ITC.Set("ic_object_knowledge", "Graph\\Interface\\book\\character_sheet\\buttons_carac\\icone_obj_knowledge.bmp");
			ITC.Set("ic_projectile", "Graph\\Interface\\book\\character_sheet\\buttons_carac\\icone_projectile.bmp");
			ITC.Set("ic_stealth", "Graph\\Interface\\book\\character_sheet\\buttons_carac\\icone_stealth.bmp");
			ITC.Set("ic_strength", "Graph\\Interface\\book\\character_sheet\\buttons_carac\\icone_strenght.bmp");

			ITC.Set("questbook", "Graph\\Interface\\book\\questbook.bmp");
			ITC.Set("pTexSpellBook", "Graph\\Interface\\book\\SpellBook.bmp");
			ITC.Set("bookmark_char", "Graph\\Interface\\book\\bookmark_char.bmp");
			ITC.Set("bookmark_magic", "Graph\\Interface\\book\\bookmark_magic.bmp");
			ITC.Set("bookmark_map", "Graph\\Interface\\book\\bookmark_map.bmp");
			ITC.Set("bookmark_quest", "Graph\\Interface\\book\\bookmark_quest.bmp");

			ITC.Set("accessible_1", "Graph\\Interface\\book\\Accessible\\accessible_1.bmp");
			ITC.Set("accessible_2", "Graph\\Interface\\book\\Accessible\\accessible_2.bmp");
			ITC.Set("accessible_3", "Graph\\Interface\\book\\Accessible\\accessible_3.bmp");
			ITC.Set("accessible_4", "Graph\\Interface\\book\\Accessible\\accessible_4.bmp");
			ITC.Set("accessible_5", "Graph\\Interface\\book\\Accessible\\accessible_5.bmp");
			ITC.Set("accessible_6", "Graph\\Interface\\book\\Accessible\\accessible_6.bmp");
			ITC.Set("accessible_7", "Graph\\Interface\\book\\Accessible\\accessible_7.bmp");
			ITC.Set("accessible_8", "Graph\\Interface\\book\\Accessible\\accessible_8.bmp");
			ITC.Set("accessible_9", "Graph\\Interface\\book\\Accessible\\accessible_9.bmp");
			ITC.Set("accessible_10", "Graph\\Interface\\book\\Accessible\\accessible_10.bmp");
			ITC.Set("current_1", "Graph\\Interface\\book\\Current_Page\\Current_1.bmp");
			ITC.Set("current_2", "Graph\\Interface\\book\\Current_Page\\Current_2.bmp");
			ITC.Set("current_3", "Graph\\Interface\\book\\Current_Page\\Current_3.bmp");
			ITC.Set("current_4", "Graph\\Interface\\book\\Current_Page\\Current_4.bmp");
			ITC.Set("current_5", "Graph\\Interface\\book\\Current_Page\\Current_5.bmp");
			ITC.Set("current_6", "Graph\\Interface\\book\\Current_Page\\Current_6.bmp");
			ITC.Set("current_7", "Graph\\Interface\\book\\Current_Page\\Current_7.bmp");
			ITC.Set("current_8", "Graph\\Interface\\book\\Current_Page\\Current_8.bmp");
			ITC.Set("current_9", "Graph\\Interface\\book\\Current_Page\\Current_9.bmp");
			ITC.Set("current_10", "Graph\\Interface\\book\\Current_Page\\Current_10.bmp");
			ITC.Set("heropageleft", "Graph\\Interface\\book\\character_sheet\\Hero_left_X24_Y24.BMP");
			ITC.Set("heropageright", "Graph\\Interface\\book\\character_sheet\\Hero_right_X305_Y270.BMP");

			ITC.Set("symbol_mega", NULL);
			ITC.Set("symbol_vista", NULL);
			ITC.Set("symbol_aam", NULL);
			ITC.Set("symbol_taar", NULL);
			ITC.Set("symbol_yok", NULL);

			ITC.Set("pTexCursorRedist", "Graph\\Interface\\cursors\\add_points.bmp");

			ITC.Set("pTexCornerLeft", "Graph\\Interface\\book\\Left_corner_original.bmp");
			ITC.Set("pTexCornerRight", "Graph\\Interface\\book\\Right_corner_original.bmp");

			ARX_Allocate_Text(ITC.Level, _T("system_charsheet_player_lvl"));
			ARX_Allocate_Text(ITC.Xp, _T("system_charsheet_player_xp"));

			ANIM_Set(&player.useanim, herowaitbook);

			player.useanim.flags |= EA_LOOP;

			ARXOldTimeMenu = ARXTimeMenu = ARX_TIME_Get();
			ARXDiffTimeMenu = 0;
		}

		GDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, false);
		SETALPHABLEND(GDevice, false);

		if (ARXmenu.mda->BookBackground != NULL)
		{
			SETALPHABLEND(GDevice, false);
			GDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, false);
			SETZWRITE(GDevice, false);
			GDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_FALSE);

			EERIEDrawBitmap2(GDevice, 0, 0, ARX_CLEAN_WARN_CAST_FLOAT(DANAESIZX), ARX_CLEAN_WARN_CAST_FLOAT(DANAESIZY), 0.9f, ARXmenu.mda->BookBackground, D3DCOLORWHITE);
		}

		BOOKZOOM = 1;

		ARX_INTERFACE_ManageOpenedBook();


		if (ARXmenu.mda)
		{
			long DONE = 0;

			if ((player.Skill_Redistribute == 0) && (player.Attribute_Redistribute == 0))
				DONE = 1;

			float ox, oy;
			ox = Xratio;
			oy = Yratio;
			LASTBOOKBUTTON = BOOKBUTTON;
			BOOKBUTTON = EERIEMouseButton;
			Xratio = ox;
			Yratio = oy;

			if (!ARXmenu.mda->flyover[FLYING_OVER].empty() ) //=ARXmenu.mda->flyover[FLYING_OVER];
			{
				if (FLYING_OVER != OLD_FLYING_OVER)
				{

					float fRandom	= rnd() * 2;
					ARX_CHECK_INT(fRandom);

					int t	= ARX_CLEAN_WARN_CAST_INT(fRandom);


					pTextManage->Clear();
					OLD_FLYING_OVER = FLYING_OVER;
					UNICODE_ARXDrawTextCenteredScroll((DANAESIZX * 0.5f),
													  12,
													  (DANAECENTERX) * 0.82f,
													  ARXmenu.mda->flyover[FLYING_OVER],
													  RGB(232 + t, 204 + t, 143 + t),
													  0x00FF00FF,
													  hFontInGame,
													  1000,
													  0.01f,
													  2);
				}
			}
			else
			{
				OLD_FLYING_OVER = -1;
			}
			
			float fPosX = 0;
			float fPosY = 313 * Yratio + (DANAESIZY - 313 * Yratio) * 0.70f;

			float fSizeX = 100 * Xratio;
			float fSizeY = 100 * Yratio;

			EERIE_3D ePos;
			COLORREF Color = 0;

			//---------------------------------------------------------------------
			// Button QUICK GENERATION
			fPosX = (DANAESIZX - (513 * Xratio)) * 0.5f;

			if (MouseInRect(fPosX, fPosY, fPosX + fSizeX + 50, fPosY + fSizeY))
			{
				SpecialCursor = CURSOR_INTERACTION_ON;
				FLYING_OVER = BUTTON_QUICK_GENERATION;

				if (EERIEMouseButton & 1) ;
				else if ((!(EERIEMouseButton & 1)) && (LastMouseClick & 1))
				{
					QUICK_MOD++;
					int iSkin = player.skin;
					ARX_MENU_CLICKSOUND();

					if (bQuickGenFirstClick)
					{
						ARX_PLAYER_MakeAverageHero();
						bQuickGenFirstClick = false;
					}
					else
					{
						ARX_PLAYER_QuickGeneration();
					}


					ARX_CHECK_CHAR(iSkin);
					player.skin = ARX_CLEAN_WARN_CAST_CHAR(iSkin);

				}
				else;

				Color = RGB(255, 255, 255);
			}
			else
				Color = RGB(232, 204, 143);

			ePos.x = fPosX;
			ePos.y = fPosY;
			FontRenderText(hFontMenu, ePos, ARXmenu.mda->str_button_quickgen, Color);

			//---------------------------------------------------------------------
			// Button SKIN
			fPosX = DANAESIZX * 0.5f;

			if (MouseInRect(fPosX, fPosY, fPosX + fSizeX, fPosY + fSizeY))
			{
				SpecialCursor = CURSOR_INTERACTION_ON;
				FLYING_OVER = BUTTON_SKIN;

				if ((!(EERIEMouseButton & 1)) && (LastMouseClick & 1))
				{
					SKIN_MOD++;
					BOOKZOOM = 1;
					ARX_MENU_CLICKSOUND();
					player.skin++;

					if (player.skin > 3)  player.skin = 0;

					switch (player.skin)
					{
						case 0:
							ePlayerAngle.b = -25.f;
							break;
						case 1:
							ePlayerAngle.b = -10.f;
							break;
						case 2:
							ePlayerAngle.b = 20.f;
							break;
						case 3:
							ePlayerAngle.b = 35.f;
							break;
					}

					ARX_PLAYER_Restore_Skin();
				}

				if (EERIEMouseButton & 1) ;
				else ;

				Color = RGB(255, 255, 255);
			}
			else
				Color = RGB(232, 204, 143);

			ePos.x = fPosX;
			ePos.y = fPosY;
			FontRenderText(hFontMenu, ePos, ARXmenu.mda->str_button_skin, Color);

			//---------------------------------------------------------------------
			// Button DONE
			fPosX = DANAESIZX - (DANAESIZX - 513 * Xratio) * 0.5f - 40 * Xratio;

			if (MouseInRect(fPosX, fPosY, fPosX + fSizeX, fPosY + fSizeY))
			{
				if (DONE) SpecialCursor = CURSOR_INTERACTION_ON;

				FLYING_OVER = BUTTON_DONE;

				if ((DONE) && (!(EERIEMouseButton & 1)) && (LastMouseClick & 1))
				{
					if ((SKIN_MOD == 8) && (QUICK_MOD == 10))
					{
						SKIN_MOD = -2;
					}
					else if (SKIN_MOD == -1)
					{
						ARX_PLAYER_MakeSpHero();
						player.skin = 4;
						ARX_PLAYER_Restore_Skin();
						SKIN_MOD = 0;
						SP_HEAD = 1;
					}
					else
					{
						if (SP_HEAD)
						{
							player.skin = 4;
							ARX_PLAYER_Restore_Skin();
							SP_HEAD = 0;
						}

						ARX_MENU_CLICKSOUND();

						bFadeInOut = true;	//fade out
						bFade = true;			//active le fade
						iFadeAction = AMCM_OFF;
					}
				}
				else
				{
					if (DONE)
						Color = RGB(255, 255, 255);
					else
						Color = RGB(192, 192, 192);
				}

			}
			else
			{
				if (DONE)
					Color = RGB(232, 204, 143);
				else
					Color = RGB(192, 192, 192);
			}

			if (SKIN_MOD < 0)
				Color = RGB(255, 0, 255);

			ePos.x = fPosX;
			ePos.y = fPosY;
			FontRenderText(hFontMenu, ePos, ARXmenu.mda->str_button_done, Color);
		}
	}

	//-------------------------------------------------------------------------
	if ((ARXmenu.currentmode == AMCM_CDNOTFOUND) && (ARXmenu.mda))
	{
		if (ARXmenu.mda->BookBackground != NULL)
		{
			SETALPHABLEND(GDevice, false);
			GDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, false);
			SETZWRITE(GDevice, false);
			GDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_FALSE);

			EERIEDrawBitmap2(GDevice, 0, 0, ARX_CLEAN_WARN_CAST_FLOAT(DANAESIZX), ARX_CLEAN_WARN_CAST_FLOAT(DANAESIZY), 0.9f, ARXmenu.mda->BookBackground, D3DCOLORWHITE);
		}

		EERIE_3D ePos;
		COLORREF Color = 0;
		int iW;
		int iH;
		std::string szText;

		Color = RGB(232, 204, 143);

		PAK_UNICODE_GetPrivateProfileString("system_menus_main_cdnotfound", "", szText);
		iW = 0;
		iH = 0;
		GetTextSize(hFontMenu, szText, iW, iH);
		ePos.x = (DANAESIZX - iW) * 0.5f;
		ePos.y = DANAESIZY * 0.4f;
		FontRenderText(hFontMenu, ePos, szText, Color);

		PAK_UNICODE_GetPrivateProfileString("system_yes", "", szText);
		iW = 0;
		iH = 0;
		GetTextSize(hFontMenu, szText, iW, iH);
		ePos.x = (DANAESIZX * 0.5f - iW) * 0.5f;
		ePos.y = DANAESIZY * 0.5f;

		if (MouseInRect(ePos.x, ePos.y, ePos.x + iW, ePos.y + iH))
		{
			SpecialCursor = CURSOR_INTERACTION_ON;

			if (EERIEMouseButton & 1) ;
			else if ((!(EERIEMouseButton & 1)) && (LastMouseClick & 1))
			{
				ARX_MENU_CLICKSOUND();

			}
			else;

			Color = RGB(255, 255, 255);
		}
		else
			Color = RGB(232, 204, 143);

		FontRenderText(hFontMenu, ePos, szText, Color);

		PAK_UNICODE_GetPrivateProfileString("system_no", "", szText);
		iW = 0;
		iH = 0;
		GetTextSize(hFontMenu, szText, iW, iH);
		ePos.x = DANAESIZX * 0.5f + (DANAESIZX * 0.5f - iW) * 0.5f;

		if (MouseInRect(ePos.x, ePos.y, ePos.x + iW, ePos.y + iH))
		{
			SpecialCursor = CURSOR_INTERACTION_ON;

			if (EERIEMouseButton & 1) ;
			else if ((!(EERIEMouseButton & 1)) && (LastMouseClick & 1))
			{
				ARX_MENU_CLICKSOUND();

			}
			else;

			Color = RGB(255, 255, 255);
		}
		else
			Color = RGB(232, 204, 143);

		FontRenderText(hFontMenu, ePos, szText, Color);
	}

	

	DynLight[0].pos.x = 0.f + EERIEMouseX - (DANAESIZX >> 1);
	DynLight[0].pos.y = 0.f + EERIEMouseY - (DANAESIZY >> 1);

	danaeApp.DANAEEndRender();

	if (pTextManage)
	{
		pTextManage->Update(FrameDiff);
		pTextManage->Render();
	}

	danaeApp.DANAEStartRender();

	if (ARXmenu.currentmode != AMCM_CREDITS)
		ARX_INTERFACE_RenderCursor(1);

	if (ARXmenu.currentmode == AMCM_NEWQUEST)
	{
		if (ProcessFadeInOut(bFadeInOut, 0.1f))
		{
			switch (iFadeAction)
			{
				case AMCM_OFF:
					ARX_TIME_UnPause();
					ARX_MENU_NEW_QUEST_Clicked_QUIT();
					iFadeAction = -1;
					bFade = false;
					fFadeInOut = 0.f;

					if (pTextManage)
					{
						pTextManage->Clear();
					}

					break;
			}
		}
	}

	danaeApp.DANAEEndRender();
	return true;
}
