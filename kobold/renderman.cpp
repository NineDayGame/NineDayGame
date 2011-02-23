#include <boost/lexical_cast.hpp>

#include "renderman.hpp"

RenderMan::RenderMan()
  : ssCount_(0) {
	init();
}

void RenderMan::init() {
	renderer_.reset(new GlRenderer());
}

void RenderMan::draw_frame() {
	/*renderer_->load_map(*(e_->known_map));
	renderer_->load_mobs(e_->seen);
	renderer_->set_player((float)e_->x, (float)e_->y);*/
	renderer_->render();
}

void RenderMan::reload_world() {
	renderer_->load_map(*(e_->known_map));
	renderer_->load_mobs(e_->seen);
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
