#include "action_scheduler.hpp"
#include "map.hpp"

void test_as()
{
//	ActionScheduler as;
	Map::ShPtr m(new Map(120,80));
	
	Living::ShPtr l(new Living(Map::WkPtr(m),"Hero1",0,0,'@',TCOD_red,30000));
	l->init_stats(1,1,1,1,4,1,1,1);

	Living::ShPtr l2(new Living(Map::WkPtr(m),"Hero2",0,0,'@',TCOD_red,30000));
	l2->init_stats(1,1,1,1,4,1,1,4);

	Living::ShPtr l3(new Living(Map::WkPtr(m),"Hero3",0,0,'@',TCOD_red,30000));
	l3->init_stats(1,1,1,1,4,1,1,2);

	Living::ShPtr l4(new Living(Map::WkPtr(m),"Hero5",0,0,'@',TCOD_red,30000));
	l4->init_stats(1,1,1,1,4,1,1,1.5);
	// as.schedule_action(Living::ShPtr(new Living(Map::WkPtr(m),"Hero1",0,0,'@',TCOD_red,30000)),"test",10);
	// as.schedule_action(Living::ShPtr(new Living(Map::WkPtr(m),"Hero2",0,0,'@',TCOD_red,30000)),"test",40);
	// as.schedule_action(Living::ShPtr(new Living(Map::WkPtr(m),"Hero3",0,0,'@',TCOD_red,30000)),"test",4);
	// as.schedule_action(Living::ShPtr(new Living(Map::WkPtr(m),"Hero4",0,0,'@',TCOD_red,30000)),"test",520);
	// as.schedule_action(Living::ShPtr(new Living(Map::WkPtr(m),"Hero5",0,0,'@',TCOD_red,30000)),"test",9999);
	// as.schedule_action(Living::ShPtr(new Living(Map::WkPtr(m),"Hero6",0,0,'@',TCOD_red,30000)),"test",400);

	Living::ActionArgs a;
	a.push_back(l2);

	Living::ActionArgs a2;
	a2.push_back(l);

	Living::ActionArgs a3;
	a3.push_back(l4);

	Living::ActionArgs a4;
	a4.push_back(l3);
	//a.push_back(boost::shared_ptr<void>(Living::ShPtr(new Living(Map::WkPtr(m),"Hero6",0,0,'@',TCOD_red,30000))));

	for(int i = 0; i < 100; ++i)
	{
		if(!l->blocked)
		l->attack(a);
		if(!l2->blocked)
		l2->attack(a2);
		if(!l3->blocked)
		l3->attack(a3);
		if(!l4->blocked)
		l4->attack(a4);
		as.tick();
//		cprintf("Ready: %d Blocked: %d",as.ready.size(),as.blocked.size());
	}
		
	
	exit(0);
}
