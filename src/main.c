#include <game/game.h>
#include <game/window.h>

int main() {

  struct window window_hints = {480, 640,"RONG: pong but RENGENINED"};
  GLFWwindow* window = window_init(window_hints);

  game_run(window);

  game_shutdown(window);
  window_shutdown(window);

  return 0;
};
