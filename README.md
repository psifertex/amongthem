# among them

RE challenge provided for KernelCon by @psifertex with special thanks to @ZetaTwo for help with better design and bugfixes!


## Deploying 

### Easy Mode

For the easy mode, simply give the player the amongthem binary from service/src with no explanation.

### Hard Mode

For hard mode, use the existing docker framework or otherwise run the amongthem binary vi xinetd so it's connected to a remote socket and point players to the port and IP. 

## Solution

### Hard Mode 
For the hard-mode solution, use pwntools or another similar library to exploit the format string vulnerability to first leak the contents of the binary from memory. Then proceed to the next step.

### Easy Mode
Reverse engineering the binary should reveal that the list of tasks is randomized but that a string with the sequence of tasks is run through a CRC32 checksum and when that value matches a hard-coded constant, the string is used with an embedded xxtea algorithm to decrypt the flag and display it.

An example brute-force solver in python doing a random walk of shuffled strings succeeds in less than a minute.  (solve.py)
