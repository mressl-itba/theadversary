/**
 * The Adversary
 * Game UI mode
 * 
 * @details This module runs the game in UI mode.
 * @author The dark net programmers
 */

#include "ui/ui.h"
#include "game/agent.h"
#include "starter_agent/starter_agent.h"
#include "greedy_agent/greedy_agent.h"

/**
 * @brief Main entry point of the application
 */
int main(int argc, char *argv[])
{
    // Load the agents
    AgentInstance agent_instances[2];

    LoadAgentInstance(agent_instances[0], starter_agent);
    LoadAgentInstance(agent_instances[1], greedy_agent);

    // Initialize the UI
    LoadUI(agent_instances);

    while(true)
    {
        if (!UpdateUI())
            break;
    }

    // Unload the UI
    UnloadUI();

    // Unload the agents
    UnloadAgentInstance(agent_instances[0]);
    UnloadAgentInstance(agent_instances[1]);
}
