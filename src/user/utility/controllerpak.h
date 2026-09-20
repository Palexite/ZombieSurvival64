// This file is reserved for code regarding controller paks

/*
=======braintstorming========

-----USERNAMES---

User names will have chars represented in 5 bits, with a maximum of 10 chars

5 * 10 = 50 bits

This means 8 bytes need to be allocated (64 bits in total).

If the player does not have a controllerpak, their username will be Player # (# replaced with port number)





-----Skills---
For every byte that is unused, we can reserve it for skills in the skill tree like an array.

If a player does not have a controllerpak, then they have to use verteran mode (using worth in trade for skills with no tradeoff).

It might be possible to make numerical attributes deterministic (Speed I, Speed II) and combine them together into a few bit allocations.
If Speed I increments speed by 1, and Speed II increments by 2. We can save the total value into 2 bits, which will deterministically tell us whether 
Speed I and or II is selected (speed of 1 means only speed I can be selected). This is better then saving a whole byte for both.


----Pointsave Bank---

8 bytes will be reserved for the pointsave bank
If the player does not have a controllerpak, their bank will always be 512.
*/



