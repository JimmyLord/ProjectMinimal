//
// Copyright (c) 2012-2014 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "GameCommonHeader.h"

GameMinimalReplaceMe::GameMinimalReplaceMe()
{
    m_pShader_VertexColor = 0;
    m_pSprite = 0;

    m_Position.Set( 0, 0, 0 );
}

GameMinimalReplaceMe::~GameMinimalReplaceMe()
{
    SAFE_RELEASE( m_pSprite );
    SAFE_DELETE( m_pShader_VertexColor );
}

void GameMinimalReplaceMe::OneTimeInit()
{
    GameCore::OneTimeInit();

    // setup our shader.
    m_pShader_VertexColor = MyNew ShaderGroup( MyNew Shader_Base(ShaderPass_Main), 0, 0 );
    m_pShader_VertexColor->SetFileForAllPasses( "Data/Shaders/Shader_White" );

    // create a sprite, it's small since I'm not using a transform down below.
    m_pSprite = MyNew MySprite();
    m_pSprite->Create( 0.1f, 0.1f, 0, 1, 0, 1, Justify_Center, true );
    m_pSprite->SetShader( m_pShader_VertexColor );
}

void GameMinimalReplaceMe::Tick(double TimePassed)
{
    GameCore::Tick( TimePassed );
}

void GameMinimalReplaceMe::OnDrawFrame()
{
    GameCore::OnDrawFrame();

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // draw the sprite... no transform, so coords are in clip space.
    MyMatrix transform;
    transform.SetIdentity();
    transform.SetPosition( m_Position );

    m_pSprite->Draw( &transform );
}

void GameMinimalReplaceMe::OnTouch(int action, int id, float x, float y, float pressure, float size)
{
    GameCore::OnTouch( action, id, x, y, pressure, size );

    // prefer 0,0 at bottom left.
    y = m_WindowHeight - y;

    m_Position.x = (x / m_WindowWidth) * 2 - 1;
    m_Position.y = (y / m_WindowHeight) * 2 - 1;
}

void GameMinimalReplaceMe::OnButtons(GameCoreButtonActions action, GameCoreButtonIDs id)
{
    GameCore::OnButtons( action, id );
}
