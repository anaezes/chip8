//#include
//#include   // OpenGL graphics and input
#include "Chip8.h" // Your cpu core implementation

int main(int argc, char **argv)
{
    //Initialize the Chip8 system
    Chip8 myChip8;

    // Set up render system and register input callbacks
    //setupGraphics();
    //setupInput();

    // Load the game into the memory
    myChip8.loadGame("test");

    // Emulation loop
    for(;;)
    {
        // Emulate one cycle
        try {
            myChip8.emulateCycle();
        }
        catch(std::runtime_error e) {
            std::cout << e.what() <<std::endl;
            return -1;
        }

        // If the draw flag is set, update the screen
        //if(myChip8.drawFlag)
        //drawGraphics();

        // Store key press state (Press and Release)
        //myChip8.setKeys();
    }

    return 0;
}