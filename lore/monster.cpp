#include "monster.hpp"
#include "util.hpp"
#include <cmath>

Monster::Monster(Map::WkPtr host_map, std::string name, int x, int y, int c, TCODColor color, int health) : Living(host_map,name,x,y,c,color,health), AI(known_map) { }
Monster::~Monster(){}

static double distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
	
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
			return;
		}
	}
	double closest_val = 9999;
	int closest_x = 0;
	int closest_y = 0;
	if(path->isEmpty())
	{
		for(int i = 0; i < known_map->height; ++i)
		{
			for(int j = 0; j < known_map->width; ++j)
			{
				if(known_map->display[j+i*known_map->width].c == 0)
				{
					double dist = distance(x,y,j,i);
					if(dist < closest_val)
					{
						closest_x = j;
						closest_y = i;
						closest_val = dist;
					}
				}
			}
		}
		path->compute(x,y,closest_x,closest_y);
	}
	int count = 5;
	while(path->isEmpty() && count-- > 0)
	{
		int dx,dy;
		known_map->random_free_spot(&dx,&dy);
		path->compute(x,y,dx,dy);
	}
	int mx,my;
	path->walk(&mx,&my,1);
	move(mx,my);
}
