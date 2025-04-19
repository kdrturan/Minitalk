# MiniTalk

MiniTalk is a simple message-passing application that enables text-based communication between two processes using UNIX signals. This project demonstrates how to implement basic inter-process communication (IPC) in C using low-level signal handling.

## Features

- Sends messages character by character
- Uses UNIX signals (SIGUSR1 and SIGUSR2) for data transmission
- Server-client architecture
- Asynchronous communication
- Works entirely via the terminal

## Project Structure


MiniTalk/
├── inc/                # Header files (.h)
├── libs/               # Utility libraries
├── srcs/               # Source files (.c)
├── Makefile            # Build script
└── .gitmodules         # Git submodules (if any)


## How to Use

### Compile

To build the project, simply run:

bash
make


This will generate two executables: server and client.

### Start the Server

bash
./server


This command starts the server and prints its PID (Process ID). The client will use this PID to send messages.

### Start the Client

bash
./client <PID> "Your message"


- <PID>: The PID shown by the server
- "Your message": The message you want to send

### Example

1. In one terminal:

   bash
   ./server
   
   Output:
   
   Server PID: 12345
   

2. In another terminal:

   bash
   ./client 12345 "Hello MiniTalk!"
   

The server terminal will receive and print the message character by character.

## Technical Details

- SIGUSR1 and SIGUSR2 represent bits 0 and 1 respectively.
- Each character is sent bit-by-bit to the server.
- The server reconstructs characters from bits and prints them to stdout.
- An acknowledgment mechanism ensures proper synchronization after each bit.

## Requirements

- A POSIX-compliant OS (Linux, macOS, WSL, etc.)
- GCC compiler

## Make Targets

| Target       | Description                      |
|--------------|----------------------------------|
| make       | Compiles the entire project      |
| make clean | Removes object files             |
| make fclean| Cleans up all binaries and objs  |
| make re    | Cleans and rebuilds the project  |

## Contributing

Feel free to fork the repository and submit pull requests. Feedback, suggestions, and contributions are always welcome!

## License

This project is open-source. If a license file is not specified, it is assumed to be for educational and personal use only.



```
