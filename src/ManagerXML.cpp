

#include <ManagerXML.h>


extern "C" {



ManagerXML::ManagerXML(const char* xmlFileName) {
	// FOR DEBUG PURPOSE
    //Dump_to_stdout( "data.xml" );

    ParseXML( xmlFileName, m_pXmlData );

}

void ManagerXML::ParseXML( const char* stateFile , MultiVectorStr4& result ) {
										//        states /ElemTypes /Elements         /Attributes (Multiple)
										// i.e   <MENU>  <TEXTURES>  <texture> 1,2...  filename, ID, type.....
	// Create the XML ducument
    TiXmlDocument xmlDoc;

    // load the state file
	xmlDoc.LoadFile( stateFile );

	/*
    if( !xmlDoc.LoadFile( stateFile ) ) {                                       // IF THERE IS AN ERROR WHEN LOADING THE XML FILE
        std::cerr << xmlDoc.ErrorDesc() << "\n";                                // PRINT THAT
        return 0;
    }
	*/

    // getting the root ELEMENT
    TiXmlElement* pRoot = xmlDoc.RootElement();                                 // GETTING ROOT ELEMENT



	// TODO :: FIX BELOW'S CODE-DUPLICATION
    // Getting This State Root Node And Assign It To pStateRoot
	// SO, FOR EVERY STATE TYPE
	MultiVectorStr4 stateTypeArray;
	
    for( TiXmlElement* state = pRoot->FirstChildElement(); state != NULL; state = state->NextSiblingElement() ){    // pRoot->FirstChildElement() WILL BE "<MENU>" ELEMENT IN THE FILE


		if( state->Value() == std::string("MENU") ) {

			MultiVectorStr3 elemTypeArray;
			// FOR EVERY ELEMENT TYPE
			for( TiXmlElement* elemType = state->FirstChildElement(); elemType != NULL; elemType = elemType->NextSiblingElement() ) {     // <TEXTURE> ELEMENT CHECKING


				MultiVectorStr2 texAttribs;
				MultiVectorStr2 objAttribs;
				// TEXTURE PARSING
				if( elemType->Value() == std::string("TEXTURES")) {
					// GETTING TEXTURE ATTRIBUTES
					texAttribs = parseTextures( elemType );
					// STORING TO elemTypeArray VECTOR
					elemTypeArray.push_back( texAttribs );
				}
				// OBJECT PARSING
				if( elemType->Value() == std::string( "OBJECTS" )) {
					// GETTING OBJECTS ATTRIBUTES
					objAttribs = parseObjects( elemType );
					// STORING TO elemTypeArray VECTOR
					elemTypeArray.push_back( objAttribs );
				}
			}
			stateTypeArray.push_back( elemTypeArray );
		}


		if( state->Value() == std::string("PLAY") ) {

			vector<vector<vector<string> > > elemTypeArray;
			// FOR EVERY ELEMENT TYPE
			for( TiXmlElement* elemType = state->FirstChildElement(); elemType != NULL; elemType = elemType->NextSiblingElement() ) {     // <TEXTURE> ELEMENT CHECKING


				MultiVectorStr2 texAttribs;
				MultiVectorStr2 objAttribs;

				// TEXTURE PARSING
				if( elemType->Value() == std::string("TEXTURES")) {
					// GETTING TEXTURE ATTRIBUTES
					texAttribs = parseTextures( elemType );
					// STORING TO elemTypeArray VECTOR
					elemTypeArray.push_back( texAttribs );
				}
				// OBJECT PARSING
				if( elemType->Value() == std::string( "OBJECTS" )) {
					// GETTING OBJECTS ATTRIBUTES
					objAttribs = parseObjects( elemType );
					// STORING TO elemTypeArray VECTOR
					elemTypeArray.push_back( objAttribs );
				}
			}
			stateTypeArray.push_back( elemTypeArray );
		}

		if( state->Value() == std::string("PAUSE") ) {

			vector<vector<vector<string> > > elemTypeArray;
			// FOR EVERY ELEMENT TYPE
			for( TiXmlElement* elemType = state->FirstChildElement(); elemType != NULL; elemType = elemType->NextSiblingElement() ) {     // <TEXTURE> ELEMENT CHECKING


				MultiVectorStr2 texAttribs;
				MultiVectorStr2 objAttribs;
				
				// TEXTURE PARSING
				if( elemType->Value() == std::string("TEXTURES")) {
					// GETTING TEXTURE ATTRIBUTES
					texAttribs = parseTextures( elemType );
					// STORING TO elemTypeArray VECTOR
					elemTypeArray.push_back( texAttribs );
				}
				// OBJECT PARSING
				if( elemType->Value() == std::string( "OBJECTS" )) {
					// GETTING OBJECTS ATTRIBUTES
					objAttribs = parseObjects( elemType );
					// STORING TO elemTypeArray VECTOR
					elemTypeArray.push_back( objAttribs );
				}
			}
			stateTypeArray.push_back( elemTypeArray );
		}

    }

	
    result = stateTypeArray;

}


void ManagerXML::ParseAnimXML( const char* stateFile , MultiVectorStr4& result ) {
										//        states /ElemTypes /Elements         /Attributes (Multiple)
										// i.e   <MENU>  <TEXTURES>  <texture> 1,2...  filename, ID, type.....
	// Create the XML ducument
    TiXmlDocument xmlDoc;

    // load the state file
	xmlDoc.LoadFile( stateFile );

	/*
    if( !xmlDoc.LoadFile( stateFile ) ) {                                       // IF THERE IS AN ERROR WHEN LOADING THE XML FILE
        std::cerr << xmlDoc.ErrorDesc() << "\n";                                // PRINT THAT
        return 0;
    }
	*/

    // getting the root ELEMENT
    TiXmlElement* pRoot = xmlDoc.RootElement();                                 // GETTING ROOT ELEMENT



	// TODO :: FIX BELOW'S CODE-DUPLICATION
    // Getting This State Root Node And Assign It To pStateRoot
	// SO, FOR EVERY STATE TYPE
	MultiVectorStr4 stateTypeArray;
	
    for( TiXmlElement* state = pRoot->FirstChildElement(); state != NULL; state = state->NextSiblingElement() ){    // pRoot->FirstChildElement() WILL BE "<MENU>" ELEMENT IN THE FILE


		if( state->Value() == std::string("MENU") ) {

			MultiVectorStr3 elemTypeArray;
			// FOR EVERY ELEMENT TYPE
			for( TiXmlElement* elemType = state->FirstChildElement(); elemType != NULL; elemType = elemType->NextSiblingElement() ) {     // <TEXTURE> ELEMENT CHECKING


				MultiVectorStr2 texAttribs;
				MultiVectorStr2 objAttribs;
				// TEXTURE PARSING
				if( elemType->Value() == std::string("TEXTURES")) {
					// GETTING TEXTURE ATTRIBUTES
					texAttribs = parseTextures( elemType );
					// STORING TO elemTypeArray VECTOR
					elemTypeArray.push_back( texAttribs );
				}
				// OBJECT PARSING
				if( elemType->Value() == std::string( "OBJECTS" )) {
					// GETTING OBJECTS ATTRIBUTES
					objAttribs = parseObjects( elemType );
					// STORING TO elemTypeArray VECTOR
					elemTypeArray.push_back( objAttribs );
				}
			}
			stateTypeArray.push_back( elemTypeArray );
		}


		if( state->Value() == std::string("PLAY") ) {

			vector<vector<vector<string> > > elemTypeArray;
			// FOR EVERY ELEMENT TYPE
			for( TiXmlElement* elemType = state->FirstChildElement(); elemType != NULL; elemType = elemType->NextSiblingElement() ) {     // <TEXTURE> ELEMENT CHECKING


				MultiVectorStr2 texAttribs;
				MultiVectorStr2 objAttribs;

				// TEXTURE PARSING
				if( elemType->Value() == std::string("TEXTURES")) {
					// GETTING TEXTURE ATTRIBUTES
					texAttribs = parseTextures( elemType );
					// STORING TO elemTypeArray VECTOR
					elemTypeArray.push_back( texAttribs );
				}
				// OBJECT PARSING
				if( elemType->Value() == std::string( "OBJECTS" )) {
					// GETTING OBJECTS ATTRIBUTES
					objAttribs = parseObjects( elemType );
					// STORING TO elemTypeArray VECTOR
					elemTypeArray.push_back( objAttribs );
				}
			}
			stateTypeArray.push_back( elemTypeArray );
		}

		if( state->Value() == std::string("PAUSE") ) {

			vector<vector<vector<string> > > elemTypeArray;
			// FOR EVERY ELEMENT TYPE
			for( TiXmlElement* elemType = state->FirstChildElement(); elemType != NULL; elemType = elemType->NextSiblingElement() ) {     // <TEXTURE> ELEMENT CHECKING


				MultiVectorStr2 texAttribs;
				MultiVectorStr2 objAttribs;
				
				// TEXTURE PARSING
				if( elemType->Value() == std::string("TEXTURES")) {
					// GETTING TEXTURE ATTRIBUTES
					texAttribs = parseTextures( elemType );
					// STORING TO elemTypeArray VECTOR
					elemTypeArray.push_back( texAttribs );
				}
				// OBJECT PARSING
				if( elemType->Value() == std::string( "OBJECTS" )) {
					// GETTING OBJECTS ATTRIBUTES
					objAttribs = parseObjects( elemType );
					// STORING TO elemTypeArray VECTOR
					elemTypeArray.push_back( objAttribs );
				}
			}
			stateTypeArray.push_back( elemTypeArray );
		}

    }

	
    result = stateTypeArray;

}


MultiVectorStr2 ManagerXML::parseTextures( TiXmlElement* pElemType ) {
	
	MultiVectorStr2 textureAttribs;
    
	// FOR EVERY TEXTURE ELEMENTS
    for( TiXmlElement* texElem = pElemType->FirstChildElement(); texElem != NULL; texElem = texElem->NextSiblingElement() ) {

        std::string filenameAttribute = texElem->Attribute("filename");                                                           // GETTING 'ATTRIBUTE filename' IN THE XML FILE
        std::string idAttribute = texElem->Attribute("ID");                                                                       // GETTING 'ATTRIBUTE ID' IN THE XML FILE

        textureAttribs.push_back( {filenameAttribute , idAttribute} );

        std::cout << "---- XMLManager::IN PARSING TEXTURES -------    OK" << "\n";
    }

	return textureAttribs;
}


MultiVectorStr2 ManagerXML::parseObjects( TiXmlElement* pElemType ) {
	
	MultiVectorStr2 objectStringAttribs;
	
	for( TiXmlElement* objElem = pElemType->FirstChildElement(); objElem != NULL; objElem = objElem->NextSiblingElement() ) {
		
		// FINAL RESULTS WE  TO GET
		int x, y, width, height, startCol, startRow, velocityX, velocityY, scale, animFrames, animSpeed;                                                      
		
		std::string textureID;
		std::string type;

		objElem->Attribute("x", &x);                                                                                          // GETTING ATTRIBUTES
																														// sets the variable x to the value contained within attribute
		objElem->Attribute("y", &y);
		objElem->Attribute("width",&width);
		objElem->Attribute("height", &height);
		objElem->Attribute("startColumn", &startCol);
		objElem->Attribute("startRow", &startRow);
		objElem->Attribute("velocityX", &velocityX);
		objElem->Attribute("velocityY", &velocityY);
		objElem->Attribute("scale", &scale);
		objElem->Attribute("animFrames", &animFrames);
		objElem->Attribute("animSpeed", &animSpeed);
		textureID = objElem->Attribute("textureID");
		type = objElem->Attribute("type");

		objectStringAttribs.push_back( {					type,						// 0
															textureID,					// 1
															to_string(x),				// 2
															to_string(y),				// 3
															to_string(width),			// 4
															to_string(height),			// 5
															to_string(startCol),		// 6
															to_string(startRow),		// 7
															to_string(velocityX),		// 8
															to_string(velocityY),		// 9
															to_string(scale),			// 10
															to_string(animFrames),		// 11
															to_string(animSpeed) } );	// 12

		std::cout << "---- XMLManager::IN PARSING OBJECTS -------    OK" << "\n";
	}

	return objectStringAttribs;
}








const char* ManagerXML::GetIndent( unsigned int numIndents ) {
	static const char * pINDENT="                                      + ";
	static const unsigned int LENGTH=strlen( pINDENT );
	unsigned int n = numIndents*NUM_INDENTS_PER_SPACE;
	if ( n > LENGTH ) n = LENGTH;

	return &pINDENT[ LENGTH-n ];
}




// same as getIndent but no "+" at the end
const char* ManagerXML::GetIndentAlt( unsigned int numIndents ) {
	static const char * pINDENT="                                        ";
	static const unsigned int LENGTH=strlen( pINDENT );
	unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
	if ( n > LENGTH ) n = LENGTH;

	return &pINDENT[ LENGTH-n ];
}




int ManagerXML::Dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent) {
	if ( !pElement ) return 0;

	TiXmlAttribute* pAttrib=pElement->FirstAttribute();
	int i=0;
	int ival;
	double dval;
	const char* pIndent=GetIndent(indent);
	printf("\n");
	while (pAttrib)
	{
		printf( "%s%s: value=[%s]", pIndent, pAttrib->Name(), pAttrib->Value());

		if (pAttrib->QueryIntValue(&ival)==TIXML_SUCCESS)    printf( " int=%d", ival);
		if (pAttrib->QueryDoubleValue(&dval)==TIXML_SUCCESS) printf( " d=%1.1f", dval);
		printf( "\n" );
		i++;
		pAttrib=pAttrib->Next();
	}
	return i;
}




