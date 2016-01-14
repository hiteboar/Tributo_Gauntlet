#include "ModuleMenu.h"
#include "Game.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

ModuleMenu::ModuleMenu(){}

ModuleMenu::~ModuleMenu(){}

bool ModuleMenu::Init(){
	menu.x = 1;
	menu.y = 1;
	menu.w = 211;
	menu.h = 478;

	coin.x = 217;
	coin.y = 7;
	coin.w = 181;
	coin.h = 27;

	game_over.x = 217;
	game_over.y = 119;
	game_over.w = 181;
	game_over.h = 27;

	success.x = 217;
	success.y = 161;
	success.w = 181;
	success.h = 27;

	one.x = 230;
	one.y = 70;
	one.w = 12;
	one.h = 21;

	two.x = 244;
	two.y = 70;
	two.h = 21;
	two.w = 12;

	three.x = 258;
	three.y = 70;
	three.w = 13;
	three.h = 21;

	four.x = 273;
	four.y = 70;
	four.w = 14;
	four.h = 21;

	five.x = 289;
	five.y = 70;
	five.w = 12;
	five.h = 21;

	six.x = 303;
	six.y = 70;
	six.w = 13;
	six.h = 21;

	seven.x = 318;
	seven.y = 70;
	seven.w = 12;
	seven.h = 21;

	eight.x = 332;
	eight.y = 70;
	eight.w = 13;
	eight.h = 21;

	nine.x = 347;
	nine.y = 70;
	nine.w = 13;
	nine.h = 21;

	zero.x = 362;
	zero.y = 70;
	zero.w = 13;
	zero.h = 21;

	return true;
}

bool ModuleMenu::Start(){
	graphics = game->textures->Load(MENUFILE_PATH);

	coin_fx = game->audio->LoadFx("Audio/coin.wav");
	welcome_fx = game->audio->LoadFx("Audio/welcome.wav");
	die_fx = game->audio->LoadFx("Audio/die.wav");
	success_fx = game->audio->LoadFx("Audio/reminder.wav");

	return true;
}

bool ModuleMenu::Update(){
	game->renderer->Blit(graphics, 1 + SCREEN_WIDTH * 2 / 3, 0, &menu, 0, SCREEN_WIDTH / 3, SCREEN_HEIGHT);

	if (time.getTime() < BLINK) { // INSERT COIN
		float coin_screen_h = coin.h * SCREEN_HEIGHT / menu.h;
		float coin_screen_w = coin.w * (SCREEN_WIDTH / 3) / menu.w;
		game->renderer->Blit(graphics, 8 + SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT / 2, &coin, 0, coin_screen_w, coin_screen_h );
	}

	if (start && game->player->health <= 0){ // GAME_OVER
		GAME_OVER = true;
		game->player->health = 0;
		game->DisableModules();
		start = false;
		game->Restart();
		game->audio->PlayFx(die_fx); 
	}

	// PRINT HEALTH  & SCORE
	DrawInt(game->player->health, SCREEN_WIDTH - 10, 72);
	DrawInt(game->player->score, SCREEN_WIDTH - 50, 72);

	if (game->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN){ // + HEALTH
		game->player->health += 750;
		game->audio->PlayFx(coin_fx);
	}
	if (game->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_DOWN && game->player->health > 0) { // START
		game->EnableModules();
		GAME_OVER = false;
		SUCCESS = false;
		game->player->score = 0;
		start = true; 
		game->audio->PlayFx(welcome_fx);
	}

	
	if (GAME_OVER) DrawGameOver();
	else if (SUCCESS) DrawSuccess();

	if (time.getTime() > BLINK * 2) time.restart();

	return true; 
}

void ModuleMenu::Success(){
	SUCCESS = true;
	game->audio->PlayFx(success_fx);
	game->DisableModules();
	game->Restart();
	start = false;
}


void ModuleMenu::DrawSuccess(){
	if (time.getTime() < BLINK) {
		float coin_screen_h = coin.h * SCREEN_HEIGHT / menu.h;
		float coin_screen_w = coin.w * (SCREEN_WIDTH / 3) / menu.w;
		game->renderer->Blit(graphics, 7 + SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 4 / 5, &success, 0, coin_screen_w, coin_screen_h);
	}
}

void ModuleMenu::DrawGameOver(){
	if (time.getTime() < BLINK) {
		float coin_screen_h = coin.h * SCREEN_HEIGHT / menu.h;
		float coin_screen_w = coin.w * (SCREEN_WIDTH / 3) / menu.w;
		game->renderer->Blit(graphics, 7 + SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 4 / 5, &game_over, 0, coin_screen_w, coin_screen_h);
	}
}

void ModuleMenu::DrawInt(int number, int x, int y){
	if (number < 0) number = 0;
	string num = to_string(number);
	int pos_x = x;
	int pos_y = y;
	for (int i = num.length() - 1; i >= 0; --i){
		SDL_Rect* value = SelectNum(num[i]);

		float num_screen_h = value->h * SCREEN_HEIGHT / menu.h;
		float num_screen_w = value->w * (SCREEN_WIDTH / 3) / menu.w;
		pos_x -= num_screen_w;

		game->renderer->Blit(graphics, pos_x, pos_y, value, 0, num_screen_w, num_screen_h);
	}

}

SDL_Rect* ModuleMenu::SelectNum(char num){
	switch (num){
	case '1':
		return &one;
		break;
	case '2':
		return &two;
		break;
	case '3':
		return &three;
		break;
	case '4':
		return &four;
		break;
	case '5':
		return &five;
		break;
	case '6':
		return &six;
		break;
	case '7':
		return &seven;
		break;
	case '8':
		return &eight;
		break;
	case '9':
		return &nine; 
		break;
	case '0':
		return &zero;
		break;
	default:
		return nullptr;
		break;
	}
}

bool ModuleMenu::CleanUp(){
	game->textures->Unload(graphics);
	return true; 
}

