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


 const int windowWidth{700};
 const int windowHeight{450};
InitWindow(windowWidth,windowHeight,"My Window");

int framesCounter = 60*30;

Texture2D obstacle = LoadTexture("resources/TieFighter.png");
Texture2D xwing = LoadTexture("resources/X-Wing.png");
Texture2D StarWars = LoadTexture("StarWarsTitle.png");



float scrollingBack = 0.0f;

Texture2D midground = LoadTexture("resources/Background.png");




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

//X_Wing Movement Speed
int speed{200};

//Collision varible
bool collision{};

//Music Source
Music music = LoadMusicStream("resources/Star_Wars_Medley.wav"); 

//Sound Source for Bullet/Lazers
Sound sound = LoadSound("resources/Quadlaser_turret_fire.wav");

//Play music
PlayMusicStream(music);

//Collision Death sound
Sound death= LoadSound("resources/R2D2.wav");

//Set FPS
SetTargetFPS(60);  
	while(!WindowShouldClose()){
	
framesCounter--;


scrollingBack -= 0.5f; 
if (scrollingBack <= -midground.width*2) scrollingBack = 0;

//Start music playing
UpdateMusicStream(music); 
	
	const float deltaTime{GetFrameTime()};
	
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

	if(CheckCollisionRecs(xwingRec,TieFighterRec)){
		collision = true;
		
	}
	if(CheckCollisionRecs(xwingRec,TieFighterRec2)){
		collision = true;
		
	}
	if(CheckCollisionRecs(xwingRec,TieFighterRec3)){
		collision = true;
		
	}

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
	if(IsKeyReleased(KEY_D))
	{xwingAnim.frame = 0;
	xwingAnim.rec.x = xwingAnim.frame* xwingAnim.rec.width;}

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
	if(IsKeyReleased(KEY_A))
	{xwingAnim.frame = 0;
	xwingAnim.rec.x = xwingAnim.frame* xwingAnim.rec.width;}

	if(IsKeyDown(KEY_W))
	{
	xwingAnim.pos.y -= speed*deltaTime;
	xwingAnim.rec.width = xwing.width/6;
	player.rec.y += speed*deltaTime;

	xwingAnim.runningTime += deltaTime; 
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
	if(IsKeyReleased(KEY_W))
	{xwingAnim.frame = 0;
	xwingAnim.rec.y = xwingAnim.frame* xwingAnim.rec.width;}

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
                bullet[i].rec.x = player.rec.x;
                bullet[i].rec.y = player.rec.y + player.rec.height / 4;
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




ClearBackground(BLACK);




if (framesCounter <= 0){
framesCounter = 0;
DrawText("You Have Won",150,200,50,BLUE);
	}
else
if (collision){
DrawText("You Died",250,200,50,RED);

}

	else{


PlaySound(death);




//Draw Scrolling Back ground
DrawTextureEx(midground, (Vector2){ scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
DrawTextureEx(midground, (Vector2){ midground.width*2 + scrollingBack, 20 }, 0.0f, 2.0f,WHITE);

DrawTexture(StarWars,350,200,WHITE);


DrawTextureRec(xwing,xwingAnim.rec,xwingAnim.pos,WHITE);

DrawTextureRec(obstacle,TieFighter.rec,TieFighter.pos,WHITE);
DrawTextureRec(obstacle,TieFighter2.rec,TieFighter2.pos,WHITE);
DrawTextureRec(obstacle,TieFighter3.rec,TieFighter3.pos,WHITE);

DrawText("Controls: \n W to Move Up \n S to Move Down \n A to move Left \n D to Move Right \n Press ESC to Close Game.",10,100,5,LIGHTGRAY);
DrawText(TextFormat("Time Left: %i", framesCounter/60), 10, 10, 20, LIME);


TieFighter.pos.y += tieVel* deltaTime;
TieFighter2.pos.y += tieVel2* deltaTime;
TieFighter3.pos.y += tieVel3* deltaTime;

}
EndDrawing();
}
UnloadTexture(xwing);
UnloadTexture(obstacle);
UnloadTexture(midground);
UnloadSound(death);
CloseWindow();
}