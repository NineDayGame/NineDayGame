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
	
	//player->register_fovcb(&KoboldGameState::update_view);
	
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

	Living::ActionArgs args;
	boost::shared_ptr<int> x(new int(player->x));
	boost::shared_ptr<int> y(new int(player->y));
	bool walking = false;
	
	reload_world();

	SDL_WaitEvent( &event_ );
	if( event_.type == SDL_KEYDOWN ) {
		switch( event_.key.keysym.sym )
		{
		case SDLK_w: camera_->set_coords(camera_->get_coords()->x+1, camera_->get_coords()->y+1); break;
		case SDLK_a: camera_->set_coords(camera_->get_coords()->x-1, camera_->get_coords()->y+1); break;
		case SDLK_s: camera_->set_coords(camera_->get_coords()->x-1, camera_->get_coords()->y-1); break;
		case SDLK_d: camera_->set_coords(camera_->get_coords()->x+1, camera_->get_coords()->y-1); break;
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
}
void KoboldGameState::draw()
{
	health_window_->update_health(player->health, player->max_health);
	
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
						if (i < 2) {
							//blk->set_texture(texture[0]);
							blk->set_color(Vector3f((color.r/255.0f), (color.g/255.0f), (color.b/255.0f)));
						}
						renderer->load_terrain(blk);
					}
				}
			}
		}
}

void KoboldGameState::reload_world()
{
	//renderer_->load_map(*(e_->known_map)); // -----
	/*renderer->clear_movables();
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
	}*/
	// ----------------------------------------------
	//renderer_->load_mobs(e_->seen); // ------------
	renderer->clear_movables();
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

	camera_->set_coords((float)player->x, (float)player->y);
	Vector3f::ShPtr pos (new Vector3f(player->x, player->y, 2.0f));
	player_light_->set_position(pos);
}

/*class MyFovListener : public FovListener
{
public:
	void update_view(int x, int y, bool seen_before, char c, TCODColor color, bool transparent, bool walkable) {
		
		if (!seen_before) {
			const int stoneid = texman_->get_texture("resources/stone3.bmp")->get_index();
			Map::ShPtr map = player->known_map;

			if (c == '.') {
				Block::ShPtr blk (new Block());
				blk->set_position((float)x, (float)y, 0.0f);
				blk->set_texture(stoneid); ////////////////
				blk->set_color(Vector3f((color.r/255.0f), (color.g/255.0f), (color.b/255.0f)));
				renderer->add_movable(blk);
			} else if ((x > 0) && (y > 0)) { 
				if (c == '#'
						&& (map->display[(x-1)+y*map->width].c == '.'
						|| map->display[x+(y-1)*map->width].c == '.')) {
				
					for (int i = 0; i < 3; ++i) {
						Block::ShPtr blk (new Block());
						blk->set_position((float)x, (float)y, (float)i);
						if (i < 2) {
							//blk->set_texture(texture[0]);
							blk->set_color(Vector3f((color.r/255.0f), (color.g/255.0f), (color.b/255.0f)));
						}
						renderer->add_movable(blk);
					}
				}
			}
		}
	}
};*/
