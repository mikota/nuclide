/*
	Copyright 2016-2018 Marco "eukara" Hladik
	
	MIT LICENSE

	Permission is hereby granted, free of charge, to any person 
	obtaining a copy of this software and associated documentation 
	files (the "Software"), to deal in the Software without 
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or
	sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

string sButtonLabels[ MENU_BUTTONS ] = {
	_("BTN_NEWGAME"),
	_("BTN_RESUMEGAME"),
	_("BTN_TRAINING"),
	_("BTN_CONFIG"),
	_("BTN_LOADGAME"),
	_("BTN_SAVELOAD"),
	_("BTN_README"),
	_("BTN_QUIT"),
	_("BTN_MULTIPLAYER"),
	_("BTN_EASY"),
	_("BTN_MEDIUM"),
	_("BTN_DIFFICULT"),
	_("BTN_SAVEGAME"),
	_("BTN_LOADGAME2"),
	_("BTN_CANCEL"),
	_("BTN_OPTIONS"),
	_("BTN_VIDEO"),
	_("BTN_AUDIO"),
	_("BTN_CONTROLS"),
	_("BTN_DONE"),
	_("BTN_QUICKSTART"),
	_("BTN_DEFAULTS"),
	_("BTN_OK"),
	_("BTN_VIDEOOPTIONS"),
	_("BTN_VIDEOMODES"),
	_("BTN_ADVCONTROLS"),
	_("BTN_ORDER"),
	_("BTN_DELETE"),
	_("BTN_INTERNET"),
	_("BTN_IRCCHAT"),
	_("BTN_LAN"),
	_("BTN_CUSTOMIZE"),
	_("BTN_SKIP"),
	_("BTN_EXIT"),
	_("BTN_CONNECT"),
	_("BTN_REFRESH"),
	_("BTN_FILTER"),
	_("BTN_CREATE"),
	_("BTN_CREATEGAME"),
	_("BTN_CHATROOMS"),
	_("BTN_LISTROOMS"),
	_("BTN_SEARCH"),
	_("BTN_SERVERS"),
	_("BTN_JOIN"),
	_("BTN_FIND"),
	_("BTN_CREATEROOM"),
	_("BTN_JOINGAME"),
	_("BTN_SEARCHGAMES"),
	_("BTN_FINDGAME"),
	_("BTN_STARTGAME"),
	_("BTN_GAMEINFO"),
	_("BTN_UPDATELIST"),
	_("BTN_ADDSERVER"),
	_("BTN_DISCONNECT"),
	_("BTN_CONSOLE"),
	_("BTN_CONTENTCONTROL"),
	_("BTN_UPDATE"),
	_("BTN_VISITWON"),
	_("BTN_PREVIEWS"),
	_("BTN_ADVOPTIONS"),
	_("BTN_3DINFO"),
	_("BTN_CUSTOMGAME"),
	_("BTN_ACTIVATE"),
	_("BTN_INSTALL"),
	_("BTN_VISITWEB"),
	_("BTN_REFRESHLIST"),
	_("BTN_DEACTIVATE"),
	_("BTN_SPECTATEGAME"),
	_("BTN_SPECTATEGAMES")
};

/*
=================
Object_Button

Used for the (used to be) bitmap buttons in the menu
=================
*/
void Object_Button( vector vPosition, int iButtonID, void() vFunction, __inout float fAlpha ) {
	static int iLastButton = -1;
	
	vPosition += vMenuOffset;
	
	if ( fAlpha > 0.0f ) {
		fAlpha -= frametime;
	} else {
		fAlpha = 0.0f;
	}
	
	if ( Menu_InputCheckMouse( vPosition, '156 26' ) == TRUE ) {
		if ( iLastButton != iButtonID ) {
			//localcmd( "play ../media/launch_deny2.wav\n" );
		}
		iLastButton = iButtonID;
		fAlpha = 1.0f;
		
		if ( fMouseClick == TRUE ) {
			if ( vFunction != __NULL__ ) {
				vFunction();
			}
			vHeaderButtonPos = vPosition;
			localsound("../media/launch_select2.wav"); 
			fMouseClick = FALSE;
		}
	}

	vector vSrcPos, vSrcSize;
	vSrcPos_x = 0;
	vSrcPos_y = ( 78 * iButtonID ) / vMenuButtonsSize_y;
	vSrcSize = [ 1, 26 / vMenuButtonsSize_y ];
	drawsubpic( vPosition, '156 26', "gfx/shell/btns_main", vSrcPos, vSrcSize, '1 1 1', 1.0f, 1 );
	drawsubpic( vPosition, '156 26', "gfx/shell/btns_main", vSrcPos + [ 0, 52 / vMenuButtonsSize_y ], vSrcSize, '1 1 1', fAlpha, 1 );
}

