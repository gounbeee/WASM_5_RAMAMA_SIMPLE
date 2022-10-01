#include <LevelDataLoader.h>



extern "C" {





Level* LevelDataLoader::ParseLevel(const char *levelFile) {

    // create a TinyXML document and load the map XML
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    // create the level object
    Level* pLevel = new Level();

    // get the root node
    TiXmlElement* pRoot = levelDocument.RootElement();

    pRoot->Attribute("tilewidth", &m_tileSize);
    pRoot->Attribute("width", &m_width);
    pRoot->Attribute("height", &m_height);

    // parse the tilesets
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {

        if(e->Value() == std::string("tileset")) {

            parseTilesets(e, pLevel->GetTilesets());												// SETTING UP TILESET
        }
    }

    // parse any object layers
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("layer")) {
            parseTileLayer(e, pLevel->GetLayers(), pLevel->GetTilesets());							// SETTING UP TILE LAYER
        }
    }

    return pLevel;

}



void LevelDataLoader::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets) {

    std::string filaName = pTilesetRoot->FirstChildElement()->Attribute("source");

    // first add the tileset to texture manager
    Instance_ManagerTexture::Instance()->Load(pTilesetRoot->FirstChildElement()->Attribute("source"), pTilesetRoot->Attribute("name"), Instance_GameSDL::Instance()->GetRenderer());

    // create a tileset object
    Tileset tileset;
    pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
    pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
    pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
    pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
    pTilesetRoot->Attribute("spacing", &tileset.spacing);
    pTilesetRoot->Attribute("margin", &tileset.margin);
    tileset.name = pTilesetRoot->Attribute("name");

    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    pTilesets->push_back(tileset);


}



void LevelDataLoader::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets) {
    LayerTile* pTileLayer = new LayerTile(m_tileSize, *pTilesets, m_width, m_height);

    // tile data
    std::vector<std::vector<int>> data;

    std::string decodedIDs;
    TiXmlElement* pDataNode = nullptr;

    for(TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {

        if(e->Value() == std::string("data")) {
            pDataNode = e;
        }
    }


    for(TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling()) {

        TiXmlText* text = e->ToText();
        std::string t = text->Value();
        decodedIDs = base64_decode(t);
    }

    // uncompress zlib compression
    uLongf numGids = m_width * m_height * sizeof(int);
    std::vector<unsigned> gids(numGids);
    uncompress((Bytef*)&gids[0], &numGids,(const Bytef*)decodedIDs.c_str(), decodedIDs.size());

    std::vector<int> layerRow(m_width);

    for(int j = 0; j < m_height; j++) {

        data.push_back(layerRow);

    }

    for(int rows = 0; rows < m_height; rows++) {

        for(int cols = 0; cols < m_width; cols++) {

            data[rows][cols] = gids[rows * m_width + cols];
        }
    }

    pTileLayer->SetTileIDs(data);

    pLayers->push_back(pTileLayer);


    //std::cout << "pTileLayer is ...   " << pTileLayer << std::endl;
    //std::cout << "pLayers is ...      " << pLayers << std::endl;

}





}