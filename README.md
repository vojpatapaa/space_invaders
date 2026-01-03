
# Space invaders
Re-creation of classic arcade game from 1978 using C language and SDL2 framework.

## Program's compilation and launch on Ubuntu
1. Firstly you have to download SDL libraries. You can use `sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev` command.

2. Secondly you have to create a repository where the program will compile and run. You can do so by typing `mkdir build` into command-line.

3. Assets folder needs to be in same directory as program. You can either copy the assets directory into build directory by typing `cp -r assets build` or move the assets directory into build directory by `mv assets build` command.

4. Set build directory as work directory by `cd build` command. Use `cmake ..` command to generate makefile file.

5. Use `make` command to compile program. After this step you should see "space_invaders" file in build directory.

6. type `./space_invaders` into command-line to launch the program.

## Code
Each module represents one game object. Most of game objects have 2 function - `update()` function and `render()` function. `update()` function is used to calculate object's position, collision with other game objects and basically whole logic of game. `render()` function is just used to copy textures into buffer.

```c
void updateButton(Button * button)
{
   MouseState * mouse =  getMouseState();
   SDL_Point point;
   SDL_Rect buttonRect;

   point.x = mouse->x;
   point.y = mouse->y;

   buttonRect.x = (int)button->xPos;
   buttonRect.y = (int)button->yPos;
   buttonRect.w = button->width;
   buttonRect.h = button->height;

   button->hovered = 0;

   if(SDL_PointInRect(&point, &buttonRect))
   {

    button->hovered = 1;

    if(mouse->leftClicked)
    {
        button->onClickAction();
    }

   }
}
```

### Delta time
Game relies on delta time. Program uses `SDL_GetPerformanceCounter()` and `SDL_GetPerformaceFrequency()` functions. With these function, program is able to determine how much time passed and delay the whole game so it reaches wanted frames per second and then find out delta time, which is just diffrence between last frame's time length and current frame's time lenght. After saving delta time with `setDeltaTime()` function, it is possible to access delta time with `getDeltaTime()` in any module.

```c
int main(int argc, char ** argv)
{
    srand(time(NULL));
    SDL_Color background = {255, 255, 255, 255};
    initGame("Space invaders", 960, 540, 60, background);

    Uint64 lastTime = SDL_GetPerformanceCounter();
    while (isRunning())
    {
        Uint64 currentTime = SDL_GetPerformanceCounter();
        setDeltaTime((currentTime - lastTime) / (double)SDL_GetPerformanceFrequency());
        lastTime = currentTime;

        handleInput();
        update();
        render();

        Uint64 frameEnd = SDL_GetPerformanceCounter();
        double elapsedMili = (frameEnd - currentTime) / (double)SDL_GetPerformanceFrequency() * 1000.0;
        if (elapsedMili < getDesiredMaxMilPerFrame())
        {
            SDL_Delay(getDesiredMaxMilPerFrame() - elapsedMili);
        }
    }
    clearGame();

    return 0;
}
```
### Controlling the game
Game uses 2 ways to get user's input - `SDL_PollEvent()` function and `SDL_GetKeyboardState()` function. `SDL_PollEvent()` is used for detecting "cross exit" use and mouse use. `SDL_GetKeyboardState()` is then used in tank module to take detect input from keyboard.

```c
const Uint8 * keyboardState = SDL_GetKeyboardState(NULL);
if(keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A])
{
    tank->xPos -= getDeltaTime() * MOVE_SPEED;
}

if(keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D])
{
    tank->xPos += getDeltaTime() * MOVE_SPEED;
}
```

## Game's rules
Enemies slowly float down towards tank (player). player's goal is to avoid enemy's shots and shoot down all enemies before they get down. Player can use bunker which can take several shots before it breaks down. Player gains score points by shooting down individual enemies. Shooting down enemies gives diffrent score based on enemy's tier. Player is also able to shoot down ufo, which is not mandatory but can give additional score points. Game can ends once player loses all lifes. If the player manages to shoot down all enemies and not die, game resets and another round starts (lifes do not reset).

### Saving score
After each play session, game decides if gained score is bigger than stored score. If it is bigger, it rewrites the score.dat file. If file is deleted or it simply isn't created yet, game's high-score will automatically be 0.
