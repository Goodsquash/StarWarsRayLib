#include "raylib.h"

struct Anim
{
	Rectangle rec; 
	Vector2 pos;
	int frame; 
	float updateTime; 
	float runningTime;  
};
struct Bullets{
	Rectangle rec;
	Vector2 speed; 
	Color color;
	bool active;
};
struct Player {
    Rectangle rec;
    Vector2 speed;
    Color color;
};


int main(){

//window size (width and height)
const int windowWidth{700};
const int windowHeight{450};

//window initilized 
InitWindow(windowWidth,windowHeight,"My Window");


//frame counter used for the countdown timer, frames are 60fps so the frame counter is multiplied by 30 to get 30 seconds
int framesCounter = 60*30;

int score = 0;

// Textures for Tiefighter, xwing loaded
Texture2D obstacle = LoadTexture("resources/TieFighter.png");
Texture2D xwing = LoadTexture("resources/X-Wing.png");
Texture2D StarWars = LoadTexture("resources/StarWarsTitle.png");
Texture2D BabyYoda = LoadTexture("resources/baby_yoda.png");


// background texture loaded
Texture2D background = LoadTexture("resources/Background.png");
// scrolling background float varible set so 0.0
float scrollingBack = 0.0f;







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

//TieFighter animation
Anim TieFighter;
TieFighter.rec.width = obstacle.width;
TieFighter.rec.height = obstacle.height;
TieFighter.rec.x=0;
TieFighter.rec.y=0;
TieFighter.pos.x = GetRandomValue(0,700);
TieFighter.pos.y = -1000;


//TieFighter2 animation
Anim TieFighter2;
TieFighter2.rec.width = obstacle.width;
TieFighter2.rec.height = obstacle.height;
TieFighter2.rec.x=0;
TieFighter2.rec.y=0;
TieFighter2.pos.x = GetRandomValue(0,700);
TieFighter2.pos.y = -1000;

//TieFighter3 animation
Anim TieFighter3;
TieFighter3.rec.width = obstacle.width;
TieFighter3.rec.height = obstacle.height;
TieFighter3.rec.x=0;
TieFighter3.rec.y=0;
TieFighter3.pos.x = GetRandomValue(0,700);
TieFighter3.pos.y = -1000;


Anim BabyYodaAnim;
BabyYodaAnim.rec.width = BabyYoda.width;
BabyYodaAnim.rec.height = BabyYoda.height;
BabyYodaAnim.rec.x=0;
BabyYodaAnim.rec.y=0;
BabyYodaAnim.pos.x = GetRandomValue(0,700);
BabyYodaAnim.pos.y = -1000;

//Bullet Number
int num_bullets{50};

//Audio Input Init 
InitAudioDevice(); 


//Player_Class
Player player;
player.rec.height= 50;
player.rec.width = 50;
player.color = RED;
player.rec.x = windowWidth/2;
player.rec.y = windowHeight-player.rec.height;
player.speed.x = 10;
player.speed.y = 0;



//Bullets for Xwing
Bullets bullet[num_bullets];
for (int i = 0; i<num_bullets; i++){
bullet[i].rec.height= 10;
bullet[i].rec.width = 10;
bullet[i].color = RED;
bullet[i].rec.x = player.rec.x;
bullet[i].rec.y = player.rec.y + player.rec.height/4;
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

bool pickup{};

//Music Source loaded
Music music = LoadMusicStream("resources/Star_Wars_Medley.wav"); 

//Sound Source for Bullet/Lazers loaded
Sound sound = LoadSound("resources/Quadlaser_turret_fire.wav");

//Starts music playing
PlayMusicStream(music);

//Collision Death sound loaded
Sound death= LoadSound("resources/R2D2.wav");

//Set Frames per second (FPS) to 60 
SetTargetFPS(60);  
//When window is not closed game is playing
	while(!WindowShouldClose()){
	
//frame counter is decreased by 1 each frame	
framesCounter--;

//scrolling back set background screen
scrollingBack -= 0.5f; 
if (scrollingBack <= -background.width*2) scrollingBack = 0;

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
	if (BabyYodaAnim.pos.y > 450) 
	{
		BabyYodaAnim.pos.x = GetRandomValue(360,450);
		BabyYodaAnim.pos.y = 0;
	}  

	if(CheckCollisionRecs(xwingRec,TieFighterRec)){
		collision = true;
		
	}
	if(CheckCollisionRecs(xwingRec,TieFighterRec2)){
		collision = true;
		
	}
	if(CheckCollisionRecs(xwingRec,TieFighterRec3)){
		collision = true;
		
	}

	if(CheckCollisionRecs(xwingRec,BabyYodaRec)){
		pickup = true;
		score++;
		BabyYodaAnim.pos.x = GetRandomValue(360,450);
		BabyYodaAnim.pos.y = -100;
	}


//Xwing moves through animation when the D key is pressed and also moves across the screen
	if(IsKeyDown(KEY_D))
{
	xwingAnim.pos.x += speed*deltaTime;
	xwingAnim.rec.width = xwing.width/6;
	player.rec.x += speed*deltaTime;

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
	player.rec.x -= speed*deltaTime;

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
	player.rec.y += speed*deltaTime;

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
	player.rec.y -= speed*deltaTime;

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





BeginDrawing();


for (int i = 0; i < num_bullets; i++)
    {
        if (bullet[i].active)
            DrawRectangleRec(bullet[i].rec, bullet[i].color);
    }
	
		

    if (IsKeyDown(KEY_SPACE))
    {
        shootRate += 5;
        for (int i = 0; i <num_bullets; i++)
        {
            if (!bullet[i].active && shootRate % 40 == 0)
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

//if there is a collision draws fail screen and runs through different text along with insult text
if (collision){num_bullets = 0;

if (framesCounter >= 1201){
	DrawText("You Are Dead",150,200,50,GOLD);
	DrawText("\n  You should have choosen \n     the Dark Side loser", 150,windowHeight/2,25,DARKGREEN);
	}

if (framesCounter >= 601 && framesCounter <= 1200){
	DrawText("You Are Dead",150,200,50,RED);
	DrawText("\n   We've shoved Baby Yoda\n  down the trash compactor\n                :'(", 150,windowHeight/2,25,PURPLE);
	}
if (framesCounter >= 301 && framesCounter <= 600 ){
	DrawText("You Are Dead ",150,200,50,DARKPURPLE );
	DrawText("\n   Can't believe you called \nTuskens Raiders 'Sand People'. \n        That's gross", 150,windowHeight/2,25,DARKGRAY);
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



PlaySound(death);

if (framesCounter >= 60*29 && framesCounter <= 60*30 ){
DrawTexture(StarWars,100,100,WHITE);}

//Draw Scrolling Back ground
DrawTextureEx(background, (Vector2){ scrollingBack, 0 }, 0.0f, 2.0f, WHITE);
DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 10 }, 0.0f, 2.0f,WHITE);




DrawTextureRec(xwing,xwingAnim.rec,xwingAnim.pos,WHITE);

DrawTextureRec(obstacle,TieFighter.rec,TieFighter.pos,WHITE);
DrawTextureRec(obstacle,TieFighter2.rec,TieFighter2.pos,WHITE);
DrawTextureRec(obstacle,TieFighter3.rec,TieFighter3.pos,WHITE);
DrawTextureRec(BabyYoda,BabyYodaAnim.rec,BabyYodaAnim.pos,WHITE);
DrawText("Controls: \n W to Move Up \n S to Move Down \n A to Move Left \n D to Move Right \n Press ESC to Close Game.",10,100,5,LIGHTGRAY);
DrawText(TextFormat("Time Left: %i", framesCounter/60), 10, 10, 20, LIME);
DrawText(TextFormat("Score: %i", score), 600, 10, 20, BLUE);

TieFighter.pos.y += tieVel* deltaTime;
TieFighter2.pos.y += tieVel2* deltaTime;
TieFighter3.pos.y += tieVel3* deltaTime;
BabyYodaAnim.pos.y += yoda*deltaTime;

}
EndDrawing();
}
UnloadTexture(xwing);
UnloadTexture(obstacle);
UnloadTexture(background);
UnloadSound(death);
UnloadSound(sound);
UnloadMusicStream(music);
CloseWindow();
}