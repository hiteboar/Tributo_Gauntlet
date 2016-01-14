#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL.h"
#include "Game.h"

ModuleRender::ModuleRender(){
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH * SCREEN_SIZE;
	camera.h = SCREEN_HEIGHT * SCREEN_SIZE;
}

bool ModuleRender::Init(){
	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC){
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(game->window->window, -1, flags);

	if (renderer == nullptr) ret = false;
	return ret;
}

bool ModuleRender::PreUpdate(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	return true;
}

bool ModuleRender::Update(){
	
	
	float x = -(game->player->pos.x - SCREEN_WIDTH / 3) * SCREEN_SIZE;
	float y = -(game->player->pos.y - SCREEN_HEIGHT / 2) * SCREEN_SIZE;
	
	if (x > 0.0f) x = 0.0f;
	else if (x < (((SCREEN_WIDTH * 2) / 3) - TILE_MAP_WIDTH * TILE_WIDTH) * SCREEN_SIZE) x = (((SCREEN_WIDTH * 2) / 3) - TILE_MAP_WIDTH * TILE_WIDTH) * SCREEN_SIZE;

	if (y > 0.0f) y = 0.0f;
	else if (y < (SCREEN_HEIGHT - TILE_MAP_HEIGHT * TILE_HEIGHT) * SCREEN_SIZE) y = (SCREEN_HEIGHT - TILE_MAP_HEIGHT * TILE_HEIGHT) * SCREEN_SIZE;
	

	game->renderer->camera.x = x;
	game->renderer->camera.y = y;

	return true;
}

bool ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return true;
}

bool ModuleRender::CleanUp()
{
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed, int screen_w, int screen_h)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	rect.y = (int)(camera.y * speed) + y * SCREEN_SIZE ;

	if (screen_w != NULL && screen_h != NULL){
		rect.w = screen_w;
		rect.h = screen_h;
	}
	else if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0) ret = false;

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)(camera.x + rect.x * SCREEN_SIZE );
		rec.y = (int)(camera.y + rect.y * SCREEN_SIZE );
		rec.w *= SCREEN_SIZE ;
		rec.h *= SCREEN_SIZE ;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0) ret = false;

	return ret;
}
