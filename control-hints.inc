/*
*
*
*
*   ---------------------------------------------------
*
*	Creater - @Bren828 					
*									18 March 2026
*
*   Version: 1.0
*
*   ---------------------------------------------------
*
*
*	https://github.com/Bren828/control-hints
*
*
*
*/
#if defined CH_included
	#endinput
#endif
#define CH_included


#if !defined CH_MAX_CONTROL_HINTS
	#define CH_MAX_CONTROL_HINTS 32
#endif

#if !defined CH_DESCRIPTION_LENGTH
	#define CH_DESCRIPTION_LENGTH 128
#endif

#if !defined CH_CONTROL_LENGTH
	#define CH_CONTROL_LENGTH 64
#endif

#if !defined CH_LETTER_SIZE_X
	#define CH_LETTER_SIZE_X 0.1598
#endif

#if !defined CH_LETTER_SIZE_Y
	#define CH_LETTER_SIZE_Y 0.9199
#endif

#if !defined CH_BACKGROUND_HEIGHT
	#define CH_BACKGROUND_HEIGHT 11.5
#endif

#if !defined CH_HINT_STACK_GAP
	#define CH_HINT_STACK_GAP 1.0
#endif

#if !defined CH_BACKGROUND_COLOR
	#define CH_BACKGROUND_COLOR 0x1e1e1eFF
#endif

#if !defined CH_FOREGROUND_COLOR
	#define CH_FOREGROUND_COLOR 0x353535FF
#endif

#if !defined CH_TEXT_COLOR
	#define CH_TEXT_COLOR 0xFFFFFFFF
#endif

#if !defined CH_DESCRIPTION_COLOR
	#define CH_DESCRIPTION_COLOR 0xFFFFFFFF
#endif

#define CH_INVALID_ID 0

#define CH_TEXT_ALIGN_LEFT 		1
#define CH_TEXT_ALIGN_RIGHT 	3

#define CH_HIDE_HINT 	0
#define CH_SHOW_HINT 	1


#define CH_HINT_OFFSET_Y (CH_BACKGROUND_HEIGHT * CH_LETTER_SIZE_Y + 3.0)


enum PLAYER_CONTROL_HINT_EN {

	bool:ch_Created,
	ch_Visible,
	bool:ch_SavedVisible,

	PlayerText:ch_TD_Background,
	PlayerText:ch_TD_Foreground,
	PlayerText:ch_TD_Description,
	PlayerText:ch_TD_Control,

	ch_AnimationTimer,
	Float:ch_AnimationHeight,

	Float:ch_BackgroundX,
	Float:ch_BackgroundY,
	Float:ch_BackgroundWidth,
	Float:ch_BackgroundHeight,

	ch_HighlightTimer,

	ch_Description[CH_DESCRIPTION_LENGTH],
	ch_Control[CH_CONTROL_LENGTH],
	ch_Selectable,
	ch_Alignment,
}

static PlayerControlHint[MAX_PLAYERS][CH_MAX_CONTROL_HINTS][PLAYER_CONTROL_HINT_EN];

static Float:ControlHintAnchorX[MAX_PLAYERS];
static Float:ControlHintAnchorY[MAX_PLAYERS];



static const Float:CH_CharacterWidth[] = {
//space     !    	"	   	#    	$    	%    	&    	'       32 - 39
	12.0,  	10.0,  	13.0,  	25.0,  	26.0,  	30.0,  	28.0,  	8.0,
//  (       )	 	*      	+    	,    	-   	.   	/       40 - 47 
	13.0,  	13.0,  	33.0,  	27.0,  	11.1,  	12.1,  	10.1,  	17.1,
//   0     	1    	2      	3    	4    	5    	6    	7       48 - 55
	26.1,  	14.1,  	24.1,  	24.1,  	27.1,  	25.1,  	25.1,  	25.1,
//  8       9    	:     	;    	<	 	 =   	 >   	?       56 - 63
	25.1,  	25.1,  	11.1,  	11.1,  	27.2,  	27.1,  	27.2,  	21.0,

//  @      	A	 	B    	C    	D    	E    	F    	G       64 - 71
	29.0,  	29.1,  	25.1,  	25.1,  	27.1,  	24.1,  	23.1,  	27.1,
//  H       I    	J    	K    	L    	M    	N    	O       72 - 79
	27.1,  	9.1,  	22.1,  	26.1,  	23.1,  	29.1,  	27.1,  	28.1,
//  P    	Q    	R    	S    	T    	U    	V    	W	    80 - 87
	25.1,  	28.1,  	25.1,  	25.1,  	26.1,  	26.1,  	28.1,  	34.1,
//  X    	Y    	Z		[    	\    	]    	^    	_       88 - 95
	28.1,  	26.1,  	25.1,  	28.0,  	18.0,  	33.0,  	10.0,  	28.1,
//  '                                                               96
	10.0
};


