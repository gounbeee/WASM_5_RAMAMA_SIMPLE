
#include <LayerTile.h>



extern "C" {




// LayerTile CLASS CONTAINTS ACTUAL TILE IDs FILLING THE ENTIRE MAP !


LayerTile::LayerTile(	int tileSize, 
						const std::vector<Tileset> &tilesets, 
						int tileNumColumns, 
						int tileNumRows) : 	m_tileSize(tileSize), 
											m_tilesets(tilesets), 
											m_position(0,0), 
											m_velocity(0,0),
											m_numColumns(0),
											m_numRows(0) {

    //m_numColumns = (Instance_GameSDL::Instance()->GetGameWidth() / m_tileSize) + 1 ;                 // TODO :: IS THIS SAFE TO PLUS 1 ?
    //std::cout << "   ^^^  m_numColumns IS       " << m_numColumns << std::endl;

    //m_numRows = (Instance_GameSDL::Instance()->GetGameHeight() / m_tileSize) + 1 ;
    //std::cout << "   ^^^  m_numRows    IS       " << m_numRows << std::endl;

    m_numColumns = tileNumColumns;                 
    //std::cout << "   ^^^  m_numColumns IS       " << m_numColumns << std::endl;

    m_numRows = tileNumRows;
    //std::cout << "   ^^^  m_numRows    IS       " << m_numRows << std::endl;


}


void LayerTile::Update() {
	
    m_position += m_velocity;
	m_velocity = Vector2D{ 0.0f, 0.0f };															// RESET TO ZERO FOR NEXT FRAME
																									// THE 'ORDER' IS IMPORTANT!

}


void LayerTile::SetVelocity( Vector2D vel ) {
    m_velocity += vel;
}



void LayerTile::Render() {
    int x, y, x2, y2 = 0;
    x = m_position.getX() / m_tileSize;                                     // m_position :: POSITION OF MAP (DEFAULT VALUE = 0,0)
                                                                            // m_tileSize = 32
                                                                            // x  = SCALED VALUE BY 32 ( 1 : 32 )
    y = m_position.getY() / m_tileSize;                                     // x2 = MODULATED VALUE BY 32 ( 0 ~ 32 LOOPING VALUE )

    x2 = int(m_position.getX()) % m_tileSize;
    y2 = int(m_position.getY()) % m_tileSize;


    // std::cout << "m_position.getX()  ---     " << m_position.getX() << std::endl;
    // std::cout << "x                  ---     " << x                 << std::endl;
    // std::cout << "x2                 ---     " << x2                << std::endl;


    // FILLING MAP AREA
    for(int i = 0; i < m_numRows; i++) {
        for(int j = 0; j < m_numColumns; j++) {

            int id = m_tileIDs[i+y][j+x];

            if(id == 0) {
                continue;
            }

            Tileset tileset = GetTilesetByID(id);                               // GETTING TILE'S (UNIQUE) ID FROM TILE MAP

            id--;                                                               // -1 BECAUSE EXPORTED VALUE AT FIRST, WAS ONE(1) PLUSED


            Instance_ManagerTexture::Instance()->RenderTile(tileset.name,
                                                    0,                                      // MARGIN
                                                    0,                                      // SPACING
                                                    (j * m_tileSize) - x2,                  // HORIZONTAL STARTING POSITION ON THE SOURCE TEXTURE
                                                    (i * m_tileSize) - y2,                  // VERTICAL   STARTING POSITION ON THE SOURCE TEXTURE
                                                    //(j * m_tileSize)+m_position.getX(),                  // HORIZONTAL STARTING POSITION ON THE SOURCE TEXTURE
                                                    //(i * m_tileSize)+m_position.getY(),                  // VERTICAL   STARTING POSITION ON THE SOURCE TEXTURE
                                                    m_tileSize,                                             // WIDTH OF FOCUSED AREA IN TEXTURE SPACE
                                                    m_tileSize,                                             // HEIGHT OF FOCUSED AREA IN TEXTURE SPACE

                                                                                                            // BECAUSE TILE ID IS 'CONTINUOUS' VALUE,
                                                                                                            // SO,
                                                    (id - (tileset.firstGridID - 1)) / tileset.numColumns,  // COLUMN INDEX (HORIZONTAL POSITION) ON THE TILESET
                                                    (id - (tileset.firstGridID - 1)) % tileset.numColumns,  // ROW INDEX (VERTICAL POSITION) ON THE TILESET
                                                    Instance_GameSDL::Instance()->GetRenderer());

        }
    }

}


Tileset LayerTile::GetTilesetByID( int tileID ) {

    for(int i = 0; i < m_tilesets.size(); i++)
    {
        if( i + 1 <= m_tilesets.size() - 1)
        {
            if(tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID)
            {
                return m_tilesets[i];
            }
        }
        else
        {
            return m_tilesets[i];
        }
    }

    std::cout << "did not find tileset, returning empty tileset\n";
    Tileset t;
    return t;
}



}
