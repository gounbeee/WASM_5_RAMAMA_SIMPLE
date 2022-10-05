
#ifndef INCLUDE_GUARD_MANAGERXML_H
#define INCLUDE_GUARD_MANAGERXML_H


#include <iostream>
#include <string>
#include <vector>
#include <tinyxml.h>
#include "GlobalTypes.h"


using namespace std;


enum xml_struct {
    MENU = 0, PLAY = 1,						// LAYER 1 :: STATES
	TEXTURES = 0, OBJECTS = 1,				// LAYER 2 :: ELEMENT TYPES
	FILENAME = 0, ID = 1,					// LAYER 2 :: ELEMENT TYPES
	// LAYER 3 :: ATTRIBUTES
	TYPE = 0, TEXTUREID = 1, XPOS = 2, YPOS = 3, WIDTH = 4, HEIGHT = 5, 
	STARTCOL = 6, STARTROW = 7, VELOX = 8, VELOY = 9, SCALE = 10, ANIMFRAMES = 11, ANIMSPEED = 12
};


class ManagerXML {

public:
    static const unsigned int NUM_INDENTS_PER_SPACE=2;

    ManagerXML();

    void ParseXML( const char* stateFile , MultiVectorStr4& result );

	MultiVectorStr4 GetXmlOutput() const { return m_pXmlData; }


    std::vector<std::vector< int > >    GetGameObjectList() { return m_gameObjectList ; }
    MultiVectorStr2                     GetGameObjectStringList() { return m_gameObjectStringList ; }
    MultiVectorStr2                     GetTextureList() { return m_textureIDList ; }
    std::vector<std::string>            GetGameStateList() { return m_gameStateList ; }


    const char* GetIndent( unsigned int numIndents );
    const char* GetIndentAlt( unsigned int numIndents );
    int Dump_attribs_to_stdout( TiXmlElement* pElement, unsigned int indent );
    void Dump_to_stdout( TiXmlNode* pParent, unsigned int indent = 0 );
    void Dump_to_stdout( const char* pFilename );

private:

	// CONTAINER FOR STORING XML STRUCTURE
	MultiVectorStr4 m_pXmlData;

	MultiVectorStr2 parseTextures( TiXmlElement* pElemType );
    MultiVectorStr2 parseObjects( TiXmlElement* pElemType );




    std::vector<std::vector<int> >  m_gameObjectList;
    MultiVectorStr2                 m_gameObjectStringList;
    MultiVectorStr2                 m_textureIDList;
    std::vector<std::string>        m_gameStateList;

    //void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs);
    //void parseObjects(TiXmlElement *pStateRoot, std::vector<std::string> *pGameObjectTypes);

};






#endif
