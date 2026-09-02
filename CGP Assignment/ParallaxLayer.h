#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "DirectXManager.h"

class ParallaxLayer
{
private:
    LPDIRECT3DTEXTURE9 texture;

    RECT sourceRect;

    D3DXVECTOR3 position[3];

    float speed;
    float segmentWidth;
    float yPosition;

public:
    ParallaxLayer();
    ~ParallaxLayer();

    bool Initialise(
        const char* textureName,
        RECT rect,
        float moveSpeed,
        float y = 0.0f
    );

    void Update();

    void Render();

    void CleanUp();
};