#include "container.hpp"

void Container::get(Container::ShPtr e)
{
	inventory.push_back(e);
	e->container = this->shared();
}

void Container::remove(Container::ShPtr e)
{
	inventory.remove(e);
}

Container::ShPtr Container::shared()
{
	return boost::enable_shared_from_this<Container>::shared_from_this();
}
