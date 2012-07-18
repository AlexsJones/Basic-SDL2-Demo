#ifndef _ENGINE_MAP_H
#define _ENGINE_MAP_H

#include "object.h"

#define MAP_DIR DATA_DIR "worlds/"

//#define MAPSIZE 1024		//change to 2^MAPSIZE?(Like Sauerbraten) MAPSIZE 8 == 256
#define BLOCK_SIZE 32		//individual grid size in pixels (should match grass texture size)
#define CHUNK_SIZE 20		//amount of blocks grouped together for loading/unloading
#define MAP_WIDTH 100
#define MAP_HEIGHT 100

#define TOTAL_CHUNKS ( (MAP_WIDTH/CHUNK_SIZE) * (MAP_WIDTH/CHUNK_SIZE) )

/** The Map will be large, give it its own namespace.
 * 
 * 
 *  The map may be randomly generated with some water, trees, region-types, rocks,
 * 	etc(basic map elements). The Map is planned to be a set size on
 * 	creation. So, no infinite maps. All map specifications will be inside
 * 	a script that users can modify to have a custom server.
 * 
 * 
**/

class Chunk
{
/**	Water level will be needed so the engine knows how to render
 * 	the border around water. For example, a beach is drawn differently
 * 	than a cliff-type pond. It may also be usefull for waterfalls.
 * 	The water block on the map overides this if it is greater.
**/
	public:
		std::vector<Block> tiles;
		int waterlevel;
		
		Chunk()
			:waterlevel(0)
		{
			tiles.reserve(CHUNK_SIZE ^ 2);
		}
};
 
class Map
{
	private:
		SDL_Rect box;
//		ifstream mapData;
//		Coordinate coordinate;
		bool loaded;
		std::vector<Chunk> chunks;
	public:
		Map()
		{	//Map(int width, int height, int blocksize ){ //provide a default blocksize
			chunks.reserve(TOTAL_CHUNKS);
			box.w = MAP_WIDTH * BLOCK_SIZE;
			box.h = MAP_HEIGHT * BLOCK_SIZE;
			box.x = -(box.w / 2);
			box.y = -(box.h / 2);
		}

		inline static void keepInBounds(SDL_Rect& box, SDL_Rect Bounds){
			//CALL Engine::keepInBounds(box, this->box);
			if (box.x < Bounds.x){ box.x = Bounds.x; }
			else if (box.x + box.w > Bounds.x + Bounds.w){ box.x = Bounds.x + Bounds.w - box.w; }
			if (box.y < Bounds.y){ box.y = Bounds.y; }
			else if (box.y + box.h > Bounds.y + Bounds.h){ box.y = Bounds.y + Bounds.h - box.h; }
		}
		
		void generate()
		{	
			Uint8 map_edge = 0xFF;
			Uint8 grass =	0x00;										//regions with different ground textures
			std::ofstream map(MAP_DIR "blank_map.dat");					//the plane is grass unless otherwise specified
			for (int nRow = 1; nRow <= MAP_HEIGHT; nRow++){				//border around map by default
				for (int nColumn = 1; nColumn <= MAP_WIDTH; nColumn++){	//regions"sectors" with different privilages
					if (nRow == 1 || nRow == MAP_HEIGHT || nColumn==1){	//call functions to describe map rules? for easier modding
						map << map_edge;
						if (nColumn == MAP_WIDTH)
							map << "\n";
						else map << " ";
					}
					else if (nColumn == MAP_WIDTH){
						map << map_edge << "\n";
					}
					else map << grass << " ";
				}
			}
			map.close();
		}
		
	/*	Spawn or new thread and/or show a loading screen.	*/
		void load(){
			loaded = true;
		}
		
	/*	This method basically calculates the coordinates the camera intersects,
		and returns an area to render. */
		const SDL_Rect getView( SDL_Rect view )
		{ 
			//align to coordinates
			view.x -= (view.x % BLOCK_SIZE) + BLOCK_SIZE;
			view.y -= (view.y % BLOCK_SIZE) + BLOCK_SIZE;
			//increase w+h by at least one gridsize.
			view.w += (view.w % BLOCK_SIZE) + BLOCK_SIZE;
			view.h += (view.h % BLOCK_SIZE) + BLOCK_SIZE;			
			return view;
		}
		
		const SDL_Rect &getBox(){ return box; }
		
		/*	Is this needed?	*/
		bool isActive(){return loaded;} //return loaded && active
};
#endif
