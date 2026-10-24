// name : structs_and_fps.c 
// date : 2026-10-24 
// std  : C 23 standard 
// desc : about how to use function pointers in structs to create polymorphism, oop-like behaviour.

//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 

//----------------------------------- typedefs and datas --------------------------------
// define a scruct called Point;
typedef struct {
    int x;
    int y;
    int z;
} Point;

// define a struct called Animal;
typedef struct {
    const char* name;
    Point position;
    void (*speak)(const char *content);
    void (*move)(Point *position, int dx, int dy, int dz);
} Animal;


//-------------------------------------- function declarations ------------------------- 
void dog_speak(const char* content);
void dog_move(Point *position, int dx, int dy, int dz);
void cat_speak(const char* content);
void cat_move(Point *position, int dx, int dy, int dz);

//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("Structs and Function Pointers");
    // define the animal dog;
    Animal dog = { .name = "Bob", {.x = 0, .y = 0, .z = 0}, dog_speak, dog_move};
    Animal cat = { .name = "Tom", {.x = -10, .y = -10, .z = 10}, cat_speak, cat_move};
    // this is the thing; 
    dog.speak("Hey, I am a dog!");
    dog.move(&(dog.position), 10, 10, 10);
    dog.move(&(dog.position), 0, 10, -5);

    cat.speak("Hey, I am a cat!");
    cat.move(&(cat.position), 10, 10, 10);
    cat.move(&(cat.position), 0, 10, -5);


    return EXIT_SUCCESS;
}



//------------------------------------- function definitions -----------------------------

// dog will speak woof;
void dog_speak(const char* content) {
    printf("Woof! %s\n", content);
}

void dog_move(Point *position, int dx, int dy, int dz) {
    int x = position->x;
    int y = position->y;
    int z = position->z;
    position->x += dx;
    position->y += dy;
    position->z += dz;
    printf("The Dog moved from (%d, %d, %d) to (%d, %d, %d).\n", x, y, z, position->x, position->y, position->z);
}

void cat_speak(const char* content) {
    printf("Meow! %s\n", content);
    printf("Meow! Meow! Meow! Purr\n");
}

void cat_move(Point *position, int dx, int dy, int dz) {
    int x = position->x;
    int y = position->y;
    int z = position->z;
    position->x += dx;
    position->y += dy;
    position->z += dz;
    printf("The Cat moved from (%d, %d, %d) to (%d, %d, %d).\n", x, y, z, position->x, position->y, position->z);
    printf("The cat moved very fast lol;\n");
}



