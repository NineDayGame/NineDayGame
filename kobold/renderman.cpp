#include <boost/lexical_cast.hpp>
// ------------------------
#include <libtcod.hpp>

#include "block.hpp"
#include "character.hpp"
#include "entity.hpp"
#include "map.hpp"
// ------------------------

#include "renderman.hpp"

RenderMan::RenderMan()
  : ssCount_(0) {
	init();
}

void RenderMan::init() {
	renderer_.reset(new GlRenderer());
	
	//-------------------------------------------------------------
	texman_.reset(new TextureMan());
    texman_->load_textures();
    const int texid = texman_->get_texture("resources/terminal.bmp")->get_index();
    fontman_.reset(new FontMan());
    fontman_->load_fonts(*texman_);
    const Font::ShPtr cfont = fontman_->get_font("resources/terminal.bmp");
	
	cwindow_.reset(new GlConsoleWindow());
	cwindow_->set_font(cfont);
	cwindow_->show();
	cwindow_->print(std::string("Welcome to NineDayGame"));
	register_printable(cwindow_);
	renderer_->add_window(cwindow_);
	
	ability_window_.reset(new AbilityWindow());
	ability_window_->set_font(cfont);
	ability_window_->set_position(960-160, 0, 0);
	ability_window_->show();
	ability_window_->set_ability(std::string("Mortal strike"), 1);
	ability_window_->set_ability(std::string("Shield bash"), 2);
	ability_window_->set_ability(std::string("Defend"),10);
	renderer_->add_window(ability_window_);
	
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
	renderer_->add_window(health_window_);
	//-------------------------------------------------------------
}

void RenderMan::draw_frame() {
	/*renderer_->load_map(*(e_->known_map));
	renderer_->load_mobs(e_->seen);
	renderer_->set_player((float)e_->x, (float)e_->y);*/
	renderer_->render();
}

void RenderMan::print_to_renderer(std::string output) {
	cwindow_->print(output);
}

void RenderMan::reload_world() {
	//renderer_->load_map(*(e_->known_map)); // -----
	renderer_->clear_movables();
	const int stoneid = texman_->get_texture("resources/stone3.bmp")->get_index();
	Map::ShPtr map = e_->known_map;
	for (int x = 0; x < map->width; ++x) {
		for (int y = 0; y < map->height; ++y) {
			if (map->display[x+y*map->width].c == '.') {
				Block::ShPtr blk (new Block());
				blk->set_position((float)x, (float)y, 0.0f);
				blk->set_texture(stoneid); ////////////////
				TCODColor c = map->display[x+y*map->width].color;
				blk->set_color(Vector3f((c.r/255.0f), (c.g/255.0f), (c.b/255.0f)));
				renderer_->add_movable(blk);
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
						renderer_->add_movable(blk);
					}
				}
			}
		}
	}
	// ----------------------------------------------
	//renderer_->load_mobs(e_->seen); // ------------
	const int defaultid = texman_->get_texture("resources/default.bmp")->get_index();
	foreach (Entity::WkPtr e, e_->seen) {
		Character::ShPtr chr (new Character());
		Entity::ShPtr m = e.lock();
		if (m) {
			chr->set_position(m->x, m->y, 0.5f);
			TCODColor c = m->color;
			chr->set_texture(defaultid); ///////////////
			chr->set_color(Vector3f((c.r/255.0f), (c.g/255.0f), (c.b/255.0f)));
			renderer_->add_movable(chr);
		}
	}	
	// ---------------------------------------------
	renderer_->set_player((float)e_->x, (float)e_->y);
}

void RenderMan::set_entity(Entity::ShPtr entity) {
	e_ = entity;
	//renderer_->load_map(*(e->known_map));
	e_->look();
	renderer_->set_sight_radius(e_->sight_range);
}

void RenderMan::take_screenshot() {
	std::string filename = std::string("screenshot");
	if (ssCount_ < 10) {
		filename += "00";
	} else if (ssCount_ < 100) {
		filename += "0";
	}
	filename += boost::lexical_cast<std::string>(ssCount_++);
	filename += ".bmp";
	renderer_->take_screenshot(filename);
}

void RenderMan::toggle_fullscreen() {
	renderer_->toggle_fullscreen();
}

void RenderMan::toggle_lighting() {
	renderer_->toggle_lighting();
}

void RenderMan::toggle_wireframes() {
	renderer_->toggle_wireframes();
}