static const Float:CH_RussianCharacterWidth[] = {
//  À    	Á    	Â      	Ã    	Ä    	Å    	Æ	            192 - 198 
	29.1,  	24.1,  	25.1,  	21.1,  	30.1,  	24.1,  	26.1,
//  Ç    	È    	É    	Ê    	Ë    	Ì    	Í    	Î       199 - 206	    
	24.1,  	27.1,  	27.1,  	26.1,  	26.1,  	29.1,  	27.1,  	28.1,
//  Ï    	Ð    	Ñ    	Ò    	Ó    	Ô    	Õ    	Ö       207 - 214	 
	26.1,  	25.1,  	25.1,  	26.1,  	26.1,  	28.1,  	28.1,  	29.1,  
//  ×    	Ø    	Ù    	Ú    	Û    	Ü    	Ý    	Þ       215 - 222
	26.1,  	28.1,  	31.1,  	28.1,  	32.1,  	25.1,  	25.1,  	32.1,
//  ß	                                                            223
	27.1
};


//Function for getting the width of a single character in a text draw
static stock Float:CH_GetTextDrawCharacterWidth(character) {

    if(character < 32 || character > 255) {
        return 0.0;
    }

    switch(character) {
        case 32..96: {
            return CH_CharacterWidth[character - 32];
        }
        case 97..122: {
            return CH_CharacterWidth[character - 64]; // a-z
        }
        case 168, 184: {
            return CH_RussianCharacterWidth[5]; // ¨/¸
        }
        case 192..223: {
            return CH_RussianCharacterWidth[character - 192]; // À-ß
        }
        case 224..255: {
            return CH_RussianCharacterWidth[character - 224]; // à-ÿ
        }
    }

    return 0.0;
}


// Function for getting the width of a string
stock Float:GetTextDrawStringWidth(const text[], bool:multiLine = false) {

	//multiLine - returns the maximum width of a line when wrapping

	if(!strlen(text)) {
		return 0.0;
	}

	new Float:totalWidth, 
		Float:currentLineWidth,
		Float:maxLineWidth;

	for(new i, length = strlen(text); i < length; i++) {

		if(text[i] == '~' && i < length - 1) {

			new next = text[i + 1];

			if(next == 'n') {
				// Save the maximum line width when wrapping
				if(currentLineWidth > maxLineWidth) {
					maxLineWidth = currentLineWidth;
				}
				currentLineWidth = 0;
			} 

			if(next == 'n' || next == 'r' || next == 'g' || next == 'b' || 
				next == 'y' || next == 'w' || next == 'l' || next == 'p' || next == 'h') {
				i++; // Skip ~X~
				continue;
			}
		}

		new Float:characterWidth = CH_GetTextDrawCharacterWidth(text[i]);

		currentLineWidth += characterWidth;
		totalWidth += characterWidth;
	}

	// Check the last line
	if(currentLineWidth > maxLineWidth) {
		maxLineWidth = currentLineWidth;
	}

	if(multiLine) {
		return maxLineWidth;
	}

	return totalWidth;
}



// Creates a hint above the previous one
stock CreateControlHintAbove(playerid, Float:xOffset, Float:yOffset, const description[], const control[], show = CH_SHOW_HINT, textAlignment = CH_TEXT_ALIGN_LEFT, selectable = 0) {
	
	xOffset = ControlHintAnchorX[playerid] - xOffset;
	yOffset = ControlHintAnchorY[playerid] - CH_HINT_OFFSET_Y - yOffset - CH_HINT_STACK_GAP;

	new hintid = CreateControlHint(playerid, xOffset, yOffset, description, control, show, textAlignment, selectable);
	return hintid;
}


