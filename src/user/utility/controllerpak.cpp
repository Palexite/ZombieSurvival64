#include "controllerpak.h"
#include "stdlib.h"
#include "libdragon.h"
#define GAMECODE "GMZS"
#define PUBLISHERCODE "13"

namespace controllerpak {



    bool portHasCPak(joypad_port_t port) {
        int accessory_0 = joypad_get_accessory_type(port);
         debugf("Accessory type at port %d: %d\n", port, accessory_0);
    if (accessory_0 == 2) { // No idea why, but this value needs to be incremented by 1. The enum is incorrect.
        return true;
    }
    return false;
    }



    int mountCPak(int port) {

        std::string prefix = "cpak" + std::to_string(port) + ":/";

        joypad_port_t joypadPort = static_cast<joypad_port_t>(port);

        return cpakfs_mount(joypadPort, prefix.c_str());
    }



    const char* readPlayerValueData(int port) {

        std::string prefix = "cpak" + std::to_string(port) + ":/" + GAMECODE + "." + PUBLISHERCODE + "-ZOMBIESURVIVAL.A";
        FILE* playerDataFile = fopen(prefix.c_str(), "rb");

        if(!playerDataFile) {
            debugf("Failed to FIND player %d's value file. Aborting.", port);
        }

        fseek(playerDataFile, 0, SEEK_END);
        long file_size = ftell(playerDataFile);
        rewind(playerDataFile);

        char *buffer = static_cast<char*>(malloc(file_size));

        if(!buffer) {
            debugf("Failed to READ player %d's data. Aborting.", port);
            fclose(playerDataFile);
            return nullptr;
        }

        size_t count = fread(buffer, 1, file_size, playerDataFile);
        fclose(playerDataFile);

        return buffer;
    }
}