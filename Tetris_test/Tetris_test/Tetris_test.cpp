 #include "stdafx.h" #include "Tetris_test.h" #include "Jeu.h" #include "Draw.h" #include <iostream> using namespace std;  #define MAX_LOADSTRING 100 #define ECR_LARGEUR 10 #define ECR_HAUTEUR 20 #define Pixel_Bloc 25   #define VIT 33       #define TEMPS_ID 0  // Global Variables: HINSTANCE hInst;                                // current instance WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name HWND hWnd;  // Forward declarations of functions included in this code module: ATOM                MyRegisterClass(HINSTANCE hInstance); BOOL                InitInstance(HINSTANCE, int); LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM); INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);  int APIENTRY wWinMain(_In_ HINSTANCE hInstance,                      _In_opt_ HINSTANCE hPrevInstance,                      _In_ LPWSTR    lpCmdLine,                      _In_ int       nCmdShow) {     UNREFERENCED_PARAMETER(hPrevInstance);     UNREFERENCED_PARAMETER(lpCmdLine);      // TODO: Place code here.      // Initialize global strings     LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);     LoadStringW(hInstance, IDC_TETRISTEST, szWindowClass, MAX_LOADSTRING);     MyRegisterClass(hInstance);      // Perform application initialization:     if (!InitInstance (hInstance, nCmdShow))     {         return FALSE;     }      HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TETRISTEST));      MSG msg;      // Main message loop:     while (GetMessage(&msg, nullptr, 0, 0))     {         if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))         {             TranslateMessage(&msg);             DispatchMessage(&msg);         }     }      return (int) msg.wParam; }    // //  FUNCTION: MyRegisterClass() // //  PURPOSE: Registers the window class. // ATOM MyRegisterClass(HINSTANCE hInstance) {     WNDCLASSEXW wcex;      wcex.cbSize = sizeof(WNDCLASSEX);      wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;     wcex.lpfnWndProc    = WndProc;     wcex.cbClsExtra     = 0;     wcex.cbWndExtra     = 0;     wcex.hInstance      = hInstance;     wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));     wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);     wcex.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);     wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TETRISTEST);     wcex.lpszClassName  = szWindowClass;     wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));      return RegisterClassExW(&wcex); }  // //   FUNCTION: InitInstance(HINSTANCE, int) // //   PURPOSE: Saves instance handle and creates main window // //   COMMENTS: // //        In this function, we save the instance handle in a global variable and //        create and display the main program window. // BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {    hInst = hInstance; // Store instance handle in our global variable     hWnd = CreateWindowW(szWindowClass,  							 TEXT("Tetris game"),  							 WS_MINIMIZEBOX | WS_SYSMENU, 							 CW_USEDEFAULT, CW_USEDEFAULT, 							 (ECR_LARGEUR * Pixel_Bloc + 156)*2, 							 (ECR_HAUTEUR * Pixel_Bloc + 25),  							 nullptr, nullptr, hInstance, nullptr);     if (!hWnd)    {       return FALSE;    }     ShowWindow(hWnd, nCmdShow);    UpdateWindow(hWnd);     return TRUE; }  // //  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM) // //  PURPOSE:  Processes messages for the main window. // //  WM_COMMAND  - process the application menu //  WM_PAINT    - Paint the main window //  WM_DESTROY  - post a quit message and return // //  INT_PTR CALLBACK ChangerMode(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);  LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { 	HDC hdc; 	PAINTSTRUCT ps; 	static Jeu *jeu; 	static Dessiner *dess; 	switch (message) 	{ 	case WM_CREATE: 		hdc = GetDC(hWnd); 		dess = new Dessiner(hdc, hWnd, Pixel_Bloc); 		jeu = new Jeu(*dess); 		ReleaseDC(hWnd, hdc); 		break; 	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_MODE_JOUER:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, ChangerMode);
			break;
		}
	} 	case WM_KEYDOWN: 		jeu->toucher(wParam); 		break; 	case WM_TIMER: 		jeu->MAJTemps(); 		break; 	case WM_KILLFOCUS: 		KillTimer(hWnd, TEMPS_ID); 		jeu->pause(true); 		break; 	case WM_SETFOCUS: 		SetTimer(hWnd, TEMPS_ID, VIT, NULL); 		break; 	case WM_PAINT: 		hdc = BeginPaint(hWnd, &ps); 		jeu->rePeindre(); 		EndPaint(hWnd, &ps); 		break; 	case WM_DESTROY: 		delete dess; 		delete jeu; 		KillTimer(hWnd, TEMPS_ID); 		PostQuitMessage(0); 		break; 	} 	return DefWindowProc(hWnd, message, wParam, lParam); }   INT_PTR CALLBACK ChangerMode(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			if (SendDlgItemMessage(hDlg, IDC_RADIO1, BM_GETCHECK, 1, 0) == 1)
				MessageBox(hWnd, L"Mono Joueur", L"Annonce", MB_OK);
			if (SendDlgItemMessage(hDlg, IDC_RADIO2, BM_GETCHECK, 1, 0) == 1)
				MessageBox(hWnd, L"Multi Joueur", L"Annonce", MB_OK);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}