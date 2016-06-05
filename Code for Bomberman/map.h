#pragma once
#define WIN32_LEAN_AND_MEAN

#include "constants.h"

      const int MAP_HEIGHT = 13;
      const int MAP_WIDTH = 20;
	  const enum tile { r,__, w, b, f};

	  inline int coordinatesInTile(float coordinate) { return static_cast<int>(coordinate) / TEXTURE_SIZE; }
	  #define IN_MAP coordinatesInTile

	  inline float coordinatesFromTile(int row_or_column) { return static_cast<float>(row_or_column) * TEXTURE_SIZE; }
	  #define FROM_MAP coordinatesFromTile

	extern tile tileMap[MAP_HEIGHT][MAP_WIDTH];

