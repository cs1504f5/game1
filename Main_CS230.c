// ---------------------------------------------------------------------------
// Project Name		:	Simple Demo
// File Name		:	Main.cpp
// Author			:	Antoine Abi Chacra
// Creation Date	:	2012/01/11
// Purpose			:	main entry point2 for the test program
// History			:
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"

// ---------------------------------------------------------------------------

// Libraries
#pragma comment (lib, "Alpha_Engine.lib")

// ---------------------------------------------------------------------------
// globals

int gGameRunning = 1;

// ---------------------------------------------------------------------------
// Static function protoypes


// ---------------------------------------------------------------------------


LRESULT CALLBACK MyWinCallBack(HWND hWin, UINT msg, WPARAM wp, LPARAM lp);


// ---------------------------------------------------------------------------
// main


int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	// Variable declaration	
	unsigned char colors[16];				// 2x2 image
	float obj1X = 0.0f, obj1Y = 0.0f;		// Position variables for object 1
	float obj1texX = 0, obj1texY = 0;		// Texture variables for object 2's texture
	AEGfxVertexList*	pMesh1;				// Pointer to Mesh (Model)
	AEGfxVertexList*	pMesh2;				// Pointer to Mesh (Model)
	AEGfxVertexList*	pMeshLine;			// Pointer to Mesh (Model)
	AEGfxTexture *pTex1;					// Pointer to Texture (Image)
	AEGfxTexture *pTex2;					// Pointer to Texture (Image)
	float camX, camY;						// Used to temporary store camera position
	float alpha = 1.0f;
	WNDCLASS	winClass;
	HWND winHandle;
	RECT rect;

	// Initialize the system 
	AESysInitInfo sysInitInfo;

	sysInitInfo.mAppInstance		= instanceH;
	sysInitInfo.mShow				= show;
	sysInitInfo.mWinWidth			= 800; 
	sysInitInfo.mWinHeight			= 600;
	sysInitInfo.mCreateConsole		= 1;
	sysInitInfo.mMaxFrameRate		= 60;
	sysInitInfo.mpWinCallBack		= NULL;//MyWinCallBack;
	sysInitInfo.mClassStyle			= CS_HREDRAW | CS_VREDRAW;											
	sysInitInfo.mWindowStyle		= WS_OVERLAPPEDWINDOW;//WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	
	winClass.style			= sysInitInfo.mClassStyle;
	winClass.lpfnWndProc	= MyWinCallBack;//(pSysInitInfo->mpWinCallBack) ? pSysInitInfo->mpWinCallBack : winCallBack;
	winClass.cbClsExtra		= 0;
	winClass.cbWndExtra		= 0;
	winClass.hInstance		= sysInitInfo.mAppInstance;
	winClass.hIcon			= LoadIcon(NULL,IDI_EXCLAMATION);
	winClass.hCursor		= LoadCursor(NULL,IDC_ARROW);
	winClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winClass.lpszMenuName	= NULL;
	winClass.lpszClassName	= "Window Class Name";

	RegisterClass(&winClass);

	rect.left = 0;
	rect.top = 0;
	rect.right = sysInitInfo.mWinWidth;//WinWidth;
	rect.bottom = sysInitInfo.mWinHeight;//WinHeight;

	AdjustWindowRect(&rect, sysInitInfo.mWindowStyle, 0);

	winHandle = CreateWindow(winClass.lpszClassName, "GAME", sysInitInfo.mWindowStyle, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, sysInitInfo.mAppInstance, NULL);

	ShowWindow	(winHandle, show);
	UpdateWindow(winHandle);


	sysInitInfo.mCreateWindow		= 0;
	sysInitInfo.mWindowHandle		= winHandle;

	if(0 == AESysInit (&sysInitInfo))
		printf("System Init Failed!\n");

	// reset the system modules
	AESysReset();

	
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// 1 triangle at a time
	// X, Y, Color, texU, texV
	AEGfxTriAdd(
		-25.5f, -25.5f, 0xFFFF0000, 0.0f, 0.0f, 
		25.5f,  0.0f, 0xFFFF0000, 0.0f, 0.0f,
		-25.5f,  25.5f, 0xFFFF0000, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh1
	pMesh1 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh1, "Failed to create mesh 1!!");


	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// This shape has 2 triangles
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f, 
		30.0f,  -30.0f, 0x00FFFF00, 1.0f, 1.0f,
		-30.0f,  30.0f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		30.0f, -30.0f, 0x00FFFFFF, 1.0f, 1.0f, 
		30.0f,  30.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-30.0f,  30.0f, 0x00FFFFFF, 0.0f, 0.0f);

	pMesh2 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh2, "Failed to create mesh 2!!");

		
	// Informing the library that we're about to start adding vertices
	AEGfxMeshStart();

	// This shape has 5 vertices

	AEGfxVertexAdd(0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(100.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(200.0f, 150.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(300.0f, -100.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(100.0f, -250.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	pMeshLine = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMeshLine, "Failed to create mesh 2!!");



	// Texture 1: From file
	pTex1 = AEGfxTextureLoad("1.png");
	AE_ASSERT_MESG(pTex1, "Failed to create texture1!!");

	// Texture 2: From memory
	// RGBA format
	colors[0] = 255;	colors[1] = 0;		colors[2] = 0;		colors[3] = 255;
	colors[4] = 0;		colors[5] = 255;	colors[6] = 0;		colors[7] = 255;
	colors[8] = 0;		colors[9] = 0;		colors[10] = 255;	colors[11] = 255;	
	colors[12] = 255;	colors[13] = 255;	colors[14] = 255;	colors[15] = 255;				

	pTex2 = AEGfxTextureLoadFromMemory(colors, 2, 2);
	// This step is optional, it creates a file from the texture argument
	AE_ASSERT_MESG(pTex2, "Failed to create texture2!!");

	
	AEGfxSetBackgroundColor(255.0f, 255.0f, 255.0f);
	
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);   // Alpha等等，向学生演示不同模式的效果

	int n = 0;
	// Game Loop
	while(gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		
		// Object Control
		if (AEInputCheckCurr(VK_UP))
			obj1Y += 3.0f;
		else
		if (AEInputCheckCurr(VK_DOWN))
			obj1Y -= 3.0f;

		if (AEInputCheckCurr(VK_LEFT))
		{
			obj1X -= 3.0f;
			if(n!=-50) n--;
		}
		else
			if (AEInputCheckCurr(VK_RIGHT))
			{
				obj1X += 3.0f;
				if (n != 50) n++;
			}
		// Alpha value
		if (AEInputCheckCurr('Z'))
			alpha -= 0.01f;
		else
		if (AEInputCheckCurr('X'))
			alpha += 0.01f;

		alpha = AEClamp(alpha, 0.0f, 1.0f);


		// Blending mode
		if (AEInputCheckCurr('1'))
			AEGfxSetBlendMode(AE_GFX_BM_NONE);
		else
		if (AEInputCheckCurr('2'))
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		else
		if (AEInputCheckCurr('3'))
			AEGfxSetBlendMode(AE_GFX_BM_ADD);
		else
		if (AEInputCheckCurr('4'))
			AEGfxSetBlendMode(AE_GFX_BM_MULTIPLY);

		if (n == 50||n==-50)
		{
			// Move the camera
			AEGfxGetCamPosition(&camX, &camY);
			if (AEInputCheckCurr(VK_UP))
				AEGfxSetCamPosition(camX, camY + 3);
			else
				if (AEInputCheckCurr(VK_DOWN))
					AEGfxSetCamPosition(camX, camY - 3);

			AEGfxGetCamPosition(&camX, &camY);
			if (AEInputCheckCurr(VK_LEFT))
				AEGfxSetCamPosition(camX - 3, camY);
			else
				if (AEInputCheckCurr(VK_RIGHT))
					AEGfxSetCamPosition(camX + 3, camY);
		}
		// Texture offset  texture rect 左上（0，0），修改前面的mesh2定义，演示只加载一半纹理的情况
		if (AEInputCheckCurr('L'))
			obj1texX += 0.01f;
		else
		if (AEInputCheckCurr('J'))
			obj1texX -= 0.01f;

		if (AEInputCheckCurr('I'))
			obj1texY += 0.01f;
		else
		if (AEInputCheckCurr('K'))
			obj1texY -= 0.01f;

		/*AEGfxSetRenderMode(AE_GFX_RM_COLOR);             //线条
		AEGfxSetPosition(200.0f,-100.0f);
		AEGfxLine		(0, 0, 0, 1.0f, 1.0f, 1.0f, 1.0, 
								200, 200, 200, 1.0, 1.0, 1.0, 1.0);
*/
		//AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		//AEGfxSetPosition(0.0f, 0.0f);
		//AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		//AEGfxMeshDraw(pMeshLine, AE_GFX_MDM_LINES_STRIP);
/*
		// Drawing object 1
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set position for object 1
		AEGfxSetPosition(obj1X, obj1Y);
		// No texture for object 1
		AEGfxTextureSet(pTex1, 0, 0);
		// Drawing the mesh (list of triangles)
		AEGfxSetTransparency(alpha);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);
*/

		// Drawing object 2
		// Set position for object 2
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);   // 必须最先设置绘制模式为纹理
		AEGfxSetPosition(obj1X, obj1Y);
		// Set texture for object 2
		AEGfxTextureSet(pTex1, 0, 0);
		AEGfxSetTransparency(alpha);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);

	
		// Drawing object 2 again
		// Set position for object 2
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(-100.0f, -60.0f);
		// Set texture for object 2
		AEGfxTextureSet(pTex2, 0.0f, 0.0f);
		AEGfxSetTransparency(1.0f);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);


/*
		// Drawing object 2 again and again
		// Set poisition for object 2
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(100.0f, 100.0f);
		// Set texture for object 2
		AEGfxTextureSet(pTex1, obj1texX, obj1texY);
		AEGfxSetTransparency(1.0f);
		AEGfxSetBlendColor(0.5f, 0.0f, 0.0, 0.75f);
		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);
*/
		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(VK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	// Freeing the objects and textures
	AEGfxMeshFree(pMesh1);
	AEGfxMeshFree(pMesh2);
	AEGfxMeshFree(pMeshLine);
	
	AEGfxTextureUnload(pTex1);
	AEGfxTextureUnload(pTex2);


	// free the system
	AESysExit();

	return 1;
}

// ---------------------------------------------------------------------------


LRESULT CALLBACK MyWinCallBack(HWND hWin, UINT msg, WPARAM wp, LPARAM lp) 
{
	HDC dc;   
	PAINTSTRUCT ps;

	switch (msg)
	{
	// when the window is created
	case WM_CREATE:
		printf("My own code in window create message!\n");
		break;

	// when the rectangle is drawn
	case WM_PAINT:
		dc = BeginPaint(hWin, &ps);

		// Cleans up the painting process
		EndPaint(hWin, &ps);
		break;

	// When it's time for the window to go away
	case WM_DESTROY:
		//PostQuitMessage(0);
		//gAESysWinExists = false;
		break;

	// called any time the window is moved
	case WM_MOVE:
		// Invalidate the rect to force a redraw
		InvalidateRect(hWin, NULL, FALSE);
		break;

	case WM_ACTIVATE:
		// DO NOT REMOVE THIS
		// *(AESysGetAppActive()) = (LOWORD(wp) == WA_INACTIVE) ? 0 : 1;
		break;

	default:
		return DefWindowProc(hWin, msg, wp, lp);
	}

	return 0;
}