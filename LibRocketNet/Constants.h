#pragma once

namespace LibRocketNet {

public enum class KeyIdentifiers {

	Unknown = 0,

	Space = 1,

	Num0 = 2,
	Num1 = 3,
	Num2 = 4,
	Num3 = 5,
	Num4 = 6,
	Num5 = 7,
	Num6 = 8,
	Num7 = 9,
	Num8 = 10,
	Num9 = 11,

	A = 12,
	B = 13,
	C = 14,
	D = 15,
	E = 16,
	F = 17,
	G = 18,
	H = 19,
	I = 20,
	J = 21,
	K = 22,
	L = 23,
	M = 24,
	N = 25,
	O = 26,
	P = 27,
	Q = 28,
	R = 29,
	S = 30,
	T = 31,
	U = 32,
	V = 33,
	W = 34,
	X = 35,
	Y = 36,
	Z = 37,

	Oem1 = 38,				// US standard keyboard; the ';:' key.
	OemPlus = 39,			// Any region; the '=+' key.
	OemComma = 40,			// Any region; the ',<' key.
	OemMinus = 41,			// Any region; the '-_' key.
	OemPeriod = 42,			// Any region; the '.>' key.
	Oem2 = 43,				// Any region; the '/?' key.
	Oem3 = 44,				// Any region; the '`~' key.

	Oem4 = 45,				// US standard keyboard; the '[{' key.
	Oem5 = 46,				// US standard keyboard; the '\|' key.
	Oem6 = 47,				// US standard keyboard; the ']}' key.
	Oem7 = 48,				// US standard keyboard; the ''"' key.
	Oem8 = 49,

	Oem102 = 50,			// RT 102-key keyboard; the '<>' or '\|' key.

	Numpad0 = 51,
	Numpad1 = 52,
	Numpad2 = 53,
	Numpad3 = 54,
	Numpad4 = 55,
	Numpad5 = 56,
	Numpad6 = 57,
	Numpad7 = 58,
	Numpad8 = 59,
	Numpad9 = 60,
	NumpadENTER = 61,
	Multiply = 62,			// Asterisk on the numeric keypad.
	Add = 63,				// Plus on the numeric keypad.
	Separator = 64,
	Subtract = 65,			// Minus on the numeric keypad.
	Decimal = 66,			// Period on the numeric keypad.
	Divide = 67,				// Forward Slash on the numeric keypad.

	/*
		* NEC PC-9800 kbd definitions
		*/
	OemNecEqual = 68,		// Equals key on the numeric keypad.

	Back = 69,				// Backspace key.
	Tab = 70,				// Tab key.

	Clear = 71,
	Return = 72,

	Pause = 73,
	Capital = 74,			// Capslock key.

	Kana = 75,				// IME Kana mode.
	Hangul = 76,				// IME Hangul mode.
	Junja = 77,				// IME Junja mode.
	Final = 78,				// IME final mode.
	Hanja = 79,				// IME Hanja mode.
	Kanji = 80,				// IME Kanji mode.

	Escape = 81,				// Escape key.

	Convert = 82,			// IME convert.
	NonConvert = 83,			// IME nonconvert.
	Accept = 84,				// IME accept.
	ModeChange = 85,			// IME mode change request.

	PageUp = 86,				// Page Up key.
	PageDown = 87,				// Page Down key.
	End = 88,
	Home = 89,
	Left = 90,				// Left Arrow key.
	Up = 91,					// Up Arrow key.
	Right = 92,				// Right Arrow key.
	Down = 93,				// Down Arrow key.
	Select = 94,
	Print = 95,
	Execute = 96,
	Snapshot = 97,			// Print Screen key.
	Insert = 98,
	Delete = 99,
	Help = 100,

	LWin = 101,				// Left Windows key.
	RWin = 102,				// Right Windows key.
	Apps = 103,				// Applications key.

	Power = 104,
	Sleep = 105,
	Wake = 106,

	F1 = 107,
	F2 = 108,
	F3 = 109,
	F4 = 110,
	F5 = 111,
	F6 = 112,
	F7 = 113,
	F8 = 114,
	F9 = 115,
	F10 = 116,
	F11 = 117,
	F12 = 118,
	F13 = 119,
	F14 = 120,
	F15 = 121,
	F16 = 122,
	F17 = 123,
	F18 = 124,
	F19 = 125,
	F20 = 126,
	F21 = 127,
	F22 = 128,
	F23 = 129,
	F24 = 130,

	NumLock = 131,			// Numlock key.
	ScrollLock = 132,			// Scroll Lock key.

	/*
		* Fujitsu/OASYS kbd definitions
		*/
	OemFJ_Jisho = 133,		// 'Dictionary' key.
	OemFJ_Masshou = 134,	// 'Unregister word' key.
	OemFJ_Touroku = 135,	// 'Register word' key.
	OemFJ_LOya = 136,		// 'Left OYAYUBI' key.
	OemFJ_ROya = 137,		// 'Right OYAYUBI' key.

	LShift = 138,
	RShift = 139,
	LControl = 140,
	RControl = 141,
	LMenu = 142,
	RMenu = 143,

	BrowserBack = 144,
	BrowserForward = 145,
	BrowserRefresh = 146,
	BrowserStop = 147,
	BrowserSearch = 148,
	BrowserFavorites = 149,
	BrowserHome = 150,

	VolumeMute = 151,
	VolumeDown = 152,
	VolumeUp = 153,
	MediaNextTrack = 154,
	MediaPrevTrack = 155,
	MediaStop = 156,
	MediaPlayPause = 157,
	LaunchMail = 158,
	LaunchMediaSelect = 159,
	LaunchApp1 = 160,
	LaunchApp2 = 161,

	/*
		* Various extended or enhanced keyboards
		*/
	OemAX = 162,
	IcoHelp = 163,
	Ico00 = 164,

	ProcessKey = 165,		// IME Process key.

	IcoClear = 166,

	Attn = 167,
	Crsel = 168,
	Exsel = 169,
	Ereof = 170,
	Play = 171,
	Zeoom = 172,
	PA1 = 173,
	OemClear = 174,

	LMeta = 175,
	RMeta = 176
};


[System:Flags]
public enum class KeyModifier
{
	Control = 1 << 0,		// Set if at least one Ctrl key is depressed.
	Shift = 1 << 1,		// Set if at least one Shift key is depressed.
	Alt = 1 << 2,		// Set if at least one Alt key is depressed.
	Meta = 1 << 3,		// Set if at least one Meta key (the command key) is depressed.
	Capslock = 1 << 4,	// Set if caps lock is enabled.
	Numlock = 1 << 5,	// Set if num lock is enabled.
	ScrollLock = 1 << 6	// Set if scroll lock is enabled.
};

}