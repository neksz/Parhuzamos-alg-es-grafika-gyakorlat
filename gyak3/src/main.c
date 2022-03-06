#include "game.h"

/**
 * Main function
 */
int main(int argc, char *argv[])
{
    Game game;

    do
    {
        init_game(&game, 800, 600);
        while (game.is_running)
        {
            handle_game_events(&game);
            update_game(&game);
            render_game(&game);
        }
        destroy_game(&game);
    } while (game.pong.restart == 1);

    return 0;
}