void ManagerXML::Dump_to_stdout( TiXmlNode* pParent, unsigned int indent ) {
	if ( !pParent ) return;

	TiXmlNode* pChild;
	TiXmlText* pText;
	int t = pParent->Type();
	printf( "%s", GetIndent(indent));
	int num;

	switch ( t ) {

        // https://sourceforge.net/p/tinyxml/discussion/42748/thread/cd0dd5a4/
    	case TiXmlNode::TINYXML_DOCUMENT:
    		printf( "Document" );
    		break;

    	case TiXmlNode::TINYXML_ELEMENT:
    		printf( "Element [%s]", pParent->Value() );
    		num = Dump_attribs_to_stdout(pParent->ToElement(), indent+1);
    		switch(num)
    		{
    			case 0:  printf( "        (No attributes)"); break;
    			case 1:  printf( "%s1 attribute", GetIndentAlt(indent)); break;
    			default: printf( "%s%d attributes", GetIndentAlt(indent), num); break;
    		}
    		break;

    	case TiXmlNode::TINYXML_COMMENT:
    		printf( "Comment: [%s]", pParent->Value());
    		break;

    	case TiXmlNode::TINYXML_UNKNOWN:
    		printf( "Unknown" );
    		break;

    	case TiXmlNode::TINYXML_TEXT:
    		pText = pParent->ToText();
    		printf( "Text: [%s]", pText->Value() );
    		break;

    	case TiXmlNode::TINYXML_DECLARATION:
    		printf( "Declaration" );
    		break;
    	default:
    		break;
	}

	printf( "\n" );
	for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
		Dump_to_stdout( pChild, indent+1 );
	}

}



// load the named file and dump its structure to STDOUT
void ManagerXML::Dump_to_stdout(const char* pFilename) {
	TiXmlDocument doc(pFilename);
	bool loadOkay = doc.LoadFile();

	if (loadOkay) {
		printf("\n%s:\n", pFilename);
		Dump_to_stdout( &doc );                               // RECURSIVE FUNCTION
	} else {
		printf("Failed to load file \"%s\"\n", pFilename);
	}
}



}
