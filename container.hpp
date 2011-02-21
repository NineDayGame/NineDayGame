#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <libtcod.hpp>
#include <list>

class Container : public boost::enable_shared_from_this<Container>
{
public:
	typedef boost::shared_ptr<Container> ShPtr;
	typedef boost::weak_ptr<Container> WkPtr;

	Container::WkPtr container;
	std::list<Container::ShPtr> inventory;

	virtual void get(Container::ShPtr e);
	virtual void remove(Container::ShPtr e);

protected:
	Container::ShPtr shared();
};

#endif
