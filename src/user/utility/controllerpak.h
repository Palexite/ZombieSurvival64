#include "cpakfs.h"
#include "controller.h"
#include "stdio.h"
#include <string>
#include <vector>

#define GAMECODE "GMZS"
#define PUBLISHERCODE "13"

#define CPAK_USERNAME_SIZE 16

#define CPAK_XP_OFFSET 17
#define CPAK_XP_SIZE 4

#define CPAK_LEVEL_OFFSET 22
#define CPAK_LEVEL_SIZE 1

#define CPAK_REMORTLEVEL_OFFSET 24
#define CPAK_REMORTLEVEL_SIZE 8

#define CPAK_POINTSAVEBANK_OFFSET 32
#define CPAK_POINTSAVEBANK_SIZE 4

#define CPAK_HIGHSCORE_OFFSET 32
#define CPAK_HIGHSCORE_SIZE 8

#define CPAK_SKILLS_OFFSET 40
#define CPAK_SKILLS_BOUND 128

struct PlayerData {
    char username[CPAK_USERNAME_SIZE];
    uint32_t xp = 0;
    uint8_t level = 1;
    uint64_t remortLevel = 0;
    uint64_t highScore = 0;
    uint32_t pointsaveBank = 512;
    std::vector<uint8_t> skills{};
};

namespace controllerpak {


    /// @brief Player data translated from their ControllerPak. This is what is acknowledged by the game when trying to get information about a player's progress.
    // Index corresponds to the port in which the ControllerPak is connected to.
    extern PlayerData CachedPlayerData[];

    extern bool portHasCPak(joypad_port_t port);

    extern int mountCPak(int port);

    extern void FormatPlayerData(int port);

    /// @brief read the player's data. On success, the data read here is also cached into CachedPlayerData.
    /// @param port The port to read from (NOTE: Call PortHasCPak and mountCPak to make sure it has a controller pak and that it is mounted!)
    /// @return Returns set of characters representing bytes. Will return nullptr if anything fails. 
    extern PlayerData readPlayerData(int port);

    /// @brief Shortcut to grab a player's username directly from their controllerPak.
    /// @param port Username to retrieve 
    /// @return 
    extern std::string getPlayerUserName(int port);

    /// @brief Performs a comprehensive save to the designated port's controller pak.
    /// @param pData The data to write to the controller pak.
    /// @param port The port in which the controller pak is located.
    extern int fullSaveToPak(PlayerData pData, int port);

    extern uint32_t getRequiredXPToLevel(uint8_t level);
}