// Creates a hint below the previous one
stock CreateControlHintBelow(playerid, Float:xOffset, Float:yOffset, const description[], const control[], show = CH_SHOW_HINT, textAlignment = CH_TEXT_ALIGN_LEFT, selectable = 0) {
	
	xOffset = ControlHintAnchorX[playerid] + xOffset;
	yOffset = ControlHintAnchorY[playerid] + CH_HINT_OFFSET_Y + yOffset + CH_HINT_STACK_GAP;
	
	new hintid = CreateControlHint(playerid, xOffset, yOffset, description, control, show, textAlignment, selectable);
	return hintid;
}


// Creates a hint
stock CreateControlHint(playerid, Float:x, Float:y, const description[], const control[], show = CH_SHOW_HINT, textAlignment = CH_TEXT_ALIGN_LEFT, selectable = 0) {
	
	new hintid = GetFreeControlHintSlot(playerid);
	if(hintid == CH_INVALID_ID) {
		return 0;
	}

	if(textAlignment != CH_TEXT_ALIGN_LEFT && textAlignment != CH_TEXT_ALIGN_RIGHT) {
		textAlignment = CH_TEXT_ALIGN_LEFT;
	}

	PlayerControlHint[playerid][hintid][ch_Created] = true;
	PlayerControlHint[playerid][hintid][ch_Visible] = show;
	PlayerControlHint[playerid][hintid][ch_Selectable] = selectable;
	PlayerControlHint[playerid][hintid][ch_Alignment] = textAlignment;

	format(PlayerControlHint[playerid][hintid][ch_Description], CH_DESCRIPTION_LENGTH, description);
	format(PlayerControlHint[playerid][hintid][ch_Control], CH_CONTROL_LENGTH, control);

	_CreateTextDrawControlHint(playerid, hintid, x, y);
	return hintid;
}


static stock GetFreeControlHintSlot(playerid) {

	for(new i = 1; i < CH_MAX_CONTROL_HINTS; i ++) {

		if(!PlayerControlHint[playerid][i][ch_Created]) {
			return i;
		}
	}

	return CH_INVALID_ID;
}


static stock _CreateTextDrawControlHint(playerid, hintid, Float:x, Float:y) {

	new alignment = PlayerControlHint[playerid][hintid][ch_Alignment];

	new Float:width = GetTextDrawStringWidth(PlayerControlHint[playerid][hintid][ch_Control]) * CH_LETTER_SIZE_X;
	new Float:min_width = 0.8 / CH_LETTER_SIZE_X;
	
	if(width < min_width) {
		width = min_width;
	}

	PlayerControlHint[playerid][hintid][ch_BackgroundX] = x;
	PlayerControlHint[playerid][hintid][ch_BackgroundY] = y;
	PlayerControlHint[playerid][hintid][ch_BackgroundWidth] = width + 5.5;
	PlayerControlHint[playerid][hintid][ch_BackgroundHeight] = CH_HINT_OFFSET_Y;

	PlayerControlHint[playerid][hintid][ch_TD_Background] = PlayerText:INVALID_TEXT_DRAW;
	PlayerControlHint[playerid][hintid][ch_TD_Foreground] = PlayerText:INVALID_TEXT_DRAW;
	PlayerControlHint[playerid][hintid][ch_TD_Control] = PlayerText:INVALID_TEXT_DRAW;
	PlayerControlHint[playerid][hintid][ch_TD_Description] = PlayerText:INVALID_TEXT_DRAW;

	ControlHintAnchorX[playerid] = x;
	ControlHintAnchorY[playerid] = y;

// Background
	new Float:background_x;

	if(alignment == CH_TEXT_ALIGN_LEFT) {
		background_x = x;
	}
	else if(alignment == CH_TEXT_ALIGN_RIGHT) {
		background_x = x - width + 5.0;
	}

	PlayerControlHint[playerid][hintid][ch_TD_Background] = CreatePlayerTextDraw(playerid, background_x, y, "LD_DUAL:white");
	PlayerTextDrawFont(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background], 4);
	PlayerTextDrawColor(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background], CH_BACKGROUND_COLOR);
	PlayerTextDrawUseBox(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background], 1);
	PlayerTextDrawBoxColor(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background], 0x00000000);
	PlayerTextDrawTextSize(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background], 
		PlayerControlHint[playerid][hintid][ch_BackgroundWidth], 
		PlayerControlHint[playerid][hintid][ch_BackgroundHeight]);

	PlayerControlHint[playerid][hintid][ch_TD_Foreground] = CreatePlayerTextDraw(playerid, background_x + 1.0, y + 1.0, "LD_DUAL:white");
	PlayerTextDrawFont(playerid, PlayerControlHint[playerid][hintid][ch_TD_Foreground], 4);
	PlayerTextDrawColor(playerid, PlayerControlHint[playerid][hintid][ch_TD_Foreground], CH_FOREGROUND_COLOR);
	PlayerTextDrawUseBox(playerid, PlayerControlHint[playerid][hintid][ch_TD_Foreground], 1);
	PlayerTextDrawBoxColor(playerid, PlayerControlHint[playerid][hintid][ch_TD_Foreground], 0x00000000);
	PlayerTextDrawTextSize(playerid, PlayerControlHint[playerid][hintid][ch_TD_Foreground], 
		PlayerControlHint[playerid][hintid][ch_BackgroundWidth] - 2.0, 
		PlayerControlHint[playerid][hintid][ch_BackgroundHeight] - 2.0);
	PlayerTextDrawSetSelectable(playerid, PlayerControlHint[playerid][hintid][ch_TD_Foreground], PlayerControlHint[playerid][hintid][ch_Selectable]);


