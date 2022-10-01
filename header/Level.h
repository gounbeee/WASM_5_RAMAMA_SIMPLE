#ifndef INCLUDE_GUARD_LEVEL_H
#define INCLUDE_GUARD_LEVEL_H



#include <iostream>
#include <vector>

#include "Layer.h"
#include "LayerTile.h"
#include "LevelDataLoader.h"

struct Tileset
{
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};


class Level {

private:
    friend class LevelDataLoader;


    std::vector<Tileset> m_tilesets;
    std::vector<Layer*> m_layers;


public:
    Level();
    ~Level();

    void Update();
    void Render();


	Layer* GetLayerByIndex( int index ); 


    std::vector<Tileset>* GetTilesets() { return &m_tilesets; }
	std::vector<Layer*>* GetLayers() { return &m_layers; }



};

#endif