void Object_TextButton( vector vPosition, string sButtonText, void() vFunction, __inout float fAlpha ) {
	static string sLastButton;
	
	vPosition += vMenuOffset;
	
	if ( fAlpha > 0.0f ) {
		fAlpha -= frametime;
	} else {
		fAlpha = 0.0f;
	}
	
	if ( Menu_InputCheckMouse( vPosition, [stringwidth(sButtonText, TRUE, FONTSIZE), 12] ) == TRUE ) {
		if ( sLastButton != sButtonText ) {
			localsound("../media/launch_deny2.wav"); 
		}
		sLastButton = sButtonText;
		fAlpha = 1.0f;

		if ( fMouseClick == TRUE ) {
			if ( vFunction != __NULL__ ) {
				vFunction();
			}
			localsound("../media/launch_select2.wav"); 
			fMouseClick = FALSE;
		}
	}

	drawstring( vPosition, sButtonText, FONTSIZE, autocvar_menu_fgcolor, fAlpha, 1 );
}

/*
=================
Object_Frame

A filled "window" of sorts
=================
*/
void Object_Frame( vector vPosition, vector vSize ) {
	vPosition += vMenuOffset;
	
	// Draw the background
	drawfill( vPosition, vSize, '0 0 0', 1.0f );
	
	drawfill( vPosition, [vSize_x, 1], autocvar_menu_fgcolor, 1.0f ); // Top
	drawfill( [vPosition_x, vPosition_y + vSize_y - 1], [vSize_x, 1], autocvar_menu_fgcolor, 1.0f ); // Bottom
	
	drawfill( vPosition, [1, vSize_y], autocvar_menu_fgcolor, 1.0f ); // Left
	drawfill( [vPosition_x + vSize_x - 1, vPosition_y], [1, vSize_y], autocvar_menu_fgcolor, 1.0f ); // Right
}

/*
=================
Object_Label

A label in a cvar driven color scheme
=================
*/
void Object_Label( vector vPosition, string sLabel, vector vSize ) {
	vPosition += vMenuOffset;
	drawstring( vPosition, sLabel, vSize, autocvar_menu_fgcolor, 1.0f, 0 );
}

/*
=================
Object_Label_Right

A right-aligned version of Object_Label
=================
*/
void Object_Label_Right( vector vPosition, string sLabel, vector vSize ) {
	vPosition_x -= stringwidth( sLabel, TRUE, vSize );
	Object_Label( vPosition, sLabel, vSize );
}

/*
=================
Object_Desc

A label in a grey scheme
=================
*/
void Object_Desc( vector vPosition, string sLabel, vector vSize ) {
	vPosition += vMenuOffset;
	drawstring( vPosition, sLabel, vSize, '0.68 0.68 0.68', 1.0f, 0 );
}

/*
=================
Object_Scrollbar

A scrollbar, for different types of purposes.
Note: Only have one at a time.
=================
*/
void Object_Scrollbar( vector vPosition, int iHeight, __inout int iProgress ) {
	Object_Frame( vPosition, [ 16, iHeight + 16 ] );
	
	vPosition += vMenuOffset;

	if ( ( iScrollbarHold == TRUE ) || ( Menu_InputCheckMouse( [vPosition_x, vPosition_y + iProgress ], '16 16' ) == TRUE ) ) {
		if ( fMouseClick == TRUE ) {
			iProgress = ( vMousePos_y - vPosition_y );
			iScrollbarHold = TRUE;
		}
	}
	
	if ( fScrollWheel == SCROLL_DOWN ) {
		iProgress += 2;
		fScrollWheel = SCROLL_NONE;
	} else if ( fScrollWheel == SCROLL_UP ) {
		iProgress -= 2;
		fScrollWheel = SCROLL_NONE;
	}
	
	if ( iProgress < 0 ) {
		iProgress = 0;
	} else if ( iProgress > iHeight ) {
		iProgress = iHeight;
	} 
	
	drawfill( [vPosition_x, vPosition_y + iProgress], [ 16, 16 ], autocvar_menu_fgcolor, 1.0f );
}

/*
=================
Object_ScrollbarH

A scrollbar, for different types of purposes.
This is the horizontal version.
Note: Only have one at a time.
=================
*/
void Object_ScrollbarH( vector vPosition, int iWidth, __inout int iProgress ) {
	Object_Frame( vPosition, [ iWidth + 16, 16 ] );
	
	vPosition += vMenuOffset;

	if ( ( Menu_InputCheckMouse( [vPosition_x, vPosition_y ], [ iWidth, 16 ] ) == TRUE ) ) {
		if ( fMouseClick == TRUE ) {
			iProgress = ( vMousePos_x - vPosition_x );
		}
		
		if ( fScrollWheel == SCROLL_DOWN ) {
			iProgress += 2;
			fScrollWheel = SCROLL_NONE;
		} else if ( fScrollWheel == SCROLL_UP ) {
			iProgress -= 2;
			fScrollWheel = SCROLL_NONE;
		}
		
		if ( iProgress < 0 ) {
			iProgress = 0;
		} else if ( iProgress > iWidth ) {
			iProgress = iWidth;
		} 
	}

	drawfill( [ vPosition_x + iProgress, vPosition_y ], [ 16, 16 ], autocvar_menu_fgcolor, 1.0f );
}

