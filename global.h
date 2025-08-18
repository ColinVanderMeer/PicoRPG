#ifndef _CORE_H
#define _CORE_H

typedef enum GameState {
  GAME_STATE_TITLE,
  GAME_STATE_NORMAL,
  GAME_STATE_MENU,
  GAME_STATE_TEXTBOX,
  GAME_STATE_FISHING,
  GAME_STATE_PC,
} GameState;

extern GameState game_state;

#endif // _CORE_H