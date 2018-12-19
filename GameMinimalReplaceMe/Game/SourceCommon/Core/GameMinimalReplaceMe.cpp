//
// Copyright (c) 2012-2018 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "GameCommonHeader.h"
#include "../../../Framework/MyFramework/SourceCommon/Renderers/Renderer_Base.h"

GameMinimalReplaceMe::GameMinimalReplaceMe()
{
    m_pSprite = 0;

    m_Position.Set( 0, 0, 0 );
}

GameMinimalReplaceMe::~GameMinimalReplaceMe()
{
    m_pSprite->Release();
}

void GameMinimalReplaceMe::OneTimeInit()
{
    GameCore::OneTimeInit();

    // Set Clear color to dark blue.
    m_pRenderer->SetClearColor( ColorFloat( 0.0f, 0.0f, 0.2f, 0.0f ) );
    m_pRenderer->SetClearDepth( 1.0f );

    // Create a shader group and a material with that shader.
    ShaderGroup* pShader_White = MyNew ShaderGroup( "Data/Shaders/Shader_White.glsl" );
    MaterialDefinition* pMaterialWhite = g_pMaterialManager->CreateMaterial();
    pMaterialWhite->SetShader( pShader_White );

    // Create a sprite, it's small since there's no camera or projection down below.
    m_pSprite = MyNew MySprite( false );
    m_pSprite->Create( 0.1f, 0.1f, 0, 1, 0, 1, Justify_Center, true );
    m_pSprite->SetMaterial( pMaterialWhite );

    // Release the shader and material.
    pMaterialWhite->Release();
    pShader_White->Release();
}

float GameMinimalReplaceMe::Tick(float deltaTime)
{
    return GameCore::Tick( deltaTime );
}

void GameMinimalReplaceMe::OnDrawFrame(unsigned int canvasid)
{
    checkGlError( "Start of OnDrawFrame.\n" );

    GameCore::OnDrawFrame( 0 );

    // Clear the screen.
    m_pRenderer->ClearBuffers( true, true, false );

    // Draw the sprite. No camera or projection, so coords are in clip space.
    MyMatrix transform;
    transform.CreateTranslation( m_Position );

    m_pSprite->Draw( 0, 0, 0, &transform, 0, 0, 0, 0, 0, 0, 0, 0, false );

    checkGlError( "After sprite draw.\n" );
}

bool GameMinimalReplaceMe::OnTouch(int action, int id, float x, float y, float pressure, float size)
{
    if( GameCore::OnTouch( action, id, x, y, pressure, size ) )
        return true;

    // Prefer 0,0 at bottom left.
    y = GetWindowHeight() - y;

    m_Position.x = (x / GetWindowWidth()) * 2 - 1;
    m_Position.y = (y / GetWindowHeight()) * 2 - 1;

    return false;
}

bool GameMinimalReplaceMe::OnButtons(GameCoreButtonActions action, GameCoreButtonIDs id)
{
    return GameCore::OnButtons( action, id );
}
