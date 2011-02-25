#include <boost/lexical_cast.hpp>

#include "renderman.hpp"

RenderMan::RenderMan()
  : ssCount_(0) {
	init();
}

void RenderMan::init() {
	renderer_.reset(new GlRenderer());
}

void RenderMan::add_movable(const Movable::ShPtr movable) {
	renderer_->add_movable(movable);
}

void RenderMan::add_window(const GlWindow::ShPtr window) {
	renderer_->add_window(window);
}

void RenderMan::clear_movables() {
	renderer_->clear_movables();
}

void RenderMan::clear_windows() {
	renderer_->clear_movables();
}

void RenderMan::set_player(float x, float y) {
	renderer_->set_player(x, y);
}

void RenderMan::draw_frame() {
	renderer_->render();
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
