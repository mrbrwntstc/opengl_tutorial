#ifndef __GAME__
#define __GAME__

enum GameState
{
  GAME_ACTIVE,
  GAME_MENU,
  GAME_WIN
};

class Game
{
public: // fields
  GameState GameState;
  bool Keys[1024];
  unsigned int Width;
  unsigned int Height;
public: // methods
  Game(unsigned int width, unsigned int height);
  ~Game();
  void Init();
  void ProcessInput(float dt);
  void Update(float dt);
  void Render();
};

#endif // __GAME__