// Control
	new Float:control_x;

	if(alignment == CH_TEXT_ALIGN_LEFT) {
		control_x = x + 3.0 + (width / 2);
	}
	else if(alignment == CH_TEXT_ALIGN_RIGHT) {
		control_x = x + 8.0 - (width / 2);
	}
		
	PlayerControlHint[playerid][hintid][ch_TD_Control] = CreatePlayerTextDraw(playerid, 
		control_x, 
		y + 1.8, 
		PlayerControlHint[playerid][hintid][ch_Control]);
	
	PlayerTextDrawBackgroundColor(playerid, PlayerControlHint[playerid][hintid][ch_TD_Control], 0x000000FF);
    PlayerTextDrawFont(playerid, PlayerControlHint[playerid][hintid][ch_TD_Control], 2);
	PlayerTextDrawAlignment(playerid, PlayerControlHint[playerid][hintid][ch_TD_Control], 2);
    PlayerTextDrawLetterSize(playerid, PlayerControlHint[playerid][hintid][ch_TD_Control], CH_LETTER_SIZE_X, CH_LETTER_SIZE_Y);
    PlayerTextDrawColor(playerid, PlayerControlHint[playerid][hintid][ch_TD_Control], CH_TEXT_COLOR);
    PlayerTextDrawSetProportional(playerid, PlayerControlHint[playerid][hintid][ch_TD_Control], 1);
    PlayerTextDrawSetShadow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Control], 0);


// Description
	new Float:description_x;

	if(alignment == CH_TEXT_ALIGN_LEFT) {
		description_x = x + 9.0 + width;
	}
	else if(alignment == CH_TEXT_ALIGN_RIGHT) {
		description_x = x - width + 1.0;
	}

	PlayerControlHint[playerid][hintid][ch_TD_Description] = CreatePlayerTextDraw(playerid, 
		description_x, 
		y + 1.8, 
		PlayerControlHint[playerid][hintid][ch_Description]);

	PlayerTextDrawBackgroundColor(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description], 0x00000055);
    PlayerTextDrawFont(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description], 2);
	PlayerTextDrawAlignment(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description], alignment);
    PlayerTextDrawLetterSize(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description], CH_LETTER_SIZE_X, CH_LETTER_SIZE_Y);
    PlayerTextDrawColor(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description], CH_DESCRIPTION_COLOR);
    PlayerTextDrawSetProportional(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description], 1);
    PlayerTextDrawSetShadow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description], 1);
    //PlayerTextDrawSetOutline(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description], 1);

	if(PlayerControlHint[playerid][hintid][ch_Visible] == CH_SHOW_HINT) {
		
		PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background]);
		PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Foreground]);
		PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Control]);
		PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description]);

		//PlayerControlHint[playerid][hintid][ch_Visible] = CH_SHOW_HINT;
	}

	return hintid;
}



stock SetControlHintAnchorX(playerid, hintid, Float:offset = 0.0) {

    if(!IsControlHintValid(playerid, hintid)) {
		return 0;
	}
	
	new Float:X = PlayerControlHint[playerid][hintid][ch_BackgroundX];

	if(offset != 0.0) {
		X += offset;
	}

    ControlHintAnchorX[playerid] = X;
    return 1;
}



stock SetControlHintAnchorY(playerid, hintid, Float:offset = 0.0) {

    if(!IsControlHintValid(playerid, hintid)) {
		return 0;
	}

	new Float:Y = PlayerControlHint[playerid][hintid][ch_BackgroundY];

	if(offset != 0.0) {
        Y += offset;
    }

    ControlHintAnchorY[playerid] = Y;
    return 1;
}


static stock _DestroyTextDrawControlHint(playerid, hintid) {

	PlayerTextDrawDestroy(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background]);
	PlayerTextDrawDestroy(playerid, PlayerControlHint[playerid][hintid][ch_TD_Foreground]);
	PlayerTextDrawDestroy(playerid, PlayerControlHint[playerid][hintid][ch_TD_Control]);
	PlayerTextDrawDestroy(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description]);

	PlayerControlHint[playerid][hintid][ch_TD_Background] = PlayerText:INVALID_TEXT_DRAW;
	PlayerControlHint[playerid][hintid][ch_TD_Foreground] = PlayerText:INVALID_TEXT_DRAW;
	PlayerControlHint[playerid][hintid][ch_TD_Control] = PlayerText:INVALID_TEXT_DRAW;
	PlayerControlHint[playerid][hintid][ch_TD_Description] = PlayerText:INVALID_TEXT_DRAW;

	return 1;
} 


stock DestroyControlHint(playerid, &hintid) { 

	if(!IsControlHintValid(playerid, hintid)) {
		hintid = 0;
		return 0;
	}

	PlayerControlHint[playerid][hintid][ch_Created] = false;
	PlayerControlHint[playerid][hintid][ch_Visible] = CH_HIDE_HINT;

	_DestroyTextDrawControlHint(playerid, hintid);

	if(PlayerControlHint[playerid][hintid][ch_AnimationTimer]) {
		KillTimer(PlayerControlHint[playerid][hintid][ch_AnimationTimer]);
		PlayerControlHint[playerid][hintid][ch_AnimationTimer] = 0;
	}

	if(PlayerControlHint[playerid][hintid][ch_HighlightTimer]) {
		KillTimer(PlayerControlHint[playerid][hintid][ch_HighlightTimer]);
		PlayerControlHint[playerid][hintid][ch_HighlightTimer] = 0;
	}

	hintid = 0;
	return 1;
}



stock DestroyAllControlHints(playerid) {
	new hintid;

	for(new i = 1; i < CH_MAX_CONTROL_HINTS; i ++) {
		hintid = i;
		DestroyControlHint(playerid, hintid);
	}
	return 1;
}



stock IsControlHintValid(playerid, hintid) {
	if(hintid <= 0 || hintid >= CH_MAX_CONTROL_HINTS) {
		return 0;
	}

	return PlayerControlHint[playerid][hintid][ch_Created];
}



stock SetControlHintPosition(playerid, hintid, Float:x, Float:y, show = CH_SHOW_HINT) {
	if(!IsControlHintValid(playerid, hintid)) {
		return 0;
	}
	
	_DestroyTextDrawControlHint(playerid, hintid);

	PlayerControlHint[playerid][hintid][ch_Visible] = show;
	_CreateTextDrawControlHint(playerid, hintid, x, y);
	return 1;
}



stock GetControlHintPosition(playerid, hintid, &Float:x, &Float:y, Float:xOffset = 0.0, Float:yOffset = 0.0) {
	if(!IsControlHintValid(playerid, hintid)) {
		return 0;
	}

	x = PlayerControlHint[playerid][hintid][ch_BackgroundX];
	y = PlayerControlHint[playerid][hintid][ch_BackgroundY];

	if(xOffset != 0.0) {
		x += xOffset;
	}

	if(yOffset != 0.0) {
		y += yOffset;
	}

	return 1;
}



stock ShowControlHint(playerid, hintid) {
	if(!IsControlHintValid(playerid, hintid)) {
		return 0;
	}

	if(IsControlHintVisible(playerid, hintid)) {
		return 0;
	}

	PlayerControlHint[playerid][hintid][ch_Visible] = CH_SHOW_HINT;
	
	PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background]);
	PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Foreground]);
	PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Control]);
	PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description]);

	return 1;
}



stock HideControlHint(playerid, hintid) {
	if(!IsControlHintValid(playerid, hintid)) {
		return 0;
	}
	
	if(!IsControlHintVisible(playerid, hintid)) {
		return 0;
	}

	PlayerControlHint[playerid][hintid][ch_Visible] = CH_HIDE_HINT;
	
	PlayerTextDrawHide(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background]);
	PlayerTextDrawHide(playerid, PlayerControlHint[playerid][hintid][ch_TD_Foreground]);
	PlayerTextDrawHide(playerid, PlayerControlHint[playerid][hintid][ch_TD_Control]);
	PlayerTextDrawHide(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description]);

	return 1;
}



stock IsControlHintVisible(playerid, hintid) {
	if(!IsControlHintValid(playerid, hintid)) {
		return 0;
	}

	return PlayerControlHint[playerid][hintid][ch_Visible];
}



stock HideAllControlHints(playerid, bool:remember = false) {

	for(new hintid = 1; hintid < CH_MAX_CONTROL_HINTS; hintid ++) {

		if(!IsControlHintValid(playerid, hintid)) {
			continue;
		}

		if(PlayerControlHint[playerid][hintid][ch_Visible] == CH_HIDE_HINT) {
			PlayerControlHint[playerid][hintid][ch_SavedVisible] = (remember) ? true : false;
			continue;
		}

		PlayerControlHint[playerid][hintid][ch_Visible] = CH_HIDE_HINT;
		PlayerControlHint[playerid][hintid][ch_SavedVisible] = false;
	
		PlayerTextDrawHide(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background]);
		PlayerTextDrawHide(playerid, PlayerControlHint[playerid][hintid][ch_TD_Foreground]);
		PlayerTextDrawHide(playerid, PlayerControlHint[playerid][hintid][ch_TD_Control]);
		PlayerTextDrawHide(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description]);
	}

	return 1;
}



stock ShowAllControlHints(playerid) {

	for(new hintid = 1; hintid < CH_MAX_CONTROL_HINTS; hintid ++) {

		if(!IsControlHintValid(playerid, hintid)) {
			continue;
		}

		if(PlayerControlHint[playerid][hintid][ch_SavedVisible]) {
			continue;
		}

		PlayerControlHint[playerid][hintid][ch_Visible] = CH_SHOW_HINT;
	
		PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background]);
		PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Foreground]);
		PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Control]);
		PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description]);
	}

	return 1;
}



stock UpdateControlHintText(playerid, hintid, const description[], const control[] = "", show = CH_SHOW_HINT) {
	
	if(!IsControlHintValid(playerid, hintid)) {
		return 0;
	}

	if(strlen(description) >= 1) {

		format(PlayerControlHint[playerid][hintid][ch_Description], CH_DESCRIPTION_LENGTH, description);
		PlayerTextDrawSetString(playerid, PlayerControlHint[playerid][hintid][ch_TD_Description], description);
	}

	if(strlen(control) >= 1) {
		format(PlayerControlHint[playerid][hintid][ch_Control], CH_CONTROL_LENGTH, control);

		_DestroyTextDrawControlHint(playerid, hintid);
		_CreateTextDrawControlHint(playerid, hintid, PlayerControlHint[playerid][hintid][ch_BackgroundX], PlayerControlHint[playerid][hintid][ch_BackgroundY]);
	}

	if(show == CH_SHOW_HINT) {
		ShowControlHint(playerid, hintid);
	}
	else {
		HideControlHint(playerid, hintid);
	}
	return 1;
}



stock StartControlHintAnimation(playerid, hintid, backgroundColor, Float:speed = 15.0) {
	
	if(!IsControlHintValid(playerid, hintid)) {
		return 0;
	}

	if(IsControlHintAnimating(playerid, hintid)) {
		return 0;
	}

	speed = speed * 0.03;

	PlayerControlHint[playerid][hintid][ch_AnimationHeight] = 0.0;
	PlayerControlHint[playerid][hintid][ch_AnimationTimer] = SetTimerEx("CH_Animation_Tick", 30, true, "dddf", playerid, hintid, backgroundColor, speed);
	return 1;
}



stock IsControlHintAnimating(playerid, hintid) {
	if(!IsControlHintValid(playerid, hintid)) {
		return 0;
	}

	if(!PlayerControlHint[playerid][hintid][ch_AnimationTimer]) {
		return 0;
	}

	return 1;
}


forward CH_Animation_Tick(playerid, hintid, backgroundColor, Float:speed);
public CH_Animation_Tick(playerid, hintid, backgroundColor, Float:speed) {

	if(!IsControlHintValid(playerid, hintid)) {
		return 0;
	}


	PlayerControlHint[playerid][hintid][ch_AnimationHeight] += speed;
	if(PlayerControlHint[playerid][hintid][ch_AnimationHeight] > PlayerControlHint[playerid][hintid][ch_BackgroundHeight]) {

		StopControlHintAnimation(playerid, hintid);

		#if defined OnPlayerControlHintAnimationEnd
			OnPlayerControlHintAnimationEnd(playerid, hintid); 
		#endif
		return 1;
	}


	PlayerTextDrawColor(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background], backgroundColor);
	PlayerTextDrawTextSize(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background], 
		PlayerControlHint[playerid][hintid][ch_BackgroundWidth], 
		PlayerControlHint[playerid][hintid][ch_AnimationHeight]);

	if(IsControlHintVisible(playerid, hintid)) {
		PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background]);
	}
	return 1;
}



stock StopControlHintAnimation(playerid, hintid) {

	if(!IsControlHintValid(playerid, hintid)) {
		return 0;
	}

	if(!IsControlHintAnimating(playerid, hintid)) {
		return 0;
	}
	
	KillTimer(PlayerControlHint[playerid][hintid][ch_AnimationTimer]);
	PlayerControlHint[playerid][hintid][ch_AnimationTimer] = 0;


	PlayerTextDrawColor(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background], CH_BACKGROUND_COLOR);
	PlayerTextDrawTextSize(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background], 
		PlayerControlHint[playerid][hintid][ch_BackgroundWidth], 
		PlayerControlHint[playerid][hintid][ch_BackgroundHeight]);

	if(IsControlHintVisible(playerid, hintid)) {
		PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background]);
	}
	return 1;
}



stock HighlightControlHintBackground(playerid, hintid, backgroundColor, timeout = 1000) {
	
	if(!IsControlHintValid(playerid, hintid)) {
		return 0;
	}
		
	if(PlayerControlHint[playerid][hintid][ch_HighlightTimer]) 
		return 0;

	if(!IsControlHintVisible(playerid, hintid)) {
		return 0;
	}	

	PlayerTextDrawColor(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background], backgroundColor);
	PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background]);

	PlayerControlHint[playerid][hintid][ch_HighlightTimer] = SetTimerEx("CH_HighlightBackgroundEnd", timeout, false, "dd", playerid, hintid);
	return 1;
}



forward CH_HighlightBackgroundEnd(playerid, hintid);
public CH_HighlightBackgroundEnd(playerid, hintid) {

	if(!IsControlHintValid(playerid, hintid)) {
		return 0;
	}

	PlayerControlHint[playerid][hintid][ch_HighlightTimer] = 0;
	PlayerTextDrawColor(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background], CH_BACKGROUND_COLOR);

	if(IsControlHintVisible(playerid, hintid)) {
		PlayerTextDrawShow(playerid, PlayerControlHint[playerid][hintid][ch_TD_Background]);
	}
	return 1;
}


