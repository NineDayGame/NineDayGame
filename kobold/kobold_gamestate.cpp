#include <iostream>

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

#include "KoboldTargetState.hpp"
// ------------------------

void parse_target_callback(Living::ShPtr e, std::string a, int x, int y);

KoboldGameState::KoboldGameState(GameState::ShPtr p, Living::ShPtr e)
	: GameState(p,e)
{
	init();
}

void KoboldGameState::init()
{
	renderer.reset(new RenderMan());
	
	init_resources();
	create_windows();
	
	player_light_.reset(new Light());
    Vector4f::ShPtr amb (new Vector4f(0.08f, 0.08f, 0.08f, 1.0f));
    player_light_->set_ambient(amb);
    Vector4f::ShPtr diff (new Vector4f(1.0f, 0.9f, 0.7f, 1.0f));
    player_light_->set_diffuse(diff);
    player_light_->set_attenuation_constant(0.5f);
    player_light_->set_attenuation_linear(0.01f);
    player_light_->set_attenuation_quadratic(0.01f);
    player_light_->set_radius(6.0f);
    renderer->set_dynamic_light(player_light_);
    
    camera_.reset(new GlCamera());
    renderer->set_camera(camera_);
    
    player->register_fovcb(this);
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
	/*ability_window_->set_ability(std::string("Mortal strike"), 1);
	ability_window_->set_ability(std::string("Shield bash"), 2);
	ability_window_->set_ability(std::string("Defend"),10);*/
	int i = 1;
	foreach(Living::ActionMap::value_type v, player->actions) {
		if (player->GET_ACTION_INFO(v.first, ACTION_MANA) > 0) {
			ability_window_->set_ability(v.first, i++);
		}
	} 
	renderer->add_window(ability_window_);
	
	health_window_.reset(new HealthWindow());
	health_window_->set_font(cfont);
	health_window_->set_position(0, 600-8, 0);
	health_window_->update_health(20, 20);
	health_window_->show();
	renderer->add_window(health_window_);
	
	mana_window_.reset(new ManaWindow());
	mana_window_->set_font(cfont);
	mana_window_->set_position(0, 600-16, 0);
	mana_window_->update_mana(20, 20);
	mana_window_->show();
	renderer->add_window(mana_window_);
}

void KoboldGameState::hotkey(int index)
{
	std::string action = ability_window_->abilities_[index-1];
	if(player->GET_ACTION_INFO(action,ACTION_TARGET) == Living::TARGET_NONE)
	{
		Living::ActionArgs args;
		((*player).*(player->actions[action]))(args);
		return;
	}
	KoboldTargetState::ShPtr t(new KoboldTargetState(this->shared_from_this(), player, camera_, renderer,
	                                                 action, &parse_target_callback, player->x, player->y));
	GameState::state = t;	
}

