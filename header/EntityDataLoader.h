
#ifndef INCLUDE_GUARD_ENTITYDATALOADER_H
#define INCLUDE_GUARD_ENTITYDATALOADER_H


#include <SDL.h>
#include <iostream>
#include <vector>


// LoaderParams CLASS
// :: MAGANAGES THE INDIVIDUAL TEXTURE WITH 'POSITION x,y', 'SIZE w,h' AND 'TEXTURE ID string'
class EntityDataLoader {

private:

    int m_x;
    int m_y;

    int m_startCol;
    int m_startRow;

    int m_width;
    int m_height;

    std::string m_textureID;

    int m_numFrames;
    int m_callbackID;
    int m_animSpeed;

public:

    // CONSTRUCTOR
    EntityDataLoader(   int x,
                    int y,
                    int width,
                    int height,
                    int startCol,
                    int startRow,
                    std::string textureID,
                    int numFrames,
                    int callbackID = 0,
                    int animSpeed = 0 ):
                    m_x(x),
                    m_y(y),
                    m_width(width),
                    m_height(height),
                    m_startCol(startCol),
                    m_startRow(startRow),
                    m_textureID(textureID),
                    m_numFrames(numFrames),
                    m_callbackID(callbackID),
                    m_animSpeed(animSpeed) {

    }

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getStartCol() const { return m_startCol; }
    int getStartRow() const { return m_startRow; }
    std::string getTextureID() const { return m_textureID; }
    int getNumFrames() const { return m_numFrames; }
    int getCallbackID() const { return m_callbackID; }
    int getAnimSpeed() const { return m_animSpeed; }
};


#endif
