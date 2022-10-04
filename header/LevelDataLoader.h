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

// ------------------------------------------
// **** THIS CLASS LevelDataLoader WORKS ****
//    
//      < RETRIEVING DATA > WITH   ::  tinyxml, zlib, nlohmann/json, base64
//      THEN
//      < CONSTRUCTING >           ::  Tileset STRUCT + LayerTile OBJECT
//      FINALLY, 
//      < CONSTRUCTING >           ::  Level OBJECT 
//      

#include <zlib.h>                   
#include <nlohmann/json.hpp>
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


using nJson = nlohmann::json;

// THIS STRUCT IS REPRESETATION OF JSON FILE
// EXPORTED FROM TILESETTER APPLICATION !
struct TlSttrJsn_Lyr_t {

    int index;
    std::string name;
    nJson::array_t positions;
    int tileCounts;

};

struct TlSttrJsn_t {

    int tile_size;
    int map_width;
    int map_height;
    int layerCount;
    std::string textureFile;
    std::vector<TlSttrJsn_Lyr_t> layers;

};


class LevelDataLoader {

public:
    Level* ParseTLDTmx(const char* levelFile);
	
	int GetTileNumColumns() const { return m_width; }
	int GetTileNumRows() const { return m_height; }
	int GetTileSize() const { return m_tileSize; }
    Level* ParseTLSetterJson(const char *jsonFile);

private:

    void parseTilesetsTmx( TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
    void parseTileLayerTmx( TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets);

    void parseTilesetsJson( TlSttrJsn_t jsonObj, std::vector<Tileset>* pTilesets);
    void parseTileLayerJson( TlSttrJsn_t jsonObj, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets);

    std::string readFileIntoString3(std::string& path);
    std::string getJsonTilesData(nJson::iterator iter, int layerInd);
    SDL_Point getsize(SDL_Texture *texture);

    int m_tileSize;
    int m_width;
    int m_height;


};

#endif
