#ifndef _SFMLPHYSICSFS_
#define _SFMLPHYSICSFS_

#include <PhysFS/physfs.h>
#include <SFML/System.hpp>

namespace sf
{
	// PhysFS - Class responsable for reading streams from compressed files
	// to be used at packing and loading assets from the Game.
    class PhysFS: public sf::InputStream
	{
		// -------- Attributes ---------- 
        private:
			PHYSFS_File* m_File;

		// -----------------------------
		
		// -------- Methods ----------
		public:
			PhysFS(const char* filename = 0x0);
			virtual ~PhysFS();
			
			bool isOpen() const;
			bool open(const char* filename);
			void close();
			
			virtual sf::Int64 read(void* data, sf::Int64 size);
			virtual sf::Int64 seek(sf::Int64 position);
			virtual sf::Int64 tell();
			virtual sf::Int64 getSize();

		// --------------------------
    };
}

#endif
