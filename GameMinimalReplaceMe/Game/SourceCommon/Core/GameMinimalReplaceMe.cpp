//
// Copyright (c) 2012-2019 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "GamePCH.h"

GameMinimalReplaceMe::GameMinimalReplaceMe()
{
    m_pSprite = nullptr;

    m_Position.Set( 0, 0, 0 );
}

GameMinimalReplaceMe::~GameMinimalReplaceMe()
{
    m_pSprite->Release();
}

//====================================================================================================
// Initialization.
//====================================================================================================

void GameMinimalReplaceMe::OneTimeInit()
{
    GameCore::OneTimeInit();

    // Set Clear color to dark blue.
    m_pRenderer->SetClearColor( ColorFloat( 0.0f, 0.0f, 0.2f, 0.0f ) );
    m_pRenderer->SetClearDepth( 1.0f );

    // Create a shader, texture and material.
    ShaderGroup* pShader = MyNew ShaderGroup( this, "Data/Shaders/Shader_Texture.glsl", nullptr );
    TextureDefinition* pTexture = this->GetManagers()->GetTextureManager()->CreateTexture( "Data/Textures/Clouds.png" );
    MaterialDefinition* pMaterial = this->GetManagers()->GetMaterialManager()->CreateMaterial();

    // Assign the shader and texture to the material.
    pMaterial->SetShader( pShader );
    pMaterial->SetTextureColor( pTexture );

    // Create a sprite, it's small since there's no view or projection matrix down below.
    m_pSprite = MyNew MySprite();
    m_pSprite->Create( this->GetManagers()->GetBufferManager(), 0.1f, 0.1f, 0, 1, 0, 1, Justify_Center, true );
    m_pSprite->SetMaterial( pMaterial );

    // Release the shader, texture and material.
    pMaterial->Release();
    pTexture->Release();
    pShader->Release();
}

//====================================================================================================
// Input/Event handling.
//====================================================================================================

bool GameMinimalReplaceMe::OnTouch(int action, int id, float x, float y, float pressure, float size)
{
    if( GameCore::OnTouch( action, id, x, y, pressure, size ) )
        return true;

    // Prefer 0,0 at bottom left.
    y = GetWindowHeight() - y;

    // Move the square to the mouse position in clip space.
    m_Position.x = (x / GetWindowWidth()) * 2 - 1;
    m_Position.y = (y / GetWindowHeight()) * 2 - 1;

    return false;
}

bool GameMinimalReplaceMe::OnButtons(GameCoreButtonActions action, GameCoreButtonIDs id)
{
    return GameCore::OnButtons( action, id );
}

//====================================================================================================
// Update/Draw.
//====================================================================================================

float GameMinimalReplaceMe::Tick(float deltaTime)
{
    return GameCore::Tick( deltaTime );
}

void GameMinimalReplaceMe::OnDrawFrame(unsigned int canvasid)
{
    GameCore::OnDrawFrame( 0 );

    // Clear the screen.
    m_pRenderer->ClearBuffers( true, true, false );

    // Draw the sprite. No camera or projection, so coordinates are in clip space.
    MyMatrix transform;
    transform.CreateTranslation( m_Position );

    m_pSprite->Draw( nullptr, nullptr, &transform );
}
