#ifndef _ENGINE_MAP_H
#define _ENGINE_MAP_H

#include "object.h"
#include <fstream>
#include <string>

#define MAP_DIR DATA_DIR "worlds/"

class Block { public: int size; };

class Chunk {
public:
	std::vector<Block> tiles;
	Chunk() {}
};


class Map : Object {
private:
	int blockSize = 32;
	int chunkSize = 32;
	int chunksWide = 4;
	int chunksHigh = 4;
	SDL_Rect box;
	bool loaded;
	std::vector<Chunk> chunks;
	
public:
	Map() {
		//Map(int width, int height, int blocksize ){ //provide a default blocksize
		chunks.reserve(chunksWide * chunksHigh * chunkSize * blockSize);
		box.w = chunksWide * chunkSize * blockSize;
		box.h = chunksHigh * chunkSize * blockSize;
		box.x = -(box.w / 2);
		box.y = -(box.h / 2);
	}
	
	void update(const double& dt) {}
	
	static void keepInBounds(SDL_Rect& box, SDL_Rect Bounds) {
		if (box.x < Bounds.x){ box.x = Bounds.x; }
		else if (box.x + box.w > Bounds.x + Bounds.w){ box.x = Bounds.x + Bounds.w - box.w; }
		if (box.y < Bounds.y){ box.y = Bounds.y; }
		else if (box.y + box.h > Bounds.y + Bounds.h){ box.y = Bounds.y + Bounds.h - box.h; }
	}
	
	void generate() {	
		std::string map_edge = "255";
		std::string grass = "0";
		std::ofstream map( MAP_DIR "blank_map.dat", std::ios::out | std::ios::trunc );
		map << std::string("This is a Map:") << std::endl;
		int rows = chunksHigh * chunkSize;
		int cols = chunksWide * chunkSize;
		for (int nRow = 1; nRow <= rows; nRow++){
			for (int nColumn = 1; nColumn <= cols; nColumn++){
				if (nRow == 1 || nRow == rows || nColumn==1){
					map << map_edge;
					if (nColumn == cols) { map << "\n"; }
					else { map << "\t"; }
				} else if (nColumn == cols) { map << map_edge << "\n"; }
				else { map << grass << "\t"; }
			}
		}
		map.close();
	}
	
	void load() {
		loaded = true;
		//Load Map from File
		//Instantiate Tiles, Blocks, and Objects
	}
	
	// Calculates where the Engine should start tiling the background texture
	const SDL_Rect getView( SDL_Rect view ) {
		//align to coordinates
		view.x -= (view.x % blockSize) + blockSize;
		view.y -= (view.y % blockSize) + blockSize;
		//increase w+h by at least one gridsize.
		view.w += (view.w % blockSize) + blockSize;
		view.h += (view.h % blockSize) + blockSize;			
		return view;
	}
	
	const SDL_Rect &getBox() { return box; }
	
	bool isActive() { return loaded; }
};


#endif

