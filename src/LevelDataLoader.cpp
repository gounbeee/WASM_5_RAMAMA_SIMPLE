#include <LevelDataLoader.h>


#include <iostream>
//#include <streambuf>
//#include <fstream>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sstream>
//#include <algorithm>
//#include <functional>


extern "C" {


// --------------
// < TILE ID ?? >
// PNG TEXTURE WILL BE SEPERATED WITH TILE IMAGES
// O O O O O O O O
// O O O O O O O O
//
// AND, TILE ID WILL BE, INCREMETAL INDEX FROM UPPER-LEFT
//
// 0 1 2 3 4 5 6 7
// 8 9 10 ........ 

// --------------------------------------
// < TILESETTER > 
// EXPORTS JSON LIKE BELOWS
// ****  x, y, TILE ID ->  "0" BASED !!!!

// { "x":15, "y":8, "id":0 },
// { "x":15, "y":9, "id":0 },
// { "x":15, "y":10, "id":0 },
// { "x":15, "y":11, "id":0 },
// { "x":15, "y":12, "id":0 },
// { "x":15, "y":13, "id":0 },
// { "x":15, "y":14, "id":0 },
// { "x":15, "y":15, "id":0 },
// { "x":15, "y":16, "id":4 },
// { "x":15, "y":17, "id":5 },
// { "x":15, "y":18, "id":16 },
// { "x":15, "y":19, "id":17 },
// { "x":15, "y":20, "id":17 },
// { "x":15, "y":21, "id":18 },
// { "x":15, "y":22, "id":5 },


// ---------------------------------------
// < TILED > 
// EXPORTS JSON LIKE BELOWS
// ****  x, y, TILE ID ->  "1" BASED !!!!

// 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
// 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
// 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
// 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
// 3,3,3,3,3,3,3,3,3,3,3,10,10,10,10,10,10,10,10,10,10,3,3,3,3,3,3,3,3,3,3,3,
// 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
// 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
// 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,







std::string LevelDataLoader::getJsonTilesData(nJson::iterator iter, int layerInd) {

    std::cout << "ALL SINGLE TILE INFO" << std::endl;
    //std::cout << iter.value()[layerInd]["positions"] << std::endl;

    // NUMBER OF TILES
    int tilesIndSize = iter.value()[layerInd]["positions"].size();
    std::cout << "**** TILE COUNTS IN THIS LAYER ****" << tilesIndSize << std::endl;



    // *****************************************
    // ORIGINAL OUTPUTTED INDEX OF SINGLE LAYER 
    // FROM TILESETTER IS VERTICAL ORDER !!!!

    // ----------------- SO --------------------
    // WE NEED TO REBUILD TO X-ORDERED VECTOR !
    // BECAUSE JSON EXPORTED FROM TILESETTER ALIGNED IN VERTICAL ORDER !
    // y TILE INDEX IS LOOPING 0 ~ 31 , 0 ~ 31 , 0 ~ 31 ...     (( 32 TIMES !!!! ))
    // x            IS         0        1        2      ...
    // AND
    // WE CAM USE   i          0,1,2... 32,33,34...     ...           1024  
    //
    // i % 32                  0,1,2... 0,1,2...
    // x * 32                  
    //
    // WANTED INDEX 
    // 0, 32, 64 ...  UNTIL  32 TIMES   ...  THEN  1, 33, 65 ...   UNTIL 32 TIMES !! ...   \
    //                                                                                      |
    //                                                                                      |
    // < CONVERTING INTEGER TO STRING >                                                     |
    // https://www.simplilearn.com/tutorials/cpp-tutorial/int-to-string-cpp                 |

    // STREAM IS FOR MANIPULATING STRING
    std::stringstream tlIndexStream;
    // FOR STORING TEXTS FROM STREAM
    std::string tlIndexStr;

    //                                   ---------------------------------------------------|
    //                                  /
    // for(int j = 0; j < 32; j++) {   
    //     for(int i = 0; i < 32; i++) {   


    // 
    for(int j = 0; j < 32; j++) {   
        for(int i = 0; i < 32; i++) {


            int tlIndex = iter.value()[layerInd]["positions"][i * 32 + j]["id"];
            
            // THIS IS FOR 1 BASED-INDEX !!!!
            // BEACUSE TILED APP IS USING THIS
            tlIndex += 1;

            //std::cout << tlIndex << std::endl;

            // insert operation
            tlIndexStream << tlIndex << ",";

        }
        // INSERT NEWLINE (BECAUSE WE WANT TO MATCH WITH EXPORTED DATA FROM TILED APP ! )
        //tlIndexStream << "\r";
        //tlIndexStream.insert('\n');

    }

    // INPUT STREAM TO STRING
    tlIndexStream >> tlIndexStr;

    // ------------------------------------------
    // DELETE LAST ONE LETTER ','
    // < DELETE LETTERS FROM STRING USING INDEX >
    // https://www.delftstack.com/howto/cpp/remove-last-character-from-a-string-in-cpp/
    tlIndexStr.erase(tlIndexStr.size() - 1, 1);


    // ------------------------------------------
    // PRINTING OUT FOR DEBUG
    std::cout << tlIndexStr << std::endl;

    return tlIndexStr;

}




// < LOADING JSON FILE TROM TILESETTER AND PARSE >
// JSON FILE IS FROM 'TILESETTER' EDITOR
Level* LevelDataLoader::ParseTLSetterJson(const char *jsonFile) {

    // < USING JSON LIBRARY >
    // https://qiita.com/yohm/items/0f389ba5c5de4e2df9cf


    // < READING FILE >
    // https://www.udacity.com/blog/2021/05/how-to-read-from-a-file-in-cpp.html
    // std::ifstream mapJsonFile; 
    // mapJsonFile.open("resources/map01_lv.json");


    // if(mapJsonFile.is_open() ) {
    //  char myChar;
    //  while ( mapJsonFile ) {
    //      myChar = mapJsonFile.get();
    //      std::cout << myChar;
    //  }
    // }


    // https://programming-place.net/ppp/contents/cpp/language/006.html
    std::string mapJsonStr;

    std::string fileName(jsonFile);
    //std::string fileName("resources/map01_json.json");
    mapJsonStr = readFileIntoString3(fileName);
    //std::cout << mapJsonStr << std::endl;


    // INPUT JSON FROM ABOVE
    nJson mapJsonObj;
    mapJsonObj = nJson::parse(mapJsonStr);


    // std::string s = mapJsonObj.dump();
    // std::cout << s << std::endl;


    // RETREIVING DATA FROM JSON FILE

    // INITIALIZING DATA STRUCTURE FOR JSON FILE
    //
    //
    //
    // #include <stdio.h>
    // typedef struct { int k; int l; int a[2]; } T;
    //
    // typedef struct { int i;  T t; } S;
    //
    // T x = {.l = 43, .k = 42, .a[1] = 19, .a[0] = 18 };
    //
    // // x initialized to {42, 43, {18, 19} }
    //
    // int main(void) {
    //
    //     S l = { 1,          // initializes l.i to 1
    //            .t = x,      // initializes l.t to {42, 43, {18, 19} }
    //            .t.l = 41,   // changes l.t to {42, 41, {18, 19} }
    //            .t.a[1] = 17 // changes l.t to {42, 41, {18, 17} }
    //           };
    //
    //     printf("l.t.k is %d\n", l.t.k); // .t = x sets l.t.k to 42 explicitly
    //                                     // .t.l = 41 would zero out l.t.k implicitly
    // }
    //
    // Output:
    //
    // l.t.k is 42


    std::string f = jsonFile;
    TlSttrJsn_t tlSttrJsn = {
        .tile_size=0,
        .map_width=0,
        .map_height=0,
        .layerCount=0,
        .textureFile=f      
    };



    // < RETRIEVING VALUE FROM JSON >
    //
    // FOR JSON FILE EXPORTED FROM TILESETTER APP 
    // IS STRUCTURED LIKE BELOW !!!!
    // 
    // {
    //     "tile_size": 16,                         1 ->> TILE SIZE         (PIXELS) 
    //     "map_width": 32,                         2 ->> MAP WIDTH  COUNT 
    //     "map_height": 32,                        3 ->> MAP HEIGHT COUNT  (IS CONSTRUCTED WITH 32 TILES)
    //     "layers": [                              4 ->> LAYERS 
    //         {                                                // -> LAYER 0  (layerIndex ABOVE !!)
    //             "name": "LAND",                              //    LAYER NAME
    //             "positions": [
    //                     { "x":0, "y":0, "id":0 },            // TILE 1 INFO (POSITION INDEX AND PICTURE ID)
    //                     { "x":0, "y":1, "id":0 },
    //                     ...
    //                 ]
    //         },
    //         {                                                // -> LAYER 1
    //             ...
    //         }
    //         ...
    //     ]
    // }


    for (nJson::iterator it = mapJsonObj.begin(); it != mapJsonObj.end(); ++it) {
        
        
            


        // SEARCHING FOR LAYERS ARRAY
        // THIS CONTAINS LAYERS IN TILESETTER APPLICATION
        //
        // SO, THERE MAY BE MULTIPLE LAYERS IN SOME CASES !
        // 

        // GETTING tile_size VALUE FROM JSON
        if( it.key() == "tile_size" ) tlSttrJsn.tile_size = it.value();
        // GETTING map_width VALUE FROM JSON
        if( it.key() == "map_width" ) tlSttrJsn.map_width = it.value();
        // GETTING map_height VALUE FROM JSON
        if( it.key() == "map_height" ) tlSttrJsn.map_height = it.value();
        // GETTING layers VALUE FROM JSON
        if( it.key() == "layers" ) {

            // STORE LAYER COUNT TO STRUCT
            std::cout << it.key() << " : " << it.value() << "\n";
            std::cout << "**** THERE ARE < " << it.value().size() << " > LAYERS !!!!" << std::endl;
            tlSttrJsn.layerCount = it.value().size();


            // IN THE LAYER ARRAY...
            // FIRST INITIALIZATION OF LAYERS
            for(int z=0; z < tlSttrJsn.layerCount ; z++) {
                // IN ONE LAYER BY LAYER...

                // CREATE NEW STRUCT FOR LAYER
                TlSttrJsn_Lyr_t newTlsLy = {
                    .index=z,                                           // STORING LAYER'S INDEX NUMER
                    .name=it.value()[z]["name"],                        // STORING LAYER'S NAME
                    .positions=it.value()[z]["positions"],              // STORING LAYER'S TILE DATA,
                    .tileCounts=static_cast<int>(it.value()[z]["positions"].size())
                };

                // ADDING LAYER STRUCT TO GLOBAL OBJECT
                tlSttrJsn.layers.push_back(newTlsLy);
            }
            
            // ---------
            // *********
            // FOR DEBUG
            // *********
            for(int q=0; q < tlSttrJsn.layerCount ; q++) {
                std::cout << tlSttrJsn.layers[q].name << std::endl;
                std::cout << tlSttrJsn.layers[q].positions << std::endl;
            }

        } // IF

    } // FOR


    // STORING TILESET INFORMATION TO MEMBER VARIABLES
    m_width = tlSttrJsn.map_width;
    m_height = tlSttrJsn.map_height;
    m_tileSize = tlSttrJsn.tile_size;


    // create the level object
    Level* pLevel = new Level();

    // **** HERE WE ARE PASSING LEVEL OBJECT'S POINTER TO FUNCTION
    //      THEN, WE GET THE DATA WE WANT                          ****

    // PARSING TILESET
    parseTilesetsJson( tlSttrJsn,  pLevel->GetTilesets() );

    // PARSING TILED-LAYER OBJECT
    parseTileLayerJson( tlSttrJsn, pLevel->GetLayers(), pLevel->GetTilesets() ); 


    return pLevel;

}


SDL_Point LevelDataLoader::getsize(SDL_Texture *texture) {
    SDL_Point size;
    SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
    return size;
}


void LevelDataLoader::parseTilesetsJson( TlSttrJsn_t jsonObj, std::vector<Tileset>* pTilesets ) {

    std::cout << jsonObj.textureFile << "    IS FULL PATH OF TEXTURE ID !" << std::endl;

    std::string flNmOnly = jsonObj.textureFile.erase(0, 10).erase(jsonObj.textureFile.size() - 5, 5);
    std::cout << flNmOnly << "    IS TEXTURE ID !" << std::endl;

    std::string imgPath = "resources/" + flNmOnly + ".png";

    // first add the tileset to texture manager
    Instance_ManagerTexture::Instance()->Load(
        imgPath,                                                        // FULL FILE NAME NEEDED
        flNmOnly,                                                       // DELETING '.json' FILENAME ONLY -> ID
        Instance_GameSDL::Instance()->GetRenderer());

    
    // GETTING IMAGE SIZE (TILESET WIDTH AND HEIGHT)
    std::map<std::string, SDL_Texture* > txtmap = Instance_ManagerTexture::Instance()->GetTextureMaps();

    // GETTING SDL_Texture*
    //
    // < GETTING IMAGE SIZE >
    // https://discourse.libsdl.org/t/sdl2-get-the-texture-width-and-height/27053/2
    SDL_Point imgSize = getsize( txtmap[flNmOnly] );
    std::cout << "TEXTURE'S    WIDTH  IS  ->  " << imgSize.x << "    HEIGHT  IS  ->  "  <<  imgSize.y << std::endl;
    
    // ---------------------
    // SETTING TILESET FILE
    Tileset tileset;
    tileset.width = imgSize.x;
    tileset.height = imgSize.y;
    tileset.firstGridID = 1;                        // TODO :::******
    tileset.tileWidth = jsonObj.tile_size;
    tileset.tileHeight = jsonObj.tile_size;
    tileset.spacing = 0;
    tileset.margin = 0;
    tileset.name = flNmOnly;

    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    pTilesets->push_back(tileset);


}



void LevelDataLoader::parseTileLayerJson(
    TlSttrJsn_t jsonObj, 
    std::vector<Layer*> *pLayers, 
    const std::vector<Tileset>* pTilesets) {

    std::cout << "**** LAYER COUNT IS  -->  " << jsonObj.layerCount <<  "  !!!!"   << std::endl;

    // FOR EVERY LAYERS IN THE JSON FILE...
    for(int q=0; q < jsonObj.layerCount ; q++) {

        std::cout << jsonObj.layers[q].index     << std::endl;
        std::cout << jsonObj.layers[q].name      << std::endl;
        std::cout << jsonObj.layers[q].positions << std::endl;


        LayerTile* pLayerTiled = new LayerTile(jsonObj.tile_size, *pTilesets, jsonObj.map_width,  jsonObj.map_height);


        // CONTAINER FOR 'LAYER-TILED' DATA
        std::vector<std::vector<int>> data;

        
        // uLongf numGids = jsonObj.map_width * jsonObj.map_height * sizeof(int);
        // std::vector<unsigned> gids(numGids);
        // uncompress((Bytef*)&gids[0], &numGids,(const Bytef*)decodedIDs.c_str(), decodedIDs.size());


        // ----------------------------
        // < DECLARE VECTOR WITH SIZE >
        // https://www.simplilearn.com/tutorials/cpp-tutorial/how-to-initialize-a-vector-in-cpp
        // 
        // The syntax to declare a vector in C++ is:
        //
        // vector <type> vector_name(size)
        //
        std::vector<int> layerRow(jsonObj.map_width);


        // --------------------------------------------
        // < FILLING DATA STORES WITH ACTUAL TILE IDs >
        //
        // --------------------------
        // CREATING EMPTY SLOTS FIRST
        // 
        // HERE WE WANT TO USE 2D MATRIX OF INTEGER
        for(int j = 0; j < jsonObj.map_height; j++) {
            data.push_back(layerRow);
        }


        // --------------------------------------------
        // PREPARING JSON-ARRAY FOR 1 TILED-LAYER

        std::cout << jsonObj.layers[q].positions.size() << std::endl;


        // FILLING MATRIX WITH DATA
        int counter = 0;

        for(int cols = 0; cols < jsonObj.map_width; cols++) {
            for(int rows = 0; rows < jsonObj.map_height; rows++) {
        
                //std::cout << jsonObj.layers[q].positions[ counter ]["id"] << std::endl;

                // STORE TILE ID DATA
                // +1 IS TO CHANGE 1-BASED INDEX !!!!
                data[rows][cols] = static_cast<int> (jsonObj.layers[q].positions[ counter ]["id"]) + 1;
               
                // COUNTER INCREMENTING
                counter++;
            }
        }


        // TRANSFER TILE ID DATA TO LAYER-TILED
        pLayerTiled->SetTileIDs(data);
        pLayerTiled->SetTileSize(jsonObj.tile_size);
        
        pLayers->push_back(pLayerTiled);


        std::cout << "pLayerTiled is ...   " << pLayerTiled << std::endl;
        std::cout << "pLayers is ...      " << pLayers << std::endl;

    }

}





// --------------------------------------------------------------------------------------




// < LOADING TMX FILE AND PARSE >
// TMX FILE IS FROM 'TILED' EDITOR
Level* LevelDataLoader::ParseTLDTmx(const char *levelFile) {

    // create a TinyXML document and load the map XML
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    // create the level object
    Level* pLevel = new Level();

    // get the root node
    TiXmlElement* pRoot = levelDocument.RootElement();

    pRoot->Attribute("tilewidth", &m_tileSize);
    pRoot->Attribute("width",     &m_width);
    pRoot->Attribute("height",    &m_height);

    // --------------------------
    // < SEARCHING IN XML FILE >
    //
    // FOR EVERY TAG NAMES IN THE XML FILE,
    // HERE WE ARE SEARCHING tileset ELEMENT
    //
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("tileset")) {
            parseTilesetsTmx(e, pLevel->GetTilesets());												// SETTING UP TILESET
        }
    }

    // parse any object layers
    // NOW, WE ARE SEARCHING layer ELEMENT
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("layer")) {
            parseTileLayerTmx(e, pLevel->GetLayers(), pLevel->GetTilesets());							// SETTING UP TILE LAYER
        }
    }

    return pLevel;

}



void LevelDataLoader::parseTilesetsTmx(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets) {

    //std::string filaName = pTilesetRoot->FirstChildElement()->Attribute("source");

    // first add the tileset to texture manager
    Instance_ManagerTexture::Instance()->Load(pTilesetRoot->FirstChildElement()->Attribute("source"), pTilesetRoot->Attribute("name"), Instance_GameSDL::Instance()->GetRenderer());

    // create a tileset object

    // RETREIVING INFO FROM TAG NAME OF TMX FILE
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


// TMX FILE CONTAINS data ELEMENT, WHICH IS ENCRYPTED WITH BASE64 + COMPRESSED WITH ZLIB
// SO WE NEED TO SEARCH AND GET THE STRING DATA FROM THE ELEMENT,
// THEN DE-COMPRESS -> STORE THE INTEGER DATA
void LevelDataLoader::parseTileLayerTmx(TiXmlElement* pTileElement, 
    std::vector<Layer*> *pLayers, 
    const std::vector<Tileset>* pTilesets) {

    LayerTile* pTileLayer = new LayerTile(m_tileSize, *pTilesets, m_width, m_height);

    // tile data
    std::vector<std::vector<int>> data;

    std::string decodedIDs;
    TiXmlElement* pDataNode = nullptr;


    // WE ARE SEARCHING layer ELEMENT UNDER THE tileset ELEMENT
    // IN TMX FILE
    for(TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {

        if(e->Value() == std::string("data")) {
            pDataNode = e;
        }
    }

    // < DECODING USING base64 + DE-COMPRESSING USING zlib >
    // 
    // 
    for(TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling()) {

        // GETTING STRING FROM data ELEMENT !
        TiXmlText* text = e->ToText();

        // CONVERT TO STRING
        std::string t = text->Value();

        // DECODING STRING WITH base64 MODULE !!!!
        decodedIDs = base64_decode(t);
    }


    // numGids IS 
    // < HORIZONTAL COUNT OF TILES * VERTICAL COUNT OF TILES * UNIT AMOUNT OF ONE TILE >
    //                                                       < DATA TYPE OF TILE INDEX >
    //                                                                    |
    //                                         < WE NEED THIS BECAUSE uncompress FUNCTION NEEDS >
    //                                         < MEMORY ALLOCATION FOR DE-COMPRESSED MEMORY AREA >
    uLongf numGids = m_width * m_height * sizeof(int);
    




    std::cout << numGids << std::endl;



    // IF HORIZONTAL TILE COUNT IS 60, AND VERTICAL IS 30 THEN, 
    // numGids IS 7200
    //
    std::vector<unsigned> gids(numGids);


    // < ZLIB FUNCTION uncompress >
    // https://refspecs.linuxbase.org/LSB_3.0.0/LSB-Core-generic/LSB-Core-generic/zlib-uncompress-1.html
    //
    // ::  int uncompress(Bytef * dest, uLongf * destLen, const Bytef * source, uLong sourceLen);
    //                             |                |                      |              |
    //                          TARGET   BYTE LENGTH TO BE FILLED     INPUT DATA   LENGTH OF INPUT BYTE
    //
    //     The uncompress() function shall attempt to uncompress sourceLen bytes of data 
    //     in the buffer source, placing the result in the buffer dest.
    //     On entry, destLen should point to a value describing the size of the dest buffer. 
    //     The application should ensure that this value is large enough to hold the entire 
    //     uncompressed data.
    //
    // ** THIS IS FOR INDICATING START POINT OF MEMORY **
    //                 |
    //                 v
    uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

    std::vector<int> layerRow(m_width);

    for(int j = 0; j < m_height; j++) {

        data.push_back(layerRow);

    }

    for(int rows = 0; rows < m_height; rows++) {

        for(int cols = 0; cols < m_width; cols++) {

            data[rows][cols] = gids[rows * m_width + cols];

            std::cout << data[rows][cols] << std::endl;

        }
    }

    pTileLayer->SetTileIDs(data);

    pLayers->push_back(pTileLayer);


    //std::cout << "pTileLayer is ...   " << pTileLayer << std::endl;
    //std::cout << "pLayers is ...      " << pLayers << std::endl;

}



// < READING TEXT FROM FILE USING FASTER WAY >
// https://www.delftstack.com/howto/cpp/read-file-into-string-cpp/
std::string LevelDataLoader::readFileIntoString3(std::string& path) {
    struct stat sb{};
    std::string res;

    FILE* input_file = fopen(path.c_str(), "r");
    if (input_file == nullptr) {
        perror("fopen");
    }

    stat(path.c_str(), &sb);
    res.resize(sb.st_size);
    fread(const_cast<char*>(res.data()), sb.st_size, 1, input_file);
    fclose(input_file);

    return res;
}





}