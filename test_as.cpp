#include "action_scheduler.hpp"
#include "map.hpp"

void test_as()
{
//	ActionScheduler as;
	Map::ShPtr m(new Map(120,80));
	
	Living::ShPtr l = Living::ShPtr(new Living(Map::WkPtr(m),"Hero6",0,0,'@',TCOD_red,30000));
	l->init_stats(1,1,1,1,1,1,1,1);
	// as.schedule_action(Living::ShPtr(new Living(Map::WkPtr(m),"Hero1",0,0,'@',TCOD_red,30000)),"test",10);
	// as.schedule_action(Living::ShPtr(new Living(Map::WkPtr(m),"Hero2",0,0,'@',TCOD_red,30000)),"test",40);
	// as.schedule_action(Living::ShPtr(new Living(Map::WkPtr(m),"Hero3",0,0,'@',TCOD_red,30000)),"test",4);
	// as.schedule_action(Living::ShPtr(new Living(Map::WkPtr(m),"Hero4",0,0,'@',TCOD_red,30000)),"test",520);
	// as.schedule_action(Living::ShPtr(new Living(Map::WkPtr(m),"Hero5",0,0,'@',TCOD_red,30000)),"test",9999);
	// as.schedule_action(Living::ShPtr(new Living(Map::WkPtr(m),"Hero6",0,0,'@',TCOD_red,30000)),"test",400);

	Living::ActionArgs a;
	a.push_back(boost::shared_ptr<void>(Living::ShPtr(new Living(Map::WkPtr(m),"Hero6",0,0,'@',TCOD_red,30000))));

	l->test(a);

	as.tick();

		l->test(a);

	as.tick();
		l->test(a);

	as.tick();

	for(int i = 0; i < 100; ++i)
		as.tick();
	
	cprintf("Ready: %d Blocked: %d",as.ready.size(),as.blocked.size());
	exit(0);
}