/*
=================
Object_CvarToggle

A nice way of toggling cvars.
=================
*/
void Object_CvarToggle( vector vPosition, string sLabel, string sCvar ) {
	float fAlpha = 0.8f;
	int iWidth = stringwidth( sLabel, FALSE );
	vPosition += vMenuOffset;
	
	if ( Menu_InputCheckMouse( vPosition, [ iWidth + 32, 19 ] ) == TRUE ) {
		fAlpha = 1.0f;
		if ( fMouseClick == TRUE ) {
			if ( cvar( sCvar ) == 0 ) {
				cvar_set( sCvar, "1" );
			} else {
				cvar_set( sCvar, "0" );
			}
			fMouseClick = FALSE;
		}
	}
	
	drawfill( vPosition + '-2 -2', [ iWidth + 48, 19 ], '0 0 0', 0.8f );
	
	if ( cvar( sCvar ) == 0 ) {
		drawpic( vPosition, "gfx/shell/cb_empty", '19 19', '1 1 1', 1.0f, 0 );
		drawstring( vPosition+[24,4], sLabel, FONTSIZE, autocvar_menu_fgcolor, fAlpha, 0 );
	} else {
		drawpic( vPosition, "gfx/shell/cb_checked", '19 19', '1 1 1', 1.0f, 0 );
		drawstring( vPosition+[24,4], sLabel, FONTSIZE, autocvar_menu_fgcolor, fAlpha, 0 );
	}
}

/*
=================
Object_FuncToggle

A nice way of toggling cvars.
=================
*/
void Object_FuncToggle( vector vPosition, string sLabel, void( void ) vFunc, int iValue ) {
	float fAlpha = 0.8f;
	int iWidth = stringwidth( sLabel, FALSE );
	vPosition += vMenuOffset;
	
	if ( Menu_InputCheckMouse( vPosition, [ iWidth + 32, 19 ] ) == TRUE ) {
		fAlpha = 1.0f;
		if ( fMouseClick == TRUE ) {
			vFunc();
			fMouseClick = FALSE;
		}
	}
	
	drawfill( vPosition + '-2 -2', [ iWidth + 48, 19 ], '0 0 0', 0.8f );
	
	if ( iValue == 0 ) {
		drawpic( vPosition, "gfx/shell/cb_empty", '19 19', '1 1 1', 1.0f, 0 );
		drawstring( vPosition+[24,4], sLabel, FONTSIZE, autocvar_menu_fgcolor, fAlpha, 0 );
	} else {
		drawpic( vPosition, "gfx/shell/cb_checked", '19 19', '1 1 1', 1.0f, 0 );
		drawstring( vPosition+[24,4], sLabel, FONTSIZE, autocvar_menu_fgcolor, fAlpha, 0 );
	}
}


/*
=================
Object_FuncToggle

A nice way of toggling cvars.
=================
*/
void Object_Textfield( vector vPosition, __inout string strValue, int iMaxChars ) {
	float fFieldAlpha = 0.8f;
	vector vSize = [ ( iMaxChars * 8 ) + 16, 14 ];
	
	Object_Frame( vPosition - '2 2', vSize );
	
	vPosition += vMenuOffset;
	
	if ( Menu_InputCheckMouse( vPosition, vSize ) == TRUE ) {
		if( fInputKeyCode == K_BACKSPACE ) {
			if ( strValue ) {
				strValue = substring( strValue, 0, strlen( strValue ) - 1 );
				fInputKeyCode = 0;
				fInputKeyASCII = 0;
			}
		} else if ( fInputKeyASCII ) {
			if ( strlen( strValue ) <= iMaxChars ) {
				strValue = sprintf( "%s%s", strValue, chr2str( fInputKeyASCII ) );
				fInputKeyASCII = 0;
				fInputKeyCode = 0;
			}
		}
		fFieldAlpha = 1.0f;
		drawstring( vPosition, sprintf( "%s_", strValue ), FONTSIZE, autocvar_menu_fgcolor, fFieldAlpha, FALSE );
	} else {
		drawstring( vPosition, strValue, FONTSIZE, autocvar_menu_fgcolor, fFieldAlpha, FALSE );
	}
}
