#include <libtcod.hpp>
#include <list>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "block.hpp"
#include "entity.hpp"
#include "living.hpp"
#include "map.hpp"
#include "vector3f.hpp"
#include "camera.hpp"
#include "item.hpp"
#include "menu.hpp"
#include "util.hpp"
#include "renderman.hpp"
#include "monster.hpp"

#include "goblin_gamestate.hpp"
#include "kobold_gamestate.hpp"

void clean_up()
{
    SDL_Quit();
}

int main(int argc, char* argv[])
{
	int width = 120;
	int height = 80;
	GameState::generate_map(width,height);
	Living::ShPtr e = GameState::generate_player();
	
	if (argc==1) {		
		//RenderMan::ShPtr renderman (new RenderMan());
		//renderman->set_entity(e);
		KoboldGameState::ShPtr kgs(new KoboldGameState(GameState::ShPtr(),e));
		GameState::state = kgs;	
	} else {

		TCODConsole::initRoot(width,height,"Test",false);

		std::list<Container::ShPtr>::iterator i = GameState::map->inventory.begin();
		std::list<Entity::ShPtr> follow;
		for(int j = 0; j < 0; ++j)
		{
			follow.push_back(SCONVERT(Entity,Container,*(++i)));
		}
		follow.push_front(e);

		GoblinGameState::ShPtr mgs(new GoblinGameState(GameState::ShPtr(),e));
		GameState::state = mgs;
		
		Camera::ShPtr c;
		int q = 0;
		foreach(Entity::ShPtr e, follow)
		{
			int size = width/follow.size();
			c = EntityCamera::ShPtr(new EntityCamera(e->known_map,e,q*size,20,size,60));
			mgs->cameras.push_back(c);
			++q;
		}

		c = TextCamera::ShPtr(new TextCamera(0,2,width,18));
		mgs->cameras.push_back(c);
		TextCamera::ShPtr tc = SCONVERT(TextCamera,Camera,c);
		register_printable(tc);

		c = TextCamera::ShPtr(new TextCamera(0,0,width,2));
		mgs->cameras.push_back(c);
		mgs->health_indicator = SCONVERT(TextCamera,Camera,c);
	}

	while(GameState::running)
	{
		GameState::state->draw();
//		TCODSystem::saveScreenshot(NULL);
		GameState::state->handle_input();
	}

	clean_up();

	return 0;
}
