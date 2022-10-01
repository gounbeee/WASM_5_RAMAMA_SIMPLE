#ifndef INCLUDE_GUARD_LEVELDATALOADER_H
#define INCLUDE_GUARD_LEVELDATALOADER_H

/*
FROM ReadMe.txt FROM ZLIB
...
Important
---------
- To use zlibwapi.dll in your application, you must define the
  macro ZLIB_WINAPI when compiling your application's source files.
...

OR, YOU WILL GET LNK2019 ERROR !!!
*/
//#define ZLIB_WINAPI

#include <iostream>
#include <vector>
#include <string>
#include <zlib.h>

#include "ManagerTexture.h"
#include "ManagerEntity.h"
#include "GameSDL.h"
#include "tinyxml.h"
#include "LayerTile.h"
#include "base64.h"
#include "Level.h"


class Level;
struct Tileset;
class Layer;
class LayerTile;


class LevelDataLoader {

public:
    Level* ParseLevel(const char* levelFile);
	
	int GetTileNumColumns() const { return m_width; }
	int GetTileNumRows() const { return m_height; }
	int GetTileSize() const { return m_tileSize; }

private:

    void parseTilesets( TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
    void parseTileLayer( TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets);

    int m_tileSize;
    int m_width;
    int m_height;

};

#endif
