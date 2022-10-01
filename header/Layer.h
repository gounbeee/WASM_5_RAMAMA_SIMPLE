#ifndef INCLUDE_GUARD_LAYER_H
#define INCLUDE_GUARD_LAYER_H

// BELOW IS NEEDED FOR USING Vector2D IN PARAMETER OF FUNCTION SetVelocity()
class Vector2D;

class Layer {

public:

    virtual void Render() = 0;
    virtual void Update() = 0;
    virtual ~Layer() {}
	virtual void SetVelocity( Vector2D vel ) = 0;

};



#endif