void KoboldGameState::handle_input()
{
	SDL_Event event_;
	
	Living::ActionArgs args;
	boost::shared_ptr<int> x(new int(player->x));
	boost::shared_ptr<int> y(new int(player->y));
	bool walking = false;
	
	reload_world();

	SDL_WaitEvent( &event_ );
	if( event_.type == SDL_KEYDOWN ) {
		switch( event_.key.keysym.sym )
		{
		// These were used for testing. Probably not needed anymore	
		/*case SDLK_w: camera_->set_coords(camera_->get_coords()->x+1, camera_->get_coords()->y+1); break;
		case SDLK_a: camera_->set_coords(camera_->get_coords()->x-1, camera_->get_coords()->y+1); break;
		case SDLK_s: camera_->set_coords(camera_->get_coords()->x-1, camera_->get_coords()->y-1); break;
		case SDLK_d: camera_->set_coords(camera_->get_coords()->x+1, camera_->get_coords()->y-1); break;*/
		case SDLK_i: {
			//KoboldInventoryMenu::ShPtr c = KoboldInventoryMenu::ShPtr(new KoboldInventoryMenu(this->shared_from_this(),5,400,20,20));
			KoboldInventoryMenu::ShPtr c (new KoboldInventoryMenu(this->shared_from_this(),player,20,400,200,80));
			c->set_font(fontman_->get_font("resources/terminal.bmp"));
			c->set_renderman(renderer);
			GameState::state = c;
			break; }
		case SDLK_1: hotkey(1); break;
		case SDLK_2: hotkey(2); break;
		case SDLK_3: hotkey(3); break;
		case SDLK_4: hotkey(4); break;
		case SDLK_5: hotkey(5); break;
		case SDLK_6: hotkey(6); break;
		case SDLK_7: hotkey(7); break;
		case SDLK_8: hotkey(8); break;
		case SDLK_9: hotkey(9); break;
		case SDLK_0: hotkey(10); break;
		case SDLK_KP1:
		case SDLK_LEFT: walking = true; --(*x); break; 
		case SDLK_KP2: walking = true; --(*x); --(*y); break; 
		case SDLK_KP3:
		case SDLK_DOWN: walking = true; --(*y); break;
		case SDLK_KP4: walking = true; --(*x); ++(*y); break;
		case SDLK_KP5: player->wait(args); break;
		case SDLK_KP6: walking = true; ++(*x); --(*y); break; 
		case SDLK_KP7:
		case SDLK_UP: walking = true; ++(*y); break; 
		case SDLK_KP8: walking = true; ++(*x); ++(*y); break; 
		case SDLK_KP9:
		case SDLK_RIGHT: walking = true; ++(*x); break;
		case SDLK_F1: renderer->toggle_fullscreen(); break;
		case SDLK_F2: renderer->toggle_lighting(); break;
		case SDLK_F3: renderer->toggle_wireframes(); break;
		case SDLK_F12: renderer->take_screenshot(); break;
		case SDLK_SPACE: player->spin_attack(args); break;
		}

		if(walking == true)
		{					
			args.push_back(x);
			args.push_back(y);
			player->walk(args);
		}		
	}
		
	if ( event_.type == SDL_QUIT ) {
		GameState::running = false;
	}

	while(player->blocked)
	{
		foreach(Container::ShPtr c, player->container.lock()->inventory)
		{
			Monster::ShPtr a = DCONVERT(Monster,Container,c);
			if(a && !a->blocked)
			{
				a->ai();
			}
		}
		as.tick();
	}

	char c;
	TCODColor color;
	bool trans;
	bool walk;
	GameState::map->get_data(player->x,player->y,&c,&color,&trans,&walk);
	if(c == '<')
	{
		GameState::generate_map(GameState::map->width,GameState::map->height);
		GameState::map->get(player);
		player->known_map->clear();
		player->host_map = GameState::map;
		int x,y;
		GameState::map->random_free_spot(&x,&y);
		player->move(x,y);
	}
}
void KoboldGameState::draw()
{
	health_window_->update_health(player->health, player->max_health);
	mana_window_->update_mana(player->mana, player->max_mana);
	
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

void KoboldGameState::update_view(int x, int y, bool seen_before, char c, TCODColor color, bool transparent, bool walkable) {
	//std::cout << "Got callback" << std::endl;
	if (!seen_before) {
			const int stoneid = texman_->get_texture("resources/stone3.bmp")->get_index();
			const int stonewall = texman_->get_texture("resources/stonewall.png")->get_index();
			Map::ShPtr map = player->known_map;

			if (c == '.') {
				Block::ShPtr blk (new Block());
				blk->set_position((float)x, (float)y, 0.0f);
				blk->set_texture(stoneid); ////////////////
				blk->set_color(Vector3f((color.r/255.0f), (color.g/255.0f), (color.b/255.0f)));
				renderer->load_terrain(blk);
			} else if ((x > 0) && (y > 0)) { 
				if (c == '#'
						&& (map->display[(x-1)+y*map->width].c == '.'
						|| map->display[x+(y-1)*map->width].c == '.')) {
				
					for (int i = 0; i < 3; ++i) {
						Block::ShPtr blk (new Block());
						blk->set_position((float)x, (float)y, (float)i);
						blk->set_texture(stonewall);
						if (i < 2 && color.r > 128 && color.g < 128) {
							//blk->set_texture(stonewall);
							blk->set_color(Vector3f((color.r/255.0f), (color.g/255.0f), (color.b/255.0f)));
						} else {
							blk->set_color(Vector3f(1.0f, 1.0f, 1.0f));
						}
						renderer->load_terrain(blk);
					}
				}
			}
		}
}

void KoboldGameState::reload_world()
{
	renderer->clear_movables();
	const int defaultid = texman_->get_texture("resources/default.bmp")->get_index();
	foreach (Entity::WkPtr e, player->seen) {
		Character::ShPtr chr (new Character());
		Entity::ShPtr m = e.lock();
		if (m) {
			chr->set_position(m->x, m->y, 0.5f);
			TCODColor c = m->color;
			chr->set_texture(defaultid);
			chr->set_color(Vector3f((c.r/255.0f), (c.g/255.0f), (c.b/255.0f)));
			renderer->add_movable(chr);
		}
	}	

	camera_->set_coords((float)player->x, (float)player->y);
	Vector3f::ShPtr pos (new Vector3f(player->x, player->y, 2.0f));
	player_light_->set_position(pos);
}