// Function for wrapping text while preserving existing line breaks (~n~) and color codes (~r~, ~b~, ~l~, ~p~, etc.).
stock WordWrapTextDrawString(const text[], output[], 
    Float:letterSizeX, Float:letterSizeY, 
    Float:maxWidth, const paste[] = "~n~", maxLineCount = 0, bool:dotsEnd = false, 
    &Float:width = 0.0, &Float:height = 0.0, &Float:totalWidth = 0.0, size_text = sizeof(output)) 
{
    width = 0.0;
    height = 0.0;
    totalWidth = 0.0;

    new textLength = strlen(text),
        lineCount, 
        lastBreakPos, 
        Float:lastBreakWidth, 
        Float:currentLineWidth,
        skipChars;

    strmid(output, text, 0, textLength, size_text);

    for(new x; x < textLength; x++) {

        if(skipChars >= 1) {
            skipChars --;
            continue;
        }

        // Handle existing line breaks (~n~)
        if((output[x] == '~' && x <= textLength - 3 && (output[x + 1] == 'n' || output[x + 1] == 'N') && output[x + 2] == '~')) {
            skipChars = 2;

            // Save the maximum line width
            if(currentLineWidth > totalWidth) {
                totalWidth = currentLineWidth;
            }

            currentLineWidth = 0.0;
            lastBreakPos = 0;
            lastBreakWidth = 0.0;
            lineCount++;
            continue;
        }

        // Skip color symbols ~r~ ~b~ ~l~ ~p~
        if(output[x] == '~' && x <= textLength - 3) {
            new next = output[x + 1];

            if(next == 'r' || next == 'g' || next == 'b' || next == 'y' || next == 'w' || next == 'l' || next == 'p' || next == 'h') {
                skipChars = 2;
                continue;
            }
        }

        currentLineWidth += CH_GetTextDrawCharacterWidth(output[x]) * letterSizeX;

        if(currentLineWidth >= maxWidth) {

            // Save the width of completed line BEFORE subtracting
            new Float:widthBeforeWrap = (lastBreakPos != 0 && lastBreakWidth > 0.0) ? lastBreakWidth : currentLineWidth;

            if(widthBeforeWrap > totalWidth) {
                totalWidth = widthBeforeWrap;
            }

            // Check for maximum line count
            if(maxLineCount != 0 && lineCount >= maxLineCount - 1) {

                if(dotsEnd == true) {
                    new w_pos = (lastBreakPos) ? lastBreakPos : x;
                    strins(output, "...", w_pos - 1, size_text);
                    strdel(output, w_pos + 2, size_text);
                }
                break;
            }

            // We check if there is enough space for insertion
            if(strlen(output) + strlen(paste) >= size_text) {
                break;
            }

            // Insert line break
            if(!lastBreakPos) {
                // If there is no suitable place for wrapping, wrap at the current position

                // add a hyphen to indicate a word wrap
                strins(output, "-", x, 1);

                //insert a line break after the hyphen
                strins(output, paste, x + 1, 3);

                textLength += strlen(paste) + 1; // +1 for hyphen
                currentLineWidth = 0.0;
            }
            else {
                strins(output, paste, lastBreakPos, 3);
                textLength += strlen(paste);

                // Subtract the wrapped part, leaving the remainder of the line
                currentLineWidth -= lastBreakWidth;
            }

            lineCount++;
            skipChars = 2;
            lastBreakPos = 0;
            lastBreakWidth = 0.0;
        }
        else if(output[x] == ' ' || output[x] == ',' || output[x] == '.') {
            // Remember the position for wrapping
            lastBreakPos = x + 1;
            lastBreakWidth = currentLineWidth;
        }
    }

    // Check the last line
    if(currentLineWidth > totalWidth) {
        totalWidth = currentLineWidth;
    }

    // Calculate the height of the text
    height = (lineCount + 1) * (9.0 * letterSizeY);
    
    // Final width - the maximum of all lines
    width = totalWidth;
}


public OnPlayerConnect(playerid) {

	ControlHintAnchorX[playerid] = 0.0;
	ControlHintAnchorY[playerid] = 0.0;

	for(new hintid; hintid < CH_MAX_CONTROL_HINTS; hintid ++) {
		PlayerControlHint[playerid][hintid][ch_Created] = false;
	}

    #if defined CH_OnPlayerConnect
        return CH_OnPlayerConnect(playerid);
	#else
    	return 1;
    #endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect CH_OnPlayerConnect
#if defined CH_OnPlayerConnect
    forward CH_OnPlayerConnect(playerid);
#endif


public OnPlayerDisconnect(playerid, reason) {

	DestroyAllControlHints(playerid);

    #if defined CH_OnPlayerDisconnect
        return CH_OnPlayerDisconnect(playerid, reason);
	#else
    	return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect CH_OnPlayerDisconnect
#if defined CH_OnPlayerDisconnect
    forward CH_OnPlayerDisconnect(playerid, reason);
#endif



public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid) {

	for(new hintid = 1; hintid < CH_MAX_CONTROL_HINTS; hintid ++) {

		if(!IsControlHintValid(playerid, hintid)) {
			continue;
		}

		if(!IsControlHintVisible(playerid, hintid)) {
			continue;
		}

		if(playertextid != PlayerControlHint[playerid][hintid][ch_TD_Foreground]) {
			continue;
		}

		#if defined OnPlayerControlHintClicked
			OnPlayerControlHintClicked(playerid, hintid);
		#endif
		return 1;
	}
	
	#if defined CH_OnPlayerClickPlayerTextDraw
        return CH_OnPlayerClickPlayerTextDraw(playerid, playertextid);
	#else
		return 1;
    #endif
}
#if defined _ALS_OnPlayerClickPlayerTextDra
    #undef OnPlayerClickPlayerTextDraw
#else
    #define _ALS_OnPlayerClickPlayerTextDra
#endif
#define OnPlayerClickPlayerTextDraw CH_OnPlayerClickPlayerTextDraw
#if defined CH_OnPlayerClickPlayerTextDraw
    forward CH_OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid);
#endif

