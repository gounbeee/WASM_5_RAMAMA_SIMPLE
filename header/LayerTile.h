#ifndef INCLUDE_GUARD_LAYERTILE_H
#define INCLUDE_GUARD_LAYERTILE_H


#include <iostream>
#include <vector>
#include "Layer.h"
#include "Level.h"
#include "Vector2D.h"
#include "ManagerTexture.h"
#include "GameSDL.h"


class Level;
struct Tileset;



class LayerTile : public Layer {

public:

    LayerTile(int tileSize, const std::vector<Tileset>& tilesets, int tileNumColumns, int tileNumRows );

    virtual void Update();
    virtual void Render();

	// FOR ANIMATING
	void SetVelocity( Vector2D vel );


    void SetTileIDs( const std::vector<std::vector<int> >& data ) {
        m_tileIDs = data;
    }

    void SetTileSize( int tileSize ) {
        m_tileSize = tileSize;
    }


    Tileset GetTilesetByID( int tileID );


private:
    int m_numColumns;
    int m_numRows;
    int m_tileSize;

    Vector2D m_position;
    Vector2D m_velocity;

    const std::vector<Tileset> &m_tilesets;
    std::vector<std::vector<int> > m_tileIDs;


};



#endif
