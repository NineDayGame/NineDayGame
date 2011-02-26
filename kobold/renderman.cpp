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

int RenderMan::add_window(const GlWindow::ShPtr window) {
	renderer_->add_window(window);
}

void RenderMan::clear_movables() {
	renderer_->clear_movables();
}

void RenderMan::clear_windows() {
	renderer_->clear_windows();
}

void RenderMan::remove_window(GlWindow::ShPtr window) {
	renderer_->remove_window(window);
}

void RenderMan::load_terrain(const Movable::ShPtr movable) {
	renderer_->load_terrain(movable);
}

void RenderMan::set_camera(GlCamera::ShPtr camera) {
	renderer_->set_camera(camera);
}

void RenderMan::set_dynamic_light(Light::ShPtr light) {
	renderer_->set_dynamic_light(light);
}

void RenderMan::draw_frame() {
	renderer_->render();
}

void RenderMan::set_entity(Entity::ShPtr entity) {
	entity->look();
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
