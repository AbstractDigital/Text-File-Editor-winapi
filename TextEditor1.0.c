#include <windows.h>
// Defines the menu identifiers
#define FILE_NEWTITLE 1
#define HELP 2
#define FILE_EXIT 3
#define FILE_SAVE_JPEG 4
#define FILE_SAVE_PNG 5
#define Ch

LRESULT CALLBACK WindowsProcedure(HWND, UINT, WPARAM, LPARAM) ;     /*/ Declares the WindowsProcedure function before reference /*/

void AddMenus(HWND) ;       /*/Declares the add menu function /*/
HMENU hMenu;        // creates menu handler variable of the type HMENU
HWND hEdit;
void AddControls(HWND) ;        //Declares the add control function



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR args, int ncmdshow)       /*/ Windows API entry point /*/
{
    /*/ creates a windows class named WindowsClass /*/
    WNDCLASSW WindowsClass = {0} ;
    WindowsClass.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    WindowsClass.hCursor = LoadCursor(NULL, IDC_CROSS) ;
    WindowsClass.hInstance = hInst ;
    WindowsClass.lpszClassName = L"WindowsClass" ;
    WindowsClass.lpfnWndProc = WindowsProcedure ;

    
    if(!RegisterClassW(&WindowsClass)){return -1;}    /*/ registers the class, in case of failure, the program will quit with an error /*/

    
    /*/ creates a window from the windows class /*/ 
    CreateWindowW(L"WindowsClass", L"TextFile Editor 1.0.0 ", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL); //main windows therefore there is no parent window, left NULL

    
    /*/ windows procedure loop /*/
    MSG msg = {0};    /*/ defines message variable(assigned zero to initiate) /*/
    while( GetMessage(&msg, NULL, NULL, NULL) )
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

}


/*/ defines WindowsProcedure /*/  
LRESULT CALLBACK WindowsProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) 
{
    wchar_t text[100];      //text array containing the text
    
    switch (msg)
    {
    case WM_COMMAND:    // this msg is sent when a menu item is clicked, the menu item ID is gotten from wp
        
        switch(wp)      //uses switch to identify the menu item pressed using the ID from wp
        {
            case FILE_NEWTITLE:         //reads the text from the edit control, then replaces the title
                GetWindowTextW(hEdit, text, 100); //get the text in text var from hEdit, which is the edit control handler 
                SetWindowTextW(hWnd, text);         //sets the new title
                break ;
            case FILE_EXIT:
                DestroyWindow(hWnd);
                break;
            case FILE_SAVE_JPEG:
                break;
            case FILE_SAVE_PNG:
                break;
        }
        break;
    
    
    
    case WM_CREATE:     //creates a menu when the window is created
        AddMenus(hWnd);
        AddControls(hWnd);
        break;

    case WM_DESTROY:    // ends the getmsg loop when the window is destroyed
        PostQuitMessage(0);
        break;
    
    default:           //handles default msg
        DefWindowProcW(hWnd,msg,wp,lp);
        break;
    }
}




/*/ defines AddMenus function /*/
void AddMenus(HWND hWnd)
{
    HMENU hSaveMenu = CreateMenu();
    AppendMenu(hSaveMenu, MF_STRING, FILE_SAVE_JPEG, "Save as .txt");
    AppendMenu(hSaveMenu, MF_STRING, FILE_SAVE_PNG, "Save as RTXT");


    HMENU hFileMenu = CreateMenu();     //creates a menu handler for drop down menu and assigns it a new menu.
    AppendMenu(hFileMenu, MF_STRING, FILE_NEWTITLE, "Change Title");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSaveMenu, "Save");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_EXIT, "Exit");



    hMenu = CreateMenu(); //assigns a new menu to the menu handler variable
    //Add 2 items to the hMenu bar created above.
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File") ;
    AppendMenu(hMenu, MF_STRING, HELP, "Help") ; 

    SetMenu(hWnd, hMenu);      //sets the menu to the main windows
}



// defines control function
void AddControls(HWND hWnd)  //Controls will be created with the createwindow function as they are childs of the parent window, we need to define the parent window
{                   // however as the classes for the controls are predefined in windows.h, we don't need to create another class for it. We need the parent window handler in this function, like the menu function
    
    /*/ creates a static control /*/
    CreateWindowW(L"static", L"TextFile Editor - Untitled.txt", WS_VISIBLE | WS_CHILD | ES_CENTER, 0,0, 500,20, hWnd,NULL,NULL,NULL); /*/the predefined class for static controls is "static", 
    2nd arg is the text contained in the controll, 3rd - style, 4th & 5th arg - x,y The window is 500x500, so our coord will be on a 500x500 plane, 6th parent/*/
    hEdit = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 0, 20, 480, 500, hWnd,NULL, NULL, NULL ); //sets hEdit as a handler

}