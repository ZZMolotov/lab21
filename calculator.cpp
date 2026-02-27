#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

HWND hEdit1, hEdit2, hResult, hText;
HWND Add, Subtract, Multiply, Divide;
void CreateControl(HWND);
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE:{	
			CreateControl(hwnd);
			break;
		}
		case WM_COMMAND:{
			if(LOWORD(wParam) >= 1 && LOWORD(wParam) <= 4){
				char str1[100],str2[100],strResult[100];
				double n1,n2,res = 0;

				GetWindowText(hEdit1, str1,100);
				GetWindowText(hEdit2, str2,100);
				n1 = atof(str1);
				n2 = atof(str2);
				switch(LOWORD(wParam)){
					case 1: res = n1 + n2; break;
					case 2: res = n1 - n2; break;
					case 3: res = n1 * n2; break;
					case 4:
						if(n2 != 0) {
							res = n1 / n2;
						}else{
							MessageBox(hwnd, "Can't Divide by Zero.", "Error", MB_OK | MB_ICONERROR);
							return 0;
						}
						break;
			}
			sprintf(strResult, "%f", res);
			MessageBox(hwnd, strResult, "Result", MB_OK);
		}
		break;
	}
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
void CreateControl(HWND hwnd){
	hText = CreateWindowA("STATIC", "Please Input two Numbers",
	WS_VISIBLE | WS_CHILD | SS_CENTER,
	25,20,200,25, hwnd, NULL, NULL, NULL);

	hEdit1 = CreateWindowA("EDIT", "",
	WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
	45,50,150,25, hwnd, NULL, NULL, NULL);

	hEdit2 = CreateWindowA("EDIT", "",
	WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
	45,85,150,25, hwnd, NULL, NULL, NULL);

	Add = CreateWindowA("BUTTON", "+", WS_VISIBLE | WS_CHILD, 60, 130, 30, 25, hwnd, (HMENU)1, NULL, NULL);
    Subtract = CreateWindowA("BUTTON", "-", WS_VISIBLE | WS_CHILD, 95, 130, 30, 25, hwnd, (HMENU)2, NULL, NULL);
    Multiply = CreateWindowA("BUTTON", "*", WS_VISIBLE | WS_CHILD, 130, 130, 30, 25, hwnd, (HMENU)3, NULL, NULL);
    Divide = CreateWindowA("BUTTON", "/", WS_VISIBLE | WS_CHILD, 165, 130, 30, 25, hwnd, (HMENU)4, NULL, NULL);
}