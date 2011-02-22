#ifndef NDG_BLOCK_H_
#define NDG_BLOCK_H_

#include <boost/shared_ptr.hpp>

#include "util.hpp"
#include "movable.hpp"

class Block : public Movable {
public:
	typedef boost::shared_ptr<Block> ShPtr;

	Block();
	void init();

private:
	DISALLOW_COPY_AND_ASSIGN(Block);
};

#endif
