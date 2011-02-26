#ifndef KOBOLD_GAMESTATE_HPP
#define KOBOLD_GAMESTATE_HPP

#include <boost/shared_ptr.hpp>
#include "gamestate.hpp"
#include "living.hpp"
#include "renderman.hpp"
#include "util.hpp"

//----------------------------------------------
#include "textureman.hpp"
#include "fontman.hpp"
#include "glcamera.hpp"
#include "light.hpp"
//----------------------------------------------

class KoboldGameState : public GameState, public FovListener
{
public:
	typedef boost::shared_ptr<KoboldGameState> ShPtr;

	RenderMan::ShPtr renderer;
	Living::ShPtr player;
	
	KoboldGameState(GameState::ShPtr p, Living::ShPtr e);
	virtual ~KoboldGameState() {}

	virtual void handle_input();
	virtual void draw();
	
	void update_view(int x, int y, bool seen_before, char c, TCODColor color, bool transparent, bool walkable);

private:
	void init();
	void init_resources();
	void create_windows();
	void reload_world();
//----------------------------------------------
	GlConsoleWindow::ShPtr cwindow_;
	AbilityWindow::ShPtr ability_window_;
	HealthWindow::ShPtr health_window_;
	MenuWindow::ShPtr menu_window_;

	TextureMan::ShPtr texman_;
	FontMan::ShPtr fontman_;
	
	GlCamera::ShPtr camera_;
	Light::ShPtr player_light_;
//----------------------------------------------
	DISALLOW_COPY_AND_ASSIGN(KoboldGameState);
};

#endif
