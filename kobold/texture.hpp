#ifndef NDG_TEXTURE_H_
#define NDG_TEXTURE_H_

#include <string>

#include <boost/shared_ptr.hpp>

#include "util.hpp"

class Texture {
public:
	typedef boost::shared_ptr<Texture> ShPtr;

	Texture(std::string name);
	
	// Returns the name of the texture
	const std::string get_name() const;
	
	// Compare the name of this texture with another name. Returns true if they're equal, false otherwise.
	const bool is_name(const std::string& rhs) const;
	
	// Return the index, AKA "OpenGL Name" of the texture. This value is meaningless unless the texture is
	// loaded.
	const int get_index() const;
	
	const int get_gltype() const;
	const int get_bytecount() const;
	
	// Set the index, AKA "OpenGL Name" of the texture - used when loading the texture.
	void set_index(int index);

private:
	std::string name_;
	int texture_index_;
	int gltype_;
	int bytecount_;

	DISALLOW_COPY_AND_ASSIGN(Texture);
};

#endif
