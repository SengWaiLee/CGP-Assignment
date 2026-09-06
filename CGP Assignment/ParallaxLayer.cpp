#include "ParallaxLayer.h"
#include <iostream>

using namespace std;

ParallaxLayer::ParallaxLayer()
{
    texture = NULL;

    speed = 0.0f;
    segmentWidth = 0.0f;
    yPosition = 0.0f;

    ZeroMemory(&sourceRect, sizeof(sourceRect));

    for (int i = 0; i < 3; i++)
    {
        position[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }
}

ParallaxLayer::~ParallaxLayer()
{
}


bool ParallaxLayer::Initialise(const char* textureName,RECT rect,float moveSpeed,float y)
{
    HRESULT hr = D3DXCreateTextureFromFileA(DirectXManager::myVirtualGPU,textureName,&texture);

    if (FAILED(hr))
    {
        cout << "Failed to load: " << textureName << endl;
        return false;
    }

    sourceRect = rect;

    speed = moveSpeed;
    yPosition = y;

    segmentWidth = static_cast<float>(sourceRect.right - sourceRect.left);

    position[0] = D3DXVECTOR3(0.0f,yPosition,0.0f);

    position[1] = D3DXVECTOR3(segmentWidth,yPosition,0.0f);

    position[2] = D3DXVECTOR3(segmentWidth * 2.0f,yPosition,0.0f);

    return true;
}


void ParallaxLayer::Update()
{
    for (int i = 0; i < 3; i++)
    {
        position[i].x -= speed;

        if (position[i].x <= -segmentWidth)
        {
            position[i].x += segmentWidth * 3.0f;
        }
    }
}

void ParallaxLayer::Render()
{
    if (!texture)
        return;

    D3DXMATRIX identityMatrix;
    D3DXMatrixIdentity(&identityMatrix);

    DirectXManager::spriteBrush->SetTransform(&identityMatrix);
    for (int i = 0; i < 3; i++)
    {
        DirectXManager::spriteBrush->Draw(texture,&sourceRect,NULL,&position[i],D3DCOLOR_XRGB(255,255,255));
    }
}

void ParallaxLayer::CleanUp()
{
    if (texture)
    {
        texture->Release();
        texture = NULL;
    }
}