#ifndef NDG_CHARACTER_H_
#define NDG_CHARACTER_H_

#include <boost/shared_ptr.hpp>

#include "basetypes.hpp"
#include "movable.hpp"

class Character : public Movable {
public:
	typedef boost::shared_ptr<Character> ShPtr;

	Character();
	void init();
	//void draw();

private:
	DISALLOW_COPY_AND_ASSIGN(Character);
};

#endif
