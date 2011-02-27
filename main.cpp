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

	Map::ShPtr m(new Map(width,height));
	m->clear();
	m->randomize(40);

	int x,y;
	m->random_free_spot(&x,&y);
	Living::ShPtr l(new Living(Map::WkPtr(m),"Hero",x,y,'@',TCOD_red,30000));
	l->init_stats(12,8,8,8,100,8,8,1);
	m->get(l);

	TCODRandom* rand = TCODRandom::getInstance();
	for(int i = 0; i < 50; ++i)
	{
		char buf[32];
		char name[32];
		char desc[128];
		int x,y;
		m->random_free_spot(&x,&y);
		sprintf(buf,"Entity %d",i);
		sprintf(name,"health potion");
		sprintf(desc,"a potion that restores up to 10 health");

		TCODColor color(rand->getInt(0,255),rand->getInt(0,255),rand->getInt(0,255));
		Monster::ShPtr e(new Monster(Map::WkPtr(m),buf,x,y,'g',color,3));
		e->init_stats(8,3,5,5,6,3,3,1);
		Item::ShPtr i(new Item(Map::WkPtr(m),name,desc,x,y,'I',TCOD_green));
		e->get(i);
		m->get(e);
	}
	Living::ShPtr e = SCONVERT(Living,Container,m->inventory.front());
	
	if (argc==1) {		
		//RenderMan::ShPtr renderman (new RenderMan());
		//renderman->set_entity(e);
		KoboldGameState::ShPtr kgs(new KoboldGameState(GameState::ShPtr(),e));
		GameState::state = kgs;	
	} else {

		TCODConsole::initRoot(width,height,"Test",false);

		std::list<Container::ShPtr>::iterator i = m->inventory.begin();
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
