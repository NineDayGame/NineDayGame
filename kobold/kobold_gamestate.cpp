#include "kobold_gamestate.hpp"
#include "util.hpp"
#include "monster.hpp"
#include "action_scheduler.hpp"

// ------------------------
#include <libtcod.hpp>

#include "block.hpp"
#include "character.hpp"
#include "entity.hpp"
#include "map.hpp"
// ------------------------

KoboldGameState::KoboldGameState(GameState::ShPtr p, Living::ShPtr e)
  : GameState(p), player(e)
{
	init();
}

void KoboldGameState::init()
{
	renderer.reset(new RenderMan());
	renderer->set_entity(player);
	
	init_resources();
	create_windows();
}

void KoboldGameState::init_resources()
{
	texman_.reset(new TextureMan());
    texman_->load_textures();
    fontman_.reset(new FontMan());
    fontman_->load_fonts(*texman_);
}

void KoboldGameState::create_windows()
{
	const int texid = texman_->get_texture("resources/terminal.bmp")->get_index();
	const Font::ShPtr cfont = fontman_->get_font("resources/terminal.bmp");
	
	cwindow_.reset(new GlConsoleWindow());
	cwindow_->set_font(cfont);
	cwindow_->show();
	cwindow_->print(std::string("Welcome to NineDayGame"));
	register_printable(cwindow_);
	renderer->add_window(cwindow_);
	
	ability_window_.reset(new AbilityWindow());
	ability_window_->set_font(cfont);
	ability_window_->set_position(960-160, 0, 0);
	ability_window_->show();
	ability_window_->set_ability(std::string("Mortal strike"), 1);
	ability_window_->set_ability(std::string("Shield bash"), 2);
	ability_window_->set_ability(std::string("Defend"),10);
	renderer->add_window(ability_window_);
	
	/*menu_window_.reset(new MenuWindow());
	menu_window_->set_dl_index(dl_index_);
	menu_window_->set_texture(texture[2]);
	menu_window_->set_position(400, 200, 0);
	menu_window_->set_scale(200, 200, 0);
	//menu_window_->show();
	menu_window_->push_item(std::string("Menu item 1"));
	menu_window_->push_item(std::string("Menu item 2"));
	menu_window_->push_item(std::string("Menu item 3"));*/
	
	health_window_.reset(new HealthWindow());
	health_window_->set_font(cfont);
	health_window_->set_position(0, 600-8, 0);
	health_window_->update_health(20, 20);
	health_window_->show();
	renderer->add_window(health_window_);
}

void KoboldGameState::handle_input()
{
	SDL_Event event_;
	reload_world();
	SDL_WaitEvent( &event_ );
	if( event_.type == SDL_KEYDOWN ) {
		switch( event_.key.keysym.sym )
		{
		case SDLK_KP1:
		case SDLK_LEFT: player->move(player->x-1, player->y); break;
		case SDLK_KP2: player->move(player->x-1, player->y-1); break;
		case SDLK_KP3:
		case SDLK_DOWN: player->move(player->x, player->y-1); break;
		case SDLK_KP4: player->move(player->x-1, player->y+1); break;
		case SDLK_KP6: player->move(player->x+1, player->y-1); break;
		case SDLK_KP7:
		case SDLK_UP: player->move(player->x, player->y+1); break;
		case SDLK_KP8: player->move(player->x+1, player->y+1); break;
		case SDLK_KP9:
		case SDLK_RIGHT: player->move(player->x+1, player->y); break;
		case SDLK_F1: renderer->toggle_fullscreen(); break;
		case SDLK_F2: renderer->toggle_lighting(); break;
		case SDLK_F3: renderer->toggle_wireframes(); break;
		case SDLK_F12: renderer->take_screenshot(); break;
		}

		foreach(Container::ShPtr c, player->container.lock()->inventory)
		{
			Monster::ShPtr a = DCONVERT(Monster,Container,c);
			if(a && !a->blocked)
			{
				a->ai();
			}
		}
	}
		
	if ( event_.type == SDL_QUIT ) {
		GameState::running = false;
	}

	while(player->blocked)
	{
		as.tick();
	}
}
void KoboldGameState::draw()
{
	foreach(Container::ShPtr c, player->container.lock()->inventory)
	{
		Entity::ShPtr e = DCONVERT(Entity,Container,c);
		if(e)
		{
			e->look();
		}
	}
	renderer->draw_frame();
}

void KoboldGameState::reload_world()
{
	//renderer_->load_map(*(e_->known_map)); // -----
	renderer->clear_movables();
	const int stoneid = texman_->get_texture("resources/stone3.bmp")->get_index();
	Map::ShPtr map = player->known_map;
	for (int x = 0; x < map->width; ++x) {
		for (int y = 0; y < map->height; ++y) {
			if (map->display[x+y*map->width].c == '.') {
				Block::ShPtr blk (new Block());
				blk->set_position((float)x, (float)y, 0.0f);
				blk->set_texture(stoneid); ////////////////
				TCODColor c = map->display[x+y*map->width].color;
				blk->set_color(Vector3f((c.r/255.0f), (c.g/255.0f), (c.b/255.0f)));
				renderer->add_movable(blk);
			} else if ((x > 0) && (y > 0)) { 
				if (map->display[x+y*map->width].c == '#'
			            && (map->display[(x-1)+y*map->width].c == '.'
			            || map->display[x+(y-1)*map->width].c == '.')) {
				
					for (int i = 0; i < 3; ++i) {
						Block::ShPtr blk (new Block());
						blk->set_position((float)x, (float)y, (float)i);
						if (i < 2) {
							TCODColor c = map->display[x+y*map->width].color;
							//blk->set_texture(texture[0]);
							blk->set_color(Vector3f((c.r/255.0f), (c.g/255.0f), (c.b/255.0f)));
						}
						renderer->add_movable(blk);
					}
				}
			}
		}
	}
	// ----------------------------------------------
	//renderer_->load_mobs(e_->seen); // ------------
	const int defaultid = texman_->get_texture("resources/default.bmp")->get_index();
	foreach (Entity::WkPtr e, player->seen) {
		Character::ShPtr chr (new Character());
		Entity::ShPtr m = e.lock();
		if (m) {
			chr->set_position(m->x, m->y, 0.5f);
			TCODColor c = m->color;
			chr->set_texture(defaultid); ///////////////
			chr->set_color(Vector3f((c.r/255.0f), (c.g/255.0f), (c.b/255.0f)));
			renderer->add_movable(chr);
		}
	}	
	// ---------------------------------------------
	renderer->set_player((float)player->x, (float)player->y);
}
