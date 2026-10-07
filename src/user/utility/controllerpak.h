#include "cpakfs.h"
#include "controller.h"
#include "stdio.h"
#include <string>


// This file is reserved for code regarding controller paks


namespace controllerpak {
    extern bool portHasCPak(joypad_port_t port);

    extern int mountCPak(int port);


    /// @brief
    // read the player's value data expressed in binary using a POSIX filesystem.

    /// @param port The port to read from (Make sure it has a controller pak and that it is mounted!)
    /// @return returns set of characters representing bytes. Will return nullptr if anything fails. 
    extern const char* readPlayerValueData(int port);
}

/*
=======braintstorming========

-----USERNAMES---

User names will have chars represented in 1 byte, with a maximum of 16 chars. 

If the player does not have a controllerpak, their username will be Player # (# replaced with port number)





-----Skills---
128 bytes will be reserved for skills in the form of one large byte-wise array.

This means every byte after all the static allocations is now interpreted as a skill.

If a player does not have a controllerpak, then they have to use verteran mode (using worth in trade for skills with no tradeoff).

It might be possible to make numerical attributes deterministic (Speed I, Speed II) and combine them together into a few bit allocations.
If Speed I increments speed by 1, and Speed II increments by 2. We can save the total value into 2 bits, which will deterministically tell us whether 
Speed I and or II is selected (speed of 1 means only speed I can be selected). This is better then saving a whole byte for both.


----Pointsave Bank---

4 bytes will be reserved for the pointsave bank
If the player does not have a controllerpak, their bank will always be 512.




===== Total memory usage out of 256 bytes (ordered) =====

// username
256 - 16

// remort
// 240 - 4

// level
// 236 - 1

// xp
// 235 - 4

// pointsave bank
231 - 4

// high score
 227 - 8
 219

// skills
// 219 - 128

91 leftover bytes




*/







