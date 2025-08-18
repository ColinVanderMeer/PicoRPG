#ifndef _CORE_H
#define _CORE_H

#include <stdbool.h>
#include <hagl_hal.h>
#include <hagl.h>

typedef enum GameState {
  GAME_STATE_TITLE,
  GAME_STATE_NORMAL,
  GAME_STATE_MENU,
  GAME_STATE_TEXTBOX,
  GAME_STATE_FISHING,
  GAME_STATE_PC,
} GameState;

extern GameState game_state;

extern bool fish_hooked;

typedef enum fish_list {
	FISH_CLOWN, FISH_COD, FISH_SALMON, FISH_PUFFERFISH, FISH_TUNA, FISH_SEA_BASS, FISH_CATFISH,
	FISH_PIG_FISH, FISH_SINGING_FISH, FISH_MACHINE_FISH, FISH_DRIMP, FISH_SHARK,
	FISH_ORPHEUS, FISH_AT_FISH, FISH_MAGICAL_FROG,
	FISH_COUNT  // Total number of fish types
} fish_list;

typedef struct {
	float min_weight;
	float max_weight;
} weight_range_t;

typedef struct {
	const char* name;
	weight_range_t weight;
  void* texture;
	const char* description;
} fish_data_t;

extern const fish_data_t fish_data[FISH_COUNT];

#endif // _CORE_H