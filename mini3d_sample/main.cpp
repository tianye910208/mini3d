

// Copyright (c) <2011> Daniel Peterson
// This file is part of Mini3D <www.mini3d.org>
// It is distributed under the MIT Software License <www.mini3d.org/license.php>

/*

MINI3D TUTORIAL 1 - THE HELLO CUBE TUTORIAL

This file is part of the mini3d tutorial series. It shows the basics of how to write a simple application using Mini3D.
For full informationabout this tutorial, please go to: www.mini3d.org/tutorials.php
*/

#include "../graphics.hpp"
#include "../system.hpp"
#include "../math.hpp"
#include "../animation.hpp"

#include <cstring>
#include <stdarg.h>
#include <cstdio>
#include <cstdlib>

#include "shaders.hpp"
#include "geometry.hpp"
#include "bitmap.hpp"


void mini3d_assert(bool expression, const char* text, ...) 
{ 
    va_list va;
    va_start(va, text);

    if (!expression) 
    { 
        fprintf(stderr, "ERROR: "); 
        vfprintf(stderr, text, va);
        fprintf(stderr, "\n");

        exit(1); 
    } 
}


// ----- DECLARE VARIABLES ----------------------------------------------------

// state variables
bool exitApplication = false;

// Keeps track of mouse movement
int mouseX, mouseY;

// Keeps track of the view angle and camera distance
float rotX = 3.1415f / 3.0f;
float rotY = 3.1415f / 6.0f;
float distance = 10.0f;

// Forward declaration of event handler
void HandleEvent(mini3d::system::Event ev);
void Render();


// ----- DECLARE GRAPHICS RESOURCES -------------------------------------------

// Render Window
mini3d::system::IWindow* window;

// Graphics Service
mini3d::graphics::IGraphicsService* graphics;

// Graphics Resources
mini3d::graphics::IWindowRenderTarget* pWindowRenderTarget;
mini3d::graphics::IIndexBuffer* iBuffer;
mini3d::graphics::IVertexBuffer* vBuffer;
mini3d::graphics::IBitmapTexture* pTexture;
mini3d::graphics::IVertexShader* pVertexShader;
mini3d::graphics::IPixelShader* pPixelShader;
mini3d::graphics::IShaderProgram* pShaderProgram;
mini3d::graphics::IShaderInputLayout* pInputLayout;
mini3d::graphics::IConstantBuffer* pConstantBuffer;


// ----- CREATE ANIMATION -----------------------------------------------------

mini3d::animation::Keyframe<mini3d::math::Vec3> keyFrames[] = {  {0.0f, mini3d::math::Vec3(0.0f, 0.0f, 0.0f) }, 
                                                                 {0.5f, mini3d::math::Vec3(1.0f, 1.0f, 1.0f) }, 
                                                                 {1.0f, mini3d::math::Vec3(0.0f, 0.0f, 0.0f) }, 
                                                                 {1.5f, mini3d::math::Vec3(1.0f, 1.0f, 1.0f) },
                                                                 {2.0f, mini3d::math::Vec3(0.0f, 0.0f, 0.0f) } };


mini3d::math::Transform objectTransform = mini3d::math::Transform::Identity(); // Animation target

mini3d::animation::Track<mini3d::math::Vec3> track(&objectTransform.pos, keyFrames, 5);
mini3d::animation::ITrack* tracks[] = { &track };
mini3d::animation::Animation animation(tracks, 1, 2.0f);

mini3d::animation::AnimationManager animationManager; // We add the animation to the animation manager in the code below!



// Tutorial Application    
int mini3d_main(int argc, char *argv[])
{
    // Create the animation
    animationManager.AddAnimation(&animation);

    // Create the graphics service object. 
    // This is used to create all the graphics resources below!
    graphics = mini3d::graphics::IGraphicsService::New();

    // create index buffer
    iBuffer = mini3d::graphics::IIndexBuffer::New(graphics, (const char*)indices, 36);

    // create vertex buffer
    vBuffer = mini3d::graphics::IVertexBuffer::New(graphics, (const char*)vertices, 24, sizeof(VertexPCT));

    // Create a 32bpp texture
    unsigned int* pBitmap = CreateTestBitmapRGBA8(256, 256);
    pTexture = mini3d::graphics::IBitmapTexture::New(graphics, (const char*)pBitmap, 256, 256); 
    delete(pBitmap);

    // Create a shader program
    if (graphics->GetCompatibility()->GetShaderLanguage() == mini3d::graphics::ICompatibility::GLSL)
    {
        pVertexShader = mini3d::graphics::IVertexShader::New(graphics, vertexShaderGLSL, strlen(vertexShaderGLSL));
        pPixelShader = mini3d::graphics::IPixelShader::New(graphics, pixelShaderGLSL, strlen(pixelShaderGLSL));
    }
    else
    {
        pVertexShader = mini3d::graphics::IVertexShader::New(graphics, vertexShaderHLSL, strlen(vertexShaderHLSL));
        pPixelShader = mini3d::graphics::IPixelShader::New(graphics, pixelShaderHLSL, strlen(pixelShaderHLSL));
    }
    
    pShaderProgram = mini3d::graphics::IShaderProgram::New(graphics, pVertexShader, pPixelShader);

    // Create shader vertex input layout
    mini3d::graphics::IShaderInputLayout::InputElement inputElements[] = {
        { "IN_position", "POSITION", 0, 0, 0, mini3d::graphics::IShaderInputLayout::R32G32B32A32_FLOAT, mini3d::graphics::IShaderInputLayout::PER_VERTEX },
        { "IN_color", "TEXCOORD", 0, 0, 16, mini3d::graphics::IShaderInputLayout::R32G32B32A32_FLOAT, mini3d::graphics::IShaderInputLayout::PER_VERTEX },
        { "IN_texCoords", "TEXCOORD", 1, 0, 32, mini3d::graphics::IShaderInputLayout::R32G32_FLOAT, mini3d::graphics::IShaderInputLayout::PER_VERTEX }};

    pInputLayout = mini3d::graphics::IShaderInputLayout::New(graphics, pShaderProgram, inputElements, 3);

    // Create shader constants buffer
    const char* shaderConstantNames[] = { "modelViewProj" };
    pConstantBuffer = mini3d::graphics::IConstantBuffer::New(graphics, 16 * sizeof(float), pShaderProgram, shaderConstantNames, 1);

    // Create a window.
    window = mini3d::system::IWindow::New("Mini3D Tutorial 1", 800, 600);

      // Create Window Render Target
    pWindowRenderTarget = mini3d::graphics::IWindowRenderTarget::New(graphics, window->GetNativeWindow(), true);

    // Display the window
    window->Show();


    // Main loop

    mini3d::system::Timer timer;
    timer.Start();

    // loop while the window is not closed
    while(exitApplication == false)
    {
        mini3d::system::Event ev;

        while (window->GetEvent(ev))
            HandleEvent(ev);

        mini3d::system::SystemEvent sev;
        while (mini3d::system::ISystem::GetInstance()->GetEvent(sev))
            ; // Do nothing for now!

        // GetIntervalInMicroSeconds will return the time interval since the last call to this function
        float timeStep = timer.GetIntervalInMicroSeconds() / 1000000.0f;
        
        // Update animations
        animationManager.Update(timeStep);

        Render();

        // Limit the framerate
        mini3d::system::IThread::SleepCurrentThread(15);
    }

    // ----- DELETE RESOURCES -------------------------------------------------

    delete vBuffer;
    delete iBuffer;
    delete pTexture;
    delete pPixelShader;
    delete pVertexShader;
    delete pShaderProgram;
    delete pWindowRenderTarget;
    delete pConstantBuffer;
    delete pInputLayout;
    delete window;
    delete graphics;

    return 0;
}

// Used for creating view projection matrix below
const mini3d::math::Vec3 at = mini3d::math::Vec3(0.0f, 0.0f, 0.0f);
const mini3d::math::Vec3 up = mini3d::math::Vec3(0.0f, 1.0f, 0.0f);

void Render()
{
    // Set the render target (always do this before setting shader program)
    graphics->SetRenderTarget(pWindowRenderTarget);

    // Set shader program (always set the shader program before assigning any resources)
    graphics->SetShaderProgram(pShaderProgram);

    // Set the Texture
    graphics->SetTexture(pTexture, 0, "texture0");

    // set render prarameters
    graphics->SetIndexBuffer(iBuffer);
    graphics->SetVertexBuffer(vBuffer);

    // Set the ViewProjection matrix
    mini3d::math::Vec3 eye = mini3d::math::Vec3(distance * cos(rotY) * cos(rotX), distance * sin(rotY), distance * cos(rotY) * sin(rotX));
    mini3d::math::Transform t = mini3d::math::Transform::LookAtRH(eye, at, up);
    t = t * objectTransform;

    unsigned int width;
    unsigned int height;
    window->GetWindowContentSize(width, height);

    float viewProjectionMatrix[16];
    t.ToViewProjectionMatrix(viewProjectionMatrix, (float)(3.1416f / 4.0f), (float)width/height, 0.01f, 100.0f);

    pConstantBuffer->SetData((const char*)&viewProjectionMatrix);
    graphics->SetConstantBuffer(pConstantBuffer, 0, "");

    graphics->SetShaderInputLayout(pInputLayout);

    // clear render target with color
    graphics->Clear(0.5,0.5,0.5,1.0,1.0);

    // draw the scene to the render target texture
    graphics->Draw();

    // do a flip
    pWindowRenderTarget->Display();

}

void HandleEvent(mini3d::system::Event ev)
{
    switch(ev.type)
    {
        case mini3d::system::Event::CLOSE:
            exitApplication = true;
        break;
        case mini3d::system::Event::MOUSE_DOWN:
        {
            unsigned int width;
            unsigned int height;
            window->GetWindowContentSize(width, height);

            if (ev.mouseButton.x < width / 10)
                animation.Play();

            mouseX = ev.mouseButton.x;
            mouseY = ev.mouseButton.y;
        }
        break;
        case mini3d::system::Event::MOUSE_MOVE:
            if (ev.mouseMove.buttons & mini3d::system::Event::LEFT)
            {
                rotX += (ev.mouseMove.x - mouseX) / 100.0f;
                rotY += (ev.mouseMove.y - mouseY) / 100.0f;

                mouseX = ev.mouseMove.x;
                mouseY = ev.mouseMove.y;
            }
        break;
        case mini3d::system::Event::MOUSE_WHEEL:
            distance -= (float)ev.mouseWheel.delta * 0.01f;
        break;
        case mini3d::system::Event::KEY_DOWN:
            if (ev.key.keyCode == mini3d::system::Event::UKID_F2)
            {
                
                if (window->GetScreenState() == mini3d::system::IWindow::SCREEN_STATE_WINDOWED)
                    window->SetScreenStateFullscreen();
                else
                    window->SetScreenStateWindowed();
            }

        break;
    }
}
