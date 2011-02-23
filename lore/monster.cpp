#include "monster.hpp"
#include "util.hpp"

Monster::Monster(Map::WkPtr host_map, std::string name, int x, int y, int c, TCODColor color, int health) : Living(host_map,name,x,y,c,color,health), AI(known_map) { }
Monster::~Monster(){}
	
void Monster::ai()
{
	foreach(Entity::WkPtr e, seen)
	{
		Living::ShPtr l = DCONVERT(Living,Entity,e.lock());
		if(l && l->name == "Hero")
		{
			char c,c2;
			TCODColor color,color2;
			bool trans,trans2;
			bool walk,walk2;
			int ox = x;
			int oy = y;
			int dx = l->x;
			int dy = l->y;
			int mx, my;
			Map::ShPtr m = known_map;
			
			m->get_data(ox,oy,&c,&color,&trans,&walk);
			m->set_data(ox,oy,c,color,true,true);
			
			m->get_data(dx,dy,&c2,&color2,&trans2,&walk2);
			m->set_data(dx,dy,c2,color2,true,true);

			path->compute(ox,oy,dx,dy);
			path->walk(&mx,&my,1);

			m->set_data(dx,dy,c,color,trans,walk);
			m->set_data(dx,dy,c2,color2,trans2,walk2);
			
			move(mx,my);
		}
	}
}
