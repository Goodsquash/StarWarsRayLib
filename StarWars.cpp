#include "raylib.h"

// Animation class
struct Anim
{
	Rectangle rec; 
	Vector2 pos;
	int frame; 
	float updateTime; 
	float runningTime;  
};
// Bullet Class
struct Bullets{
	Rectangle rec;
	Vector2 speed; 
	Color color;
	bool active;
};

//executes code
int main(){

//window size (width and height)
const int windowWidth{700};
const int windowHeight{450};

//window initilized 
InitWindow(windowWidth,windowHeight,"My Window");


//frame counter used for the countdown timer, frames are 60fps so the frame counter is multiplied by 30 to get 30 seconds
int framesCounter = 60*30;

//score varible
int score = 0;

// Textures for Tiefighter, xwing loaded
Texture2D obstacle = LoadTexture("resources/TieFighter.png");
Texture2D xwing = LoadTexture("resources/X-Wing.png");
Texture2D StarWars = LoadTexture("resources/StarWarsTitle.png");
Texture2D BabyYoda = LoadTexture("resources/baby_yoda.png");


// background texture loaded
Texture2D background = LoadTexture("resources/background1.png");
// scrolling background float varible set so 0.0
float scrollingBack = 1000.0f;


//Xwing_animation
Anim xwingAnim;
xwingAnim.rec.width = xwing.width/6; 
xwingAnim.rec.height = xwing.height;
xwingAnim.rec.x = 0;
xwingAnim.rec.y = 0;
xwingAnim.pos.x = windowWidth/2 - xwingAnim.rec.width/2;
xwingAnim.pos.y = windowHeight - xwingAnim.rec.height;
xwingAnim.frame = 0;
xwingAnim.updateTime = 1.0/12.0;
xwingAnim.runningTime = 0.0;

//TieFighter oject using anim 
Anim TieFighter;
TieFighter.rec.width = obstacle.width;
TieFighter.rec.height = obstacle.height;
TieFighter.rec.x=0;
TieFighter.rec.y=0;
TieFighter.pos.x = GetRandomValue(0,700);
TieFighter.pos.y = -1000;


//TieFighter2 object
Anim TieFighter2;
TieFighter2.rec.width = obstacle.width;
TieFighter2.rec.height = obstacle.height;
TieFighter2.rec.x=0;
TieFighter2.rec.y=0;
TieFighter2.pos.x = GetRandomValue(0,700);
TieFighter2.pos.y = -1000;

//TieFighter3 object
Anim TieFighter3;
TieFighter3.rec.width = obstacle.width;
TieFighter3.rec.height = obstacle.height;
TieFighter3.rec.x=0;
TieFighter3.rec.y=0;
TieFighter3.pos.x = GetRandomValue(0,700);
TieFighter3.pos.y = -1000;

// Baby Yoda item
Anim BabyYodaAnim;
BabyYodaAnim.rec.width = BabyYoda.width;
BabyYodaAnim.rec.height = BabyYoda.height;
BabyYodaAnim.rec.x=0;
BabyYodaAnim.rec.y=0;
BabyYodaAnim.pos.x = GetRandomValue(0,700);
BabyYodaAnim.pos.y = -1000;

//Bullet Number
int num_bullets{20};

//Audio Input Init 
InitAudioDevice(); 


//Bullets for Xwing
Bullets bullet[num_bullets];
for (int i = 0; i<num_bullets; i++){
bullet[i].rec.height= 10;
bullet[i].rec.width = 10;
bullet[i].color = RED;
bullet[i].rec.x = xwingAnim.rec.x;
bullet[i].rec.y = xwingAnim.rec.y + xwingAnim.rec.height/4;
bullet[i].speed.x = 50;
bullet[i].speed.y = -10;
bullet[i].active = false;}
int shootRate = 0;

//TieFighter Speed with random values
int tieVel{GetRandomValue(80,300)};
int tieVel2{GetRandomValue(80,300)};
int tieVel3{GetRandomValue(80,300)};
int yoda{GetRandomValue(80,300)};

//X_Wing Movement Speed
int speed{200};

//Collision varible
bool collision{};


//Music Source loaded
Music music = LoadMusicStream("resources/Star_Wars_Medley.wav"); 

//Sound Source for Bullet/Lazers loaded
Sound sound = LoadSound("resources/Quadlaser_turret_fire.wav");

//Sound Source when player death happens
Sound death= LoadSound("resources/R2D2.wav");

//Sound source when baby yoda is picked up
Sound yahoo = LoadSound("resources/yahoo!.wav");

//Sound source when tie figter is hit by bullet
Sound TieDie = LoadSound("resources/TIE_fighter_explode.wav");

//Starts music playing
PlayMusicStream(music);


//Set Frames per second (FPS) to 60 
SetTargetFPS(60);  
//When window is not closed game is playing
	while(!WindowShouldClose()){
	
//frame counter is decreased by 1 each frame	
framesCounter--;

//scrolling back set background screen
scrollingBack -= 0.5f; 
if (scrollingBack <= -background.height*2) scrollingBack = 0;

//Updates buffers for music streaming
UpdateMusicStream(music); 

	//Get time in seconds for last frame drawn (delta time)
	const float deltaTime{GetFrameTime()};
	
	//All Texture Rectangles drawn
	Rectangle xwingRec{
	xwingAnim.pos.x,
	xwingAnim.pos.y,
	xwingAnim.rec.height,
	xwingAnim.rec.width	
	};
	Rectangle TieFighterRec{
	TieFighter.pos.x,
	TieFighter.pos.y,
	TieFighter.rec.width,
	TieFighter.rec.height
	};
	Rectangle TieFighterRec2{
	TieFighter2.pos.x,
	TieFighter2.pos.y,
	TieFighter2.rec.width,
	TieFighter2.rec.height
	};
	Rectangle TieFighterRec3{
	TieFighter3.pos.x,
	TieFighter3.pos.y,
	TieFighter3.rec.width,
	TieFighter3.rec.height
	};
	Rectangle BabyYodaRec{
	BabyYodaAnim.pos.x,
	BabyYodaAnim.pos.y,
	BabyYodaAnim.rec.width,
	BabyYodaAnim.rec.height
	};
	for (int i = 0; i<num_bullets; i++){
	Rectangle BulletsRec{
	bullet[i].rec.x, 
	bullet[i].rec.y,
	bullet[i].rec.width,
	bullet[i].rec.height
	};

//TieFighter reset at random positions when they reach the bottom screen.
	if (TieFighter.pos.y > 450) 
	{
		TieFighter.pos.x = GetRandomValue(0,200);
		TieFighter.pos.y = 0;
	} 
	if (TieFighter2.pos.y > 450) 
	{
		TieFighter2.pos.x = GetRandomValue(210,350);
		TieFighter2.pos.y = 0;
	} 
	if (TieFighter3.pos.y > 450) 
	{
		TieFighter3.pos.x = GetRandomValue(360,450);
		TieFighter3.pos.y = 0;
	}

// Baby Yoda reset code
	if (BabyYodaAnim.pos.y > 450) 
	{
		BabyYodaAnim.pos.x = GetRandomValue(360,450);
		BabyYodaAnim.pos.y = 0;
	}  
// Bullet rec reset code, used so it doesn't hit off screen tiefighters after they reset
	if (bullet[i].rec.y <=0) 
	{
		bullet[i].rec.x = -10000;
		bullet[i].rec.y = -10000;
	}  
//When the xwing collides with Tie Fighters the collision is switch to true and also plays death sound.
	if(CheckCollisionRecs(xwingRec,TieFighterRec)){
		collision = true;
		PlaySound(death);
	}
	if(CheckCollisionRecs(xwingRec,TieFighterRec2)){
		collision = true;
		PlaySound(death);
	}
	if(CheckCollisionRecs(xwingRec,TieFighterRec3)){
		collision = true;
		PlaySound(death);
	}

// if statement for when xwing hits baby yoda his rec is reset, score is added and sound is played
	if(CheckCollisionRecs(xwingRec,BabyYodaRec)){
	
		BabyYodaAnim.pos.x = GetRandomValue(50,600);
		BabyYodaAnim.pos.y = -300;
		score++;
		PlaySound(yahoo);
	}

// if statement for when bullets hit Tie Fighter, Tie Fighter position is reset, score is added and sound plays.
	if(CheckCollisionRecs(BulletsRec,TieFighterRec)){
	
		TieFighter.pos.x = GetRandomValue(100,450);
		TieFighter.pos.y = -100;
		score = score + 1;
		PlaySound(TieDie);
	}
	if(CheckCollisionRecs(BulletsRec,TieFighterRec2)){

		TieFighter2.pos.x = GetRandomValue(100,450);
		TieFighter2.pos.y = -100;
		score = score +1;
		PlaySound(TieDie);
	
	}
	if(CheckCollisionRecs(BulletsRec,TieFighterRec3)){
		TieFighter3.pos.x = GetRandomValue(100,450);
		TieFighter3.pos.y = -100;
		score = score +1;
		PlaySound(TieDie);
	}
}

	

//Xwing moves through animation when the D key is pressed and also moves across the screen
	if(IsKeyDown(KEY_D))
{
	xwingAnim.pos.x += speed*deltaTime;
	xwingAnim.rec.width = xwing.width/6;


	xwingAnim.runningTime += deltaTime; 
	if(xwingAnim.runningTime >= xwingAnim.updateTime)
	{
	xwingAnim.runningTime = 0.0;
	xwingAnim.rec.x = xwingAnim.frame* xwingAnim.rec.width;
	xwingAnim.frame++;
	if (xwingAnim.frame>5){
	xwingAnim.frame = 0;
	}

	}

}
	//Animations stops when key is released
	if(IsKeyReleased(KEY_D))
	{xwingAnim.frame = 0;
	xwingAnim.rec.x = xwingAnim.frame* xwingAnim.rec.width;}

//Xwing moves through animation when the A key is pressed and also moves across the screen
	if(IsKeyDown(KEY_A))
	{
	xwingAnim.pos.x -= speed*deltaTime;
	xwingAnim.rec.width = -xwing.width/6;


	xwingAnim.runningTime += deltaTime; 
	if(xwingAnim.runningTime >= xwingAnim.updateTime)
	{
	xwingAnim.runningTime = 0.0;
	xwingAnim.rec.x = xwingAnim.frame* xwingAnim.rec.width;
	xwingAnim.frame++;
	if (xwingAnim.frame>5){
	xwingAnim.frame = 0;
	}

	}
	}
	//Animations stops when key is released
	if(IsKeyReleased(KEY_A))
	{xwingAnim.frame = 0;
	xwingAnim.rec.x = xwingAnim.frame* xwingAnim.rec.width;}

	//Xwing moves up the screen up the screen when W key is pressed
	if(IsKeyDown(KEY_W))
	{
	xwingAnim.pos.y -= speed*deltaTime;
	xwingAnim.rec.width = xwing.width/6;


	xwingAnim.runningTime += deltaTime; 
	if(xwingAnim.runningTime >= xwingAnim.updateTime)
	{
	xwingAnim.runningTime = 0.0;
	xwingAnim.rec.x = xwingAnim.frame* xwingAnim.rec.width;
	xwingAnim.frame++;
	if (xwingAnim.frame>5){
	xwingAnim.frame = 0;
	}

	}
	}
	
	if(IsKeyReleased(KEY_W))
	{xwingAnim.frame = 0;
	xwingAnim.rec.y = xwingAnim.frame* xwingAnim.rec.width;}

//Xwing down up the screen up the screen when S key
	if(IsKeyDown(KEY_S))
	{
	xwingAnim.pos.y += speed*deltaTime;
	xwingAnim.rec.width = xwing.width/6;


	xwingAnim.runningTime -= deltaTime; 
	if(xwingAnim.runningTime >= xwingAnim.updateTime)
	{
	xwingAnim.runningTime = 0.0;
	xwingAnim.rec.y = xwingAnim.frame* xwingAnim.rec.width;
	xwingAnim.frame++;
	if (xwingAnim.frame>5){
	xwingAnim.frame = 0;
	}

	}
	}
	if(IsKeyReleased(KEY_S))
	{xwingAnim.frame = 0;
	xwingAnim.rec.y = xwingAnim.frame* xwingAnim.rec.width;}


//Sets bullets rec if active
for (int i = 0; i < num_bullets; i++)
    {
        if (bullet[i].active)
            DrawRectangleRec(bullet[i].rec, bullet[i].color);
    }
	
//bullets are fire when space is held down
    if (IsKeyDown(KEY_SPACE))
    {
        shootRate += 5;
        for (int i = 0; i <num_bullets; i++)
        {
            if (!bullet[i].active && shootRate % 60 == 0)
            {
				PlaySound(sound);
                bullet[i].rec.x = xwingAnim.pos.x+60;
                bullet[i].rec.y = xwingAnim.pos.y+40;
                bullet[i].active = true;
				break;
            }
        }
    }


    for (int i = 0; i < num_bullets; i++)
    {
        if (bullet[i].active)
        {
           
            bullet[i].rec.y += bullet[i].speed.y;
			

            if (bullet[i].rec.y <= 0) 
            {
                bullet[i].active = false;
                shootRate = 0;
            }

        }
    }

BeginDrawing();


//Black background so stars can be seen
ClearBackground(BLACK);

//if the framecounter, time limit equals zero win screen pops up and runs through text over time and then closes

if (framesCounter <= 0){DrawText(TextFormat("Final Score: %i", score), 250, 250, 20, GREEN);  
	num_bullets = 0;
	
DrawText("You Have Won",150,200,50,BLUE);

if (framesCounter <= -200){
	DrawText("You Have Won",150,200,50,PURPLE);
	
	}
if (framesCounter <= -400 ){
	DrawText("You Have Won",150,200,50,GREEN);
	}
if (framesCounter <= -600 ){
	DrawText("You Have Won",150,200,50,GOLD);
	}

	if (framesCounter == -800 ){
		break;
	}
	}
else

//if there is a collision draws fail screen and runs through different text along with insult text, if the frame counter equals 1 the screen closes
if (collision){num_bullets = 0;

if (framesCounter >= 1201){
	DrawText("You Are Dead",150,200,50,GOLD);
	DrawText("\n  You should have chosen \n     the Dark Side loser", 150,windowHeight/2,25,DARKGREEN);
	}

if (framesCounter >= 601 && framesCounter <= 1200){
	DrawText("You Are Dead",150,200,50,RED);
	DrawText("\n   We've shoved Baby Yoda\n  down the trash compactor\n                :'(", 150,windowHeight/2,25,PURPLE);
	}
if (framesCounter >= 301 && framesCounter <= 600 ){
	DrawText("You Are Dead ",150,200,50,DARKPURPLE );
	DrawText("\n   Stormtroopers called \n  they want their aim back", 150,windowHeight/2,25,DARKGRAY);
	}
if (framesCounter  >= 1 && framesCounter <= 300 ){
	DrawText("You Are Dead ",150,200,50,LIGHTGRAY);
	DrawText("\n       Jar Jar Binks is now running a\n grass roots campaign against Palpatine.\n               It's not going well", 80,windowHeight/2,25,DARKBLUE);
	}


	if (framesCounter == 1 ){
		
		break;
	}
}

	else{



//Draw Scrolling Back ground
DrawTextureEx(background, (Vector2){ 0, -scrollingBack }, 0.0f, 2.0f, WHITE);
DrawTextureEx(background, (Vector2){ 0, background.height*2 + -scrollingBack}, 0.0f, 2.0f,WHITE);


//draws Star Wars Tile for a second at the start of the game
if (framesCounter >= 60*29 && framesCounter <= 60*30 ){
DrawTexture(StarWars,100,100,WHITE);}


//Draws Xwing texture
DrawTextureRec(xwing,xwingAnim.rec,xwingAnim.pos,WHITE);

//Draws Tie Fighter 1,2,3 Texture
DrawTextureRec(obstacle,TieFighter.rec,TieFighter.pos,WHITE);
DrawTextureRec(obstacle,TieFighter2.rec,TieFighter2.pos,WHITE);
DrawTextureRec(obstacle,TieFighter3.rec,TieFighter3.pos,WHITE);

//Draws Baby Yoda Texture
DrawTextureRec(BabyYoda,BabyYodaAnim.rec,BabyYodaAnim.pos,WHITE);

// Draws Controls Text to left of the screen
DrawText("\n Controls: \n W to Move Up \n S to Move Down \n A to Move Left \n D to Move Right \n Press Space to Fire Laser \n Press ESC to Close Game.",10,100,5,LIGHTGRAY);

//Draws timer at top left
DrawText(TextFormat("Time Left: %i", framesCounter/60), 10, 10, 20, LIME);

//Draws Score at top right 
DrawText(TextFormat("Score: %i", score), 550, 10, 20, BLUE);


//Objects failing speed 
TieFighter.pos.y += tieVel* deltaTime;
TieFighter2.pos.y += tieVel2* deltaTime;
TieFighter3.pos.y += tieVel3* deltaTime;
BabyYodaAnim.pos.y += yoda*deltaTime;

}
//Ends drawing
EndDrawing();
}
//Unloads Textures and sounds
UnloadTexture(xwing);
UnloadTexture(obstacle);
UnloadTexture(background);
UnloadTexture(BabyYoda);
UnloadTexture(StarWars);
UnloadSound(death);
UnloadSound(sound);
UnloadSound(yahoo);
UnloadSound(TieDie);
UnloadMusicStream(music);

//Window Closes
CloseWindow();
}