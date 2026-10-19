/**
 * The Adversary
 * Game headless mode
 *
 * @details This module runs a Reversi game in headless mode.
 * @author The dark net programmers
 */

#include <iostream>

#include "game/game.h"

#include "starter_agent/starter_agent.h"
#include "greedy_agent/greedy_agent.h"

/**
 * @brief Prints the current board of the game to the console.
 */
void PrintBoard(const Game &game)
{
    for (int32_t y = 0; y < BOARD_SIZE; y++)
    {
        for (int32_t x = 0; x < BOARD_SIZE; x++)
        {
            GameSquare square = GetGameSquare(game, {x, y});
            char symbol = '.';
            if (square == SQUARE_BLACK)
                symbol = 'B';
            else if (square == SQUARE_WHITE)
                symbol = 'W';

            std::cout << symbol << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Black: " << GetGameScore(game, SQUARE_BLACK) << "  White: " << GetGameScore(game, SQUARE_WHITE) << std::endl;
}

/**
 * @brief Function that the agents should call to check if a stop has been requested by the game engine. In this headless implementation, we will never request a stop, so this function always returns false.
 */
bool StopRequested()
{
    return false;
}

/**
 * @brief Main entry point of the application
 */
int main(int argc, char *argv[])
{
    // Initialize the game state
    Game game;

    InitializeGame(game);

    // Load the agents
    AgentInstance agent_instances[2];

    LoadAgentInstance(agent_instances[0], starter_agent);
    LoadAgentInstance(agent_instances[1], greedy_agent);

    // Main game loop
    bool game_over = false;
    while (!game_over)
    {
        std::cout << ".";

        GameStatus status = GetGameStatus(game);
        GamePosition next_move;

        switch (status)
        {
        case GAME_BLACK_PLAYS:
            next_move = agent_instances[0].descriptor->get_next_move(agent_instances[0].state, game, StopRequested);
            PlayMove(game, next_move);

            break;

        case GAME_WHITE_PLAYS:
            next_move = agent_instances[1].descriptor->get_next_move(agent_instances[1].state, game, StopRequested);
            PlayMove(game, next_move);

            break;

        case GAME_BLACK_WINS:
            std::cout << "Black wins!" << std::endl;
            game_over = true;

            break;

        case GAME_WHITE_WINS:
            std::cout << "White wins!" << std::endl;
            game_over = true;

            break;

        case GAME_DRAW:
            std::cout << "It's a draw!" << std::endl;
            game_over = true;

            break;

        default:
            break;
        }
    }

    std::cout << std::endl;

    PrintBoard(game);

    UnloadAgentInstance(agent_instances[0]);
    UnloadAgentInstance(agent_instances[1]);

    return GetGameScore(game, SQUARE_BLACK);
}
