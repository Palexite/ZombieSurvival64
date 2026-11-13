#include "controllerpak.h"
#include "stdlib.h"
#include "libdragon.h"

#define SAVEPATH "cpak" + std::to_string(port) + ":/" + GAMECODE + "." + PUBLISHERCODE + "-ZOMBIESURVIVAL.A";


namespace controllerpak {


    PlayerData CachedPlayerData[4];


    bool portHasCPak(joypad_port_t port) {
        int accessory_0 = joypad_get_accessory_type(port);
         debugf("Accessory type at port %d: %d\n", port, accessory_0);
    if (accessory_0 == 2) { 
        return true;
    }
    return false;
    }



    int mountCPak(int port) {

        std::string prefix = "cpak" + std::to_string(port) + ":/";

        joypad_port_t joypadPort = static_cast<joypad_port_t>(port-1);

        CachedPlayerData[port] = {};

        debugf("new mount path for port %d: %s\n", port, prefix.c_str());
        return cpakfs_mount(joypadPort, prefix.c_str());
    }




    void FormatPlayerData(int port) {
        std::string prefix = SAVEPATH;
        FILE* playerDataFile = fopen(prefix.c_str(), "wb");

        debugf("Attempting to write to path: %s\n", prefix.c_str());

        if(!playerDataFile) {
            debugf("Failed to write player %d's data. Aborting.\n", port);
            return;
        }

        // DEFAULT VALUES
        debugf("SUCCESSFULLY FOUND player %d's data. Writing.\n", port);
        fwrite("PLAYER", 1,  CPAK_USERNAME_SIZE, playerDataFile);

        int XP = 0;
        fseek(playerDataFile, CPAK_XP_OFFSET, SEEK_SET);
        fwrite(&XP, CPAK_XP_SIZE, 1, playerDataFile);


        int level = 1;
        fseek(playerDataFile, CPAK_LEVEL_OFFSET, SEEK_SET);
        fwrite(&level, CPAK_LEVEL_SIZE, 1, playerDataFile);


        int remortLevel = 0;
        fseek(playerDataFile, CPAK_REMORTLEVEL_OFFSET, SEEK_SET);
        fwrite(&remortLevel, CPAK_REMORTLEVEL_SIZE, 1, playerDataFile);


        int pointsaveBank = 512;
        fseek(playerDataFile, CPAK_POINTSAVEBANK_OFFSET, SEEK_SET);
        fwrite(&pointsaveBank, CPAK_POINTSAVEBANK_SIZE, 1, playerDataFile);


        int highScore = 0;
        fseek(playerDataFile, CPAK_HIGHSCORE_OFFSET, SEEK_SET);
        fwrite(&highScore, CPAK_HIGHSCORE_SIZE, 1, playerDataFile);

        std::vector<uint8_t> skills(CPAK_SKILLS_BOUND, 0);

        fseek(playerDataFile, CPAK_SKILLS_OFFSET, SEEK_SET);
        fwrite(skills.data(), 1, CPAK_SKILLS_BOUND, playerDataFile);

        fclose(playerDataFile);
    }



       int fullSaveToPak(PlayerData pData, int port) {

        if(portHasCPak(static_cast<joypad_port_t>(port-1))) {

        std::string prefix = SAVEPATH;
        FILE* playerDataFile = fopen(prefix.c_str(), "wb");

        if(!playerDataFile) {
            debugf("Failed to write player %d's data. Aborting.\n", port);
            return -2;
        }

        // DEFAULT VALUES
            debugf("SUCCESSFULLY FOUND player %d's data. Writing.\n", port);
        fwrite("PLAYER", 1,  CPAK_USERNAME_SIZE, playerDataFile);

        fseek(playerDataFile, 0, SEEK_SET);
        fwrite(pData.username, 1,  CPAK_USERNAME_SIZE, playerDataFile);

        int XP = pData.xp;
        fseek(playerDataFile, CPAK_XP_OFFSET, SEEK_SET);
        fwrite(&XP, CPAK_XP_SIZE, 1, playerDataFile);


        int level = pData.level;
        fseek(playerDataFile, CPAK_LEVEL_OFFSET, SEEK_SET);
        fwrite(&level, CPAK_LEVEL_SIZE, 1, playerDataFile);


        int remortLevel = pData.remortLevel;
        fseek(playerDataFile, CPAK_REMORTLEVEL_OFFSET, SEEK_SET);
        fwrite(&remortLevel, CPAK_REMORTLEVEL_SIZE, 1, playerDataFile);


        int pointsaveBank = pData.pointsaveBank;
        fseek(playerDataFile, CPAK_POINTSAVEBANK_OFFSET, SEEK_SET);
        fwrite(&pointsaveBank, CPAK_POINTSAVEBANK_SIZE, 1, playerDataFile);


        int highScore = pData.highScore;
        fseek(playerDataFile, CPAK_HIGHSCORE_OFFSET, SEEK_SET);
        fwrite(&highScore, CPAK_HIGHSCORE_SIZE, 1, playerDataFile);


        std::vector<uint8_t> skills(CPAK_SKILLS_BOUND, 0);
        skills = pData.skills;

        fseek(playerDataFile, CPAK_SKILLS_OFFSET, SEEK_SET);
        fwrite(skills.data(), 1, CPAK_SKILLS_BOUND, playerDataFile);

        fclose(playerDataFile);

            return 1;
            
        }
        debugf("Cannot write save: no CPak found.\n");
            return -1;
    }



    PlayerData readPlayerData(int port) {

        std::string prefix = SAVEPATH;
        FILE* playerDataFile = fopen(prefix.c_str(), "rb");

        if(!playerDataFile) {
            debugf("Failed to FIND player %d's data. Aborting.\n", port);
            return {};
        }
        PlayerData pData = {};

        fseek(playerDataFile, 0, SEEK_END);
        long file_size = ftell(playerDataFile);
        rewind(playerDataFile);

        char *buffer = static_cast<char*>(malloc(file_size));

        if(!buffer) {
            debugf("Failed to READ player %d's data. Aborting.\n", port);
            fclose(playerDataFile);
            return {};
        }


        // fetching Username
        
        //char *buffer = static_cast<char*>(malloc(CPAK_USERNAME_SIZE));
        //char userName[CPAK_USERNAME_SIZE]{};

        fseek(playerDataFile, 0, SEEK_SET);
        fread(pData.username, 1, CPAK_USERNAME_SIZE, playerDataFile);
/*
        for(uint8_t i = 0; i < CPAK_USERNAME_SIZE; i++) {
            userName[i] = buffer[i];
        }
            std::snprintf(
                pData.username,
                CPAK_USERNAME_SIZE,
                "%s",
                userName
            );
        
        buffer = static_cast<char*>(malloc(CPAK_XP_SIZE));
*/

        fseek(playerDataFile, CPAK_XP_OFFSET, SEEK_SET);
        fread(&pData.xp, CPAK_XP_SIZE, 1, playerDataFile);



        fseek(playerDataFile, CPAK_LEVEL_OFFSET, SEEK_SET);
        fread(&pData.level, CPAK_LEVEL_SIZE, 1, playerDataFile);



        fseek(playerDataFile, CPAK_REMORTLEVEL_OFFSET, SEEK_SET);
        fread(&pData.remortLevel, CPAK_REMORTLEVEL_SIZE, 1, playerDataFile);



        fseek(playerDataFile, CPAK_POINTSAVEBANK_OFFSET, SEEK_SET);
        fread(&pData.pointsaveBank, CPAK_POINTSAVEBANK_SIZE, 1, playerDataFile);



        fseek(playerDataFile, CPAK_HIGHSCORE_OFFSET, SEEK_SET);
        fread(&pData.highScore, CPAK_HIGHSCORE_SIZE, 1, playerDataFile);


        std::vector<uint8_t> skills(CPAK_SKILLS_BOUND, 0);

        fseek(playerDataFile, CPAK_SKILLS_OFFSET, SEEK_SET);
        fread(&pData.skills, 1, CPAK_SKILLS_BOUND, playerDataFile);

        fclose(playerDataFile);

        return pData;
    }

    std::string getPlayerUserName(int port) {
        std::string username;
        PlayerData playerData = readPlayerData(port);

        if(*playerData.username != '\0') {
            username.assign(playerData.username, CPAK_USERNAME_SIZE);
            debugf("USERNAME: %s\n", username.c_str());
        } else {
            debugf("Failed to get player %d's username. Aborting.\n", port);
            return nullptr;
        }

        return username;
    }

    uint32_t getRequiredXPToLevel(uint8_t level) {
        return (level * (512 * (1 + level * 0.01)));
    }
}