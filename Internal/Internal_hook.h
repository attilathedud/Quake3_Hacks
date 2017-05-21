// Call responsible for drawing the world
#define drawworld ((unsigned char*)0x0044C8DE)

// Call responsible for drawing entities
#define basicwalls ((unsigned char*)0x0044C8D4)

// Call responsible for drawing the sky
#define sky ((unsigned char*)0x0046D8E1)

// Call responsible for drawing the mist
#define rclear ((unsigned char*)0x0045A6F6)

// Call responsible for drawing bone wireframes
#define wireframe ((unsigned char*)0x00463CB8)

// Call responsible for drawing texture wireframes
#define texwireframe ((unsigned char*)0x00463CC5)

// Shade the wireframes
#define wblue ((unsigned char*)0x00463CCD)
#define wgreen ((unsigned char*)0x00463CD2)
#define wred ((unsigned char*)0x00463CD7)

// Inverse the opcodes of draw world and draw entities call to switch the order they are rendered
unsigned char switchdw[] = {0xE8, 0x3D, 0xE7, 0xFF, 0xFF};
unsigned char switchbw[] = {0xE8, 0x87, 0xA4, 0x01, 0x00};

// nops to fill in instructions
unsigned char nop2[] = {0x90, 0x90};
unsigned char nop5[] = {0x90, 0x90, 0x90, 0x90, 0x90};
unsigned char nop6[] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90};

// Original sky instructions
unsigned char regsky[] = {0x85, 0xC9};

// Our sky rendering state
bool ssky;
