#pragma once


//Though the other examples fomr Utsabs project are singletons... this class is going to require two instances of itself in the game.
//One for player 1 and the other for player 2
#define PLAYER_JUMP_HEIGHT 1000.f
#define PLAYER_DEFAULT_WIDTH  32.0f
#define PLAYER_DEFAULT_HEIGHT  32.0f
#define PLAYER_MOVE_SPEED 200.f //we need to change this because the less the move speed the faster the monkeys become
#define PLAYER_GRAVITY 5000.f 
#define PLAYER_HIT_WAIT	2.f

#define PLAYER_LOWERPLATFORM_Y (PLATFORM_DEFAULT_HEIGHT + texture_height - g_window->init.height / 2)

#define PLAYER_SPRITE_CHANGERATE 8.f

struct KeysPressed {
	unsigned int left, right, up, down, shit;
	KeysPressed(int _left, int _right, int _up, int _down, int _shit) :
		left(_left), right(_right), up(_up), down(_down), shit(_shit) {}
};
enum PlayerState {
	ON_GROUND, ON_VINE, IN_AIR, HIT
};

class PlayerMonkey {
private:
	
	unsigned int spritesheet;

	int player_number;
	float pos_x;
	float pos_y;


	//This is what defines the monkey boundries the collision box verticies
	float UR_x, UR_y,// upper right x,y
		  UL_x, UL_y,// upper left x,y
		  LR_x, LR_y,// lower left x,y
		  LL_x, LL_y;// lower right x,y

	float velocity_y;
	bool isOnGround; // will be set to true if the monkey is on a platform or on the ground

	void updateOnGround();
	void updateOnVine();
	void updateInAir();
	void updateHit();


	//Need to determine what the actual width and height of the sprite.
	//Need to send the Renderer::DrawSprite() function already processed section of the sprite (width/height)
	float texture_width;
	float texture_height;

	//Mutators
	void setVerticies();


	//Mutators - Player Movement
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void jump();
	void updateJump();
	void applyGravity();
	void moveUpVine();
	void moveDownVine();
	bool onVineJump();
	void airJump();
	void CheckIfTouchingGround();

	void ThrowProjectile();

	//onVineJump specific variables
	bool vineUpKeyPressed, vineUpKeyReleased;
	bool grabbingVine;
	float timeStampOfUpKeyPress, timeStampOfUpKeyReleased;

	bool lookingLeft{ false };

	bool isHitKeyPressed{ false };
	float hitTimer{ 0 };

	//Point accumulator variables

	// SPRITES
	float sprite_itr { 0 };
	int sprite_mode { 0 };

	bool performedVineJump, performedPlatformJump;

	

protected:

public:
	bool canAirJump;
	const KeysPressed* controls;
	float Previous_Lower_Y_Collision_Box_Position; //used for determining platform collision entrance
	int player_points;
	PlayerState player_state;
	PlayerState previouse_state;

	//Default Constructor
	PlayerMonkey();

	//Constructor
	PlayerMonkey(int p_num, float x, float y, PlayerState p_state, KeysPressed *controls);

	//Accessors
	const int getPlayerNumber(){return player_number;}
	const float getPosition_X(){return pos_x;}
	const float getPosition_Y(){return pos_y;}
	const unsigned int getSpriteSheetID(){return spritesheet;}
	const PlayerState getPlayerState(){return player_state;}
	const float getMax_X(){ return UR_x;}
	const float getMax_Y(){ return UR_y;}
	const float getMin_X(){ return LL_x;}
	const float getMin_Y(){ return LL_y;}
	const float getTextureWidth(){return texture_width;}
	const float getTextureHeight(){return texture_height;}

	//Mutators
	void setPlayerNumber(int number) {player_number = number;}
	void setSpriteSheetID(unsigned int id) { spritesheet = id; }
	void setPlayerState(PlayerState _state);
	void setPlayer_Y_Velocity(float _velocity_y){velocity_y = _velocity_y;}
	void setPosition_X(float _pos_x) {pos_x = _pos_x;}
	void setPosition_Y(float _pos_y) {pos_y = _pos_y;}
	void setPlayerGrabbingVine(bool state){grabbingVine = state;}

	//Member Functions
	void DrawSprite();
	void UpdatePlayer();
	void init();
	bool isLookingLeft() { return lookingLeft; }

	void ProjectileHit();
};