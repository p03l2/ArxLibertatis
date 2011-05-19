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

#ifndef ARX_CORE_RESOURCE_H
#define ARX_CORE_RESOURCE_H

#include "Configure.h"

#define IDI_MAIN                        106

#ifdef BUILD_EDITOR

#define IDSTARTSNAPSHOT                 2
#define IDPASTE                         3
#define IDCANCELSNAP                    3
#define IDSYNTAX                        3
#define IDCOPY                          4
#define IDRESET                         5
#define IDAPPLY                         7
#define IDR_DANAEMENU                   101
#define IDD_MUTLIPLAYER_CONNECT         101
#define IDD_MUTLIPLAYER_GAMES           102
#define IDD_MAIN_GAME                   103
#define IDD_MULTIPLAYER_CREATE          104
#define IDD_LOBBY_WAIT_STATUS           114
#define IDD_CHANGEDEVICE                144
#define IDD_DANAEABOUT                  148
#define IDB_DANAE                       150
#define IDR_DANAETOOLS                  151
#define IDB_DANAETB                     156
#define IDD_OPTIONS                     160
#define IDD_STARTOPTIONS                161
#define IDD_SHOWTEXT                    165
#define IDD_SHOWVARS                    166
#define IDD_OPTIONS2                    168
#define IDD_SHOWTEXTBIG                 169
#define IDB_ARX                         171
#define IDD_GAIATEXTEDIT                173
#define IDD_FOGDIALOG                   174
#define IDD_LIGHTDIALOG                 175
#define IDD_SCRIPTDIALOG                176
#define IDD_TESTDIALOG                  177
#define IDD_LANGUAGEDIALOG              178
#define IDD_PRECALC                     179
#define IDB_ARXPRESENTATION             181
#define IDD_PASS                        182
#define IDB_BITMAP1                     183
#define IDD_MAPDIALOG                   185
#define IDD_INTERDLG                    186
#define IDD_PATHWAYDLG                  187
#define IDI_ICON1                       188
#define IDD_SNAPSHOT                    189
#define IDD_SCRIPTERROR                 190
#define IDD_MESHREDUCTION               191
#define IDC_CURSOR1                     199
#define IDB_BITMAP2                     201
#define IDD_LEVEL_SELECTOR              203
#define IDD_ARX_CONFIG_DIALOG           206
#define IDI_ICON2                       214
#define IDB_BITMAP3                     217
#define IDD_CASE                        403
#define IDC_DEVICE_COMBO                1000
#define IDC_PLAYER_NAME_EDIT            1000
#define IDC_MODE_COMBO                  1001
#define IDC_GAMES_LIST                  1001
#define IDC_JOIN                        1002
#define IDC_BUTTON1                     1002
#define IDC_CREATE                      1003
#define IDC_CONNECTION_LIST             1004
#define IDC_BACK                        1005
#define IDC_CHECK_DPLAY_PROTOCOL        1006
#define IDC_EDIT_SESSION_NAME           1007
#define IDC_CHAT_EDIT                   1010
#define IDC_WINDOWED_CHECKBOX           1012
#define IDC_WIREFRAME                   1012
#define IDC_CHAT_LISTBOX                1012
#define IDC_BUTTON2                     1012
#define IDC_STEREO_CHECKBOX             1013
#define IDC_NOTEXTURES                  1013
#define IDC_SEARCH_CHECK                1013
#define IDC_BUTTON3                     1013
#define IDC_FULLSCREEN_TEXT             1014
#define IDC_BUTTON4                     1014
#define IDC_SHOWLIGHTSNSHADOWS          1015
#define IDC_BUTTON5                     1015
#define IDC_TORCHHALO                   1016
#define IDC_BUTTON6                     1016
#define IDC_BKGCOLOR                    1017
#define IDC_BUTTON7                     1017
#define IDC_MATHOPTIM                   1018
#define IDQUIT                          1018
#define IDC_BUTTON8                     1018
#define IDC_SHOWNORMALS                 1019
#define IDC_OTHERSERVER                 1019
#define IDC_QUIT                        1019
#define IDC_OK                          1020
#define IDC_SHOWDEPTH                   1020
#define IDC_ARKANESERVER                1020
#define IDC_INFOTEXT                    1021
#define IDC_RAY                         1022
#define IDC_TORCHHALO2                  1023
#define IDC_COLLISIONS                  1024
#define IDD_REPLACE                     1024
#define IDC_CHOOSEDIR                   1025
#define IDC_PLAYERCOLLISIONS            1025
#define IDD_REPLACEALL                  1025
#define IDC_COMPATIBILITY               1026
#define IDC_INVERTMOUSE                 1026
#define IDC_MULTIPLAYER                 1028
#define IDC_LOBBYCONNECTCANCEL          1029
#define IDC_NUM_PLAYERS                 1030
#define IDC_DEBUG1ST                    1033
#define IDC_SEND                        1034
#define IDC_ILLUMNORMAL                 1034
#define IDC_WAIT_TEXT                   1035
#define IDC_ILLUMRAYLAUNCH              1035
#define IDC_ILLUMSMOOTH                 1036
#define IDC_DEBUGNPCMOVE                1037
#define IDC_DEBUGSYS                    1038
#define IDD_HELP                        1038
#define IDC_FILTERPOINT                 1039
#define IDC_FILTERLINEAR                1040
#define IDC_SHOWTEXT                    1040
#define IDD_WORD                        1040
#define IDC_FILTERANISOTROPIC           1041
#define IDC_SHOWTEXT2                   1041
#define IDC_SETTEXTURE                  1042
#define IDC_DYNAMICNORMALS              1043
#define IDC_HIDEBACKGROUND              1044
#define IDC_DEBUGCODE                   1044
#define IDC_HIDENPC                     1045
#define IDC_DEBUGMOLLESS                1045
#define IDC_HIDEFIXINTER                1046
#define IDC_SYNTAXCHECK                 1046
#define IDC_HIDEITEMS                   1047
#define IDC_VERSION                     1047
#define IDC_HIDEPARTICLES               1048
#define IDC_ABOUT_VERSION               1048
#define IDC_HIDEINTERFACE               1049
#define IDC_FULLRENDER16BITS            1049
#define IDC_FULLRENDER32BITS            1050
#define IDC_HIDENODES                   1050
#define IDC_SLIDERDEPTH                 1051
#define IDC_HIDEANCHORS                 1051
#define IDC_STATICDEPTH                 1052
#define IDC_HIDECAMERAS                 1052
#define IDC_HIDEMAGICDUST               1053
#define IDC_HIDESPEECH                  1054
#define IDC_DEPTHDEFAULT                1055
#define IDD_UP                          1056
#define IDD_DOWN                        1057
#define IDC_TEXTEDIT                    1058
#define IDC_LIGHTPOWERUP                1059
#define IDC_POWERSLIDER                 1060
#define IDC_D3DTRANSFORM                1061
#define IDC_INTERNORM                   1062
#define IDC_SLIDER_ROTATIONSPEED        1062
#define IDC_TLEVEL1                     1062
#define IDC_POWERSLIDER2                1063
#define IDC_BUTTON_COLOR                1063
#define IDC_TLEVEL2                     1063
#define IDC_SLIDER_MOVESPEED            1064
#define IDC_TIMESLIDER                  1064
#define IDC_TLEVEL3                     1064
#define IDC_SLIDER_SCALING              1065
#define IDC_TLEVEL4                     1065
#define IDC_SLIDER_DURATION             1066
#define IDC_TLEVEL5                     1066
#define IDC_SLIDER_INITSIZE             1067
#define IDC_TLEVEL6                     1067
#define IDC_SLIDER_FREQUENCY            1068
#define IDC_TLEVEL7                     1068
#define IDC_BLEND1                      1069
#define IDC_TLEVEL8                     1069
#define IDC_BLEND2                      1070
#define IDC_TLEVEL9                     1070
#define IDC_BLEND3                      1071
#define IDC_TLEVEL10                    1071
#define IDC_BLEND4                      1072
#define IDD_GROUPBOXDIRECTION           1072
#define IDC_DIRECTIONAL                 1073
#define IDC_LOADDEMO                    1073
#define IDC_SLIDER_FREQUENCY_TEXT       1074
#define IDC_LOADDEMO2                   1074
#define IDC_TEXTUREPRECISION            1075
#define IDC_STATICC                     1076
#define IDC_TEX16                       1077
#define IDC_TEX32                       1078
#define IDC_NOAPPLYDYNLIGHT             1078
#define IDC_HOTSPOT                     1079
#define IDC_LOADDEMO3                   1079
#define IDC_STATIC2                     1080
#define IDC_SLIDER11                    1080
#define IDC_LOADDEMO4                   1080
#define IDC_STATIC3                     1081
#define IDC_STATIC11                    1081
#define IDC_TLEVEL0                     1081
#define IDC_STATIC4                     1082
#define IDC_HOTSPOT2                    1082
#define IDC_TLEVEL11                    1082
#define IDC_STATIC5                     1083
#define IDC_SLIDER12                    1083
#define IDC_TLEVEL12                    1083
#define IDC_STATIC6                     1084
#define IDC_HOTSPOT4                    1084
#define IDC_TLEVEL13                    1084
#define IDC_HOTSPOT3                    1085
#define IDC_TLEVEL14                    1085
#define IDC_SLIDER13                    1086
#define IDC_TLEVEL15                    1086
#define IDC_STATIC13                    1087
#define IDC_TLEVEL16                    1087
#define IDC_LIGHTCOLOR                  1088
#define IDC_TLEVEL17                    1088
#define IDC_STATIC12                    1089
#define IDC_TLEVEL18                    1089
#define IDC_FLARES                      1090
#define IDC_SLIDER14                    1090
#define IDC_TLEVEL19                    1090
#define IDC_EDIT1                       1091
#define IDC_STATIC14                    1091
#define IDC_MAPUPDATE                   1091
#define IDC_TLEVEL20                    1091
#define IDC_EDIT2                       1092
#define IDC_HOTSPOT5                    1092
#define IDC_THIRDPERSON                 1092
#define IDC_TLEVEL21                    1092
#define IDC_OBJNAME                     1093
#define IDC_HOTSPOT6                    1093
#define IDC_TLEVEL22                    1093
#define IDC_NODIRCREATION               1094
#define IDC_HOTSPOT7                    1094
#define IDC_SEMIDYNAMIC                 1095
#define IDC_TLEVEL23                    1095
#define IDC_EXTINGUISH                  1096
#define IDC_TLEVEL24                    1096
#define IDC_EXTINGUISH2                 1097
#define IDC_SLIDER15                    1098
#define IDC_STATIC15                    1099
#define IDC_SLIDER16                    1100
#define IDC_STATIC16                    1101
#define IDC_SPAWNFIRE                   1102
#define IDC_SPAWNSMOKE                  1103
#define IDC_SET_FIRE                    1104
#define IDC_SET_FIRE2                   1105
#define IDC_TIMEFACTOR                  1105
#define IDC_SLIDER17                    1106
#define IDC_TESTSLIDER                  1106
#define IDC_HOTSPOT8                    1107
#define IDC_TEST1                       1107
#define IDC_STATIC17                    1108
#define IDC_TEST2                       1108
#define IDC_LANGUAGE1                   1108
#define IDC_COLORLEGACY                 1109
#define IDC_TEST3                       1109
#define IDC_LANGUAGE2                   1109
#define IDC_INTERCOLOR                  1109
#define IDC_SLIDER18                    1110
#define IDC_TEST4                       1110
#define IDC_LANGUAGE3                   1110
#define IDC_INTERCOLOR2                 1110
#define IDC_INTERPOLATEMOUSE            1110
#define IDC_HOTSPOT9                    1111
#define IDC_LANGUAGE4                   1111
#define IDC_VSYNC                       1111
#define IDC_MODE                        1111
#define IDC_STATIC18                    1112
#define IDC_LANGUAGE5                   1112
#define IDC_SHOWSHADOWS                 1112
#define IDC_SLIDER19                    1113
#define IDC_LANGUAGE6                   1113
#define IDC_HPO                         1113
#define IDC_HOTSPOT10                   1114
#define IDC_LANGUAGE7                   1114
#define IDC_PROGRESS                    1114
#define IDC_STATIC19                    1115
#define IDC_LANGUAGE8                   1115
#define ID_RECALCULATE                  1115
#define IDC_SLIDER20                    1116
#define ID_STOP                         1116
#define IDC_HOTSPOT11                   1117
#define ID_PAUSE                        1117
#define IDC_STATIC20                    1118
#define ID_AROUND                       1118
#define IDC_CAST_SHADOWS                1119
#define IDC_LAUNCHDEMO                  1120
#define IDC_SLIDER21                    1120
#define IDC_STATIC33                    1121
#define IDC_FLARESIZZ                   1121
#define IDC_EDITPASS                    1122
#define IDC_STATIC21                    1122
#define IDC_NO_IGNIT                    1123
#define IDC_ZMAPMODE                    1124
#define IDC_BLURTEXTURES                1125
#define IDC_POINTINTERPOLATION          1126
#define IDC_FORCEIO                     1126
#define IDC_NOMIPMAPS                   1127
#define IDC_MESHTWEAK                   1128
#define IDC_SYNTAXCHECKING              1128
#define IDC_MAPFRAME                    1129
#define IDC_WATERFX                     1130
#define IDC_REFLECTFX                   1131
#define IDC_INTERTEXT                   1132
#define IDC_GOTOOBJECT                  1133
#define IDC_INTERTREEVIEW               1134
#define IDC_PATHWAYTIME                 1135
#define IDC_SELECTOBJECT                1135
#define IDC_PATHWAYBEZIER               1136
#define IDC_PATHWAYHIERARCHY            1137
#define IDC_PATHWAYLOOP                 1138
#define IDC_EDITNAME                    1139
#define IDC_EDITNBINTERPOLATIONS        1140
#define IDC_IMAGESSEC                   1141
#define IDC_SETPATH                     1142
#define IDC_XSIZE                       1143
#define IDC_YSIZE                       1144
#define IDC_16BITS                      1145
#define IDC_EDITFILENAMES               1146
#define IDC_MEMORYCACHE                 1147
#define IDC_FREEZESCRIPT                1148
#define IDC_ERRORLOG                    1149
#define IDC_ERRORSTRING                 1150
#define IDC_SLIDER_REDUCTION            1151
#define IDD_FINDWHAT                    1152
#define IDD_REPLACEWITH                 1153
#define IDC_NO_REDUCTION                1154
#define IDC_REDUCTION                   1155
#define IDC_ZONE                        1155
#define IDC_FORCE_REDUCTION             1156
#define IDC_EDITHEIGHT                  1156
#define IDC_CONSTANTUPDATE              1158
#define IDC_FIXFLARESIZE                1159
#define IDC_FASTLOADING                 1160
#define IDC_FLARE                       1161
#define IDC_LINE1                       1165
#define IDC_COL1                        1166
#define IDC_LINE2                       1167
#define IDC_COL2                        1168
#define IDC_LOCSCR2                     1169
#define IDC_STATICCOL2                  1170
#define IDC_STATICLINE2                 1171
#define IDC_LOCSCR1                     1172
#define IDC_STATICCOL1                  1173
#define IDC_STATICLINE1                 1174
#define IDD_SEARCH                      1175
#define IDC_TREATALLIO                  1176
#define IDC_SEARCHEDIT                  1177
#define IDC_NOCHECKSUM                  1178
#define IDC_AMBIANCE                    1179
#define IDC_AMBIANCETEXT                1180
#define IDC_FADECOLOR                   1181
#define IDC_COLORCHOOSE                 1182
#define IDC_CLIPPINGFAR                 1183
#define IDC_SLIDER1                     1184
#define IDC_CLIPPINGRESET               1185
#define IDC_REVERB                      1186
#define IDC_SLIDER2                     1187
#define IDC_SOUND                       1187
#define IDC_DISABLESOUND                1187
#define IDC_FCLIPTEXT                   1189
#define IDC_MAXVOLTEXT                  1190
#define IDC_SHOWCOLOR                   1194
#define IDC_REVERBCOMBO                 1195
#define IDC_TRUEFIGHT                   1196
#define IDC_NEED_ANCHOR                 1198
#define IDC_ARXDEMO                     1199
#define IDC_USED3DFOG                   1200
#define IDC_C_LEVEL0                    1201
#define IDC_C_LEVEL1                    1202
#define IDC_C_LEVEL2                    1203
#define IDC_C_LEVEL3                    1204
#define IDC_C_LEVEL4                    1205
#define IDC_C_LEVEL5                    1206
#define IDC_C_LEVEL6                    1207
#define IDC_C_LEVEL7                    1208
#define IDC_C_LEVEL8                    1209
#define IDC_C_LEVEL9                    1210
#define IDC_C_LEVEL10                   1211
#define IDC_C_LEVEL11                   1212
#define IDC_C_LEVEL12                   1213
#define IDC_C_LEVEL13                   1214
#define IDC_C_LEVEL14                   1215
#define IDC_C_LEVEL15                   1216
#define IDC_C_LEVEL16                   1217
#define IDC_C_LEVEL17                   1218
#define IDC_C_LEVEL18                   1219
#define IDC_C_LEVEL19                   1220
#define IDC_C_LEVEL20                   1221
#define IDC_C_LEVEL21                   1222
#define IDC_C_LEVEL22                   1223
#define IDC_C_LEVEL23                   1224
#define IDC_GOTOPOLY                    1225
#define IDC_ARX_CONFIG_STATIC           1226
#define IDC_COMBO_LANGUAGE              1228
#define IDC_COMBO_RESOLUTION            1229
#define IDC_COMBO_BPP                   1230
#define IDC_COMBO_TEXTURE               1231
#define IDC_COMBO_MISC                  1232
#define IDD_FINDDLG                     1540
#define IDD_REPLACEDLG                  1541
#define IDB_ARX_CONFIG_BITMAP           30003
#define DANAE_MENU_EXIT                 40001
#define DANAE_MENU_LOADLEVEL            40010
#define DANAE_MENU_SAVELEVEL            40011
#define DANAE_MENU_NEWLEVEL             40012
#define DANAE_MENU_ABOUT                40013
#define DANAE_MENU_SAVEAS               40014
#define DANAE_B001                      40015
#define DANAE_B002                      40016
#define DANAE_B003                      40017
#define DANAE_B004                      40018
#define DANAE_B005                      40019
#define DANAE_B006                      40020
#define DANAE_B007                      40021
#define DANAE_B008                      40022
#define DANAE_B009                      40023
#define DANAE_B010                      40024
#define DANAE_B011                      40025
#define DANAE_B012                      40026
#define DANAE_B013                      40027
#define DANAE_B014                      40028
#define DANAE_MENU_OPTIONS              40029
#define DANAE_MENU_PROJECTPATH          40030
#define DANAE_MENU_OPTIONS2             40031
#define DANAE_MENU_TEXLIST              40032
#define DANAE_MENU_UPDATEALLTEXTURES    40033
#define DANAE_MENU_UPDATEALLOBJECTS     40034
#define DANAE_MENU_UPDATEALLSCRIPTS     40035
#define DANAE_MENU_UPDATESCENE          40036
#define DANAE_MENU_IMPORTSCN            40037
#define DANAE_MENU_UPDATESOUNDS         40038
#define DANAE_MENU_LANGUAGE             40040
#define DANAE_MENU_GLOBALLIST           40041
#define DANAE_MENU_LOCALLIST            40042
#define DANAE_MENU_RECALC               40043
#define DANAE_MENU_RESETSHADOWS         40044
#define DANAE_MENU_INTEROBJLIST         40045
#define DANAE_MENU_CHOOSEFONT           40046
#define DANAE_MENU_MEMORY               40047
#define DANAE_MENU_UNFREEZEALLINTER     40048
#define DANAE_MENU_MESH_REDUCTION       40049
#define DANAE_MENU_ANIMATIONSLIST       40050
#define DANAE_MENU_UPDATELOCALISATION   40051
#define DANAE_B015                      40052
#define DANAE_B016                      40053
#define DANAE_B017                      40054
#define DANAE_B018                      40055
#define DANAE_B019                      40056
#define DANAE_B020                      40057
#define DANAE_MENU_FORCELOAD            40058
#define DANAE_MENU_PURGELEVEL           40059
#define DANAE_MENU_SAVEPATH             40060
#define IDM_MOULINEX                    40061
#define IDM_ANYPOLY                     40062
#define DANAE_MENU_UPDATEALLANIMS       40065
#define IDM_DLF_CHECK                   40066

#endif // BUILD_EDITOR

#endif // ARX_CORE_RESOURCE_H
