#pragma once
#ifndef _CONSTANTS_H            // Prevent multiple definitions if this
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string>

//=============================================================================
//                  Constants
//=============================================================================

// window
const char CLASS_NAME[] = "Bomberman";
const char GAME_TITLE[] = "Bomberman";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH = 1280;						// width of game in pixels
const UINT GAME_HEIGHT = 832;						// height of game in pixels

// game
const int TEXTURE_SIZE = 64;
const int TEXTURE_COLS = 1;

const bool VSYNC = false;                   // true locks display to vertical sync rate
const float FRAME_RATE = 240.0f;            // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const double PI = 3.14159265;

// graphic images
const std::string BACKGROUND_IMAGE		= "pictures\\background.png";
const std::string ROCK_IMAGE			= "pictures\\rock.png";
const std::string WOOD_IMAGE			= "pictures\\wood.png";
const std::string BOMB_IMAGE			= "pictures\\bomb.png";
const std::string FIRE_IMAGE			= "pictures\\fire.png";
const std::string MAN_IMAGE				= "pictures\\man.png";
const std::string ENEMY_IMAGE			= "pictures\\enemy.png";
const std::string SMARTENEMY_IMAGE		= "pictures\\smartenemy.png";
const std::string ASTARENEMY_IMAGE		= "pictures\\astarenemy.png";
const std::string HEART_IMAGE			= "pictures\\heart.png";
const std::string BONUSBOMB_IMAGE		= "pictures\\bonusbomb.png";
const std::string BONUSEXPLOSION_IMAGE	= "pictures\\bonusexplosion.png";

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "";
// XGS_FILE must be location of .xgs file.
const char XGS_FILE[]   = "";

// audio cues

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY  = '`';         // ` key
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key
const UCHAR BACKSPACE_KEY = VK_SPACE;
const UCHAR LEFT_KEY    = 0x41;     // left arrow
const UCHAR RIGHT_KEY   = 0x44;    // right arrow
const UCHAR UP_KEY      = 0x57;       // up arrow
const UCHAR DOWN_KEY    = 0x53;     // down arrow

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    {
        ptr->Release();
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    {
        delete ptr;
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    {
        delete[] ptr;
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice();
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice();
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

#endif
