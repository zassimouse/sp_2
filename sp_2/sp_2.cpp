// sp_2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "sp_2.h"

#define MAX_LOADSTRING 100
#define MAX_BUFFERSTRING 3000


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

INT numOfColumns = 4;
INT numOfRows = 3;
WCHAR strCellText[MAX_BUFFERSTRING];

// Functions
VOID DrawTable(HWND hWnd, RECT wndRect);
VOID DrawLine(HDC hdc, COLORREF color, int x1, int y1, int x2, int y2);
VOID DrawVerticalTableLines(HDC hdc, COLORREF color, INT cellSizeX, INT tableSizeY);


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SP2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SP2));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SP2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    //wcex.hbrBackground = CreateSolidBrush(RGB(80, 110, 78));

    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SP2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: // создание окна, вызывается ещё до его отрисовки
    {
      



        const TCHAR szFileName[] = L"text1.txt"; // File with the text

        // Создаём дискриптор файла (число, с помощью которого можно идентифицировать объект)
        // параметры: имя файла, режим доступа, совместный доступ, дескр. защиты, действие, атрибуты файла, дескр. шаблона файла
        HANDLE hFile = CreateFile(szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (INVALID_HANDLE_VALUE == hFile) // если дескриптор не был создан
        {
            MessageBox(hWnd, L"File not found!", L"Error", MB_OK); // выводим сообщение об ошибке
        }
        else // если же всё хорошо
        {
            MessageBox(hWnd, L"Success!", L"Good", MB_OK); // выводим сообщение об ошибке

            DWORD dwByte;
            // параметры: дескриптор файла на чтение, буфер для записи, число байтов для чтение, число прочитанных байтов, асинхронный буфер
            ReadFile(hFile, strCellText, MAX_BUFFERSTRING, &dwByte, NULL); // читаем файл
            //strCellText[MAX_BUFFERSTRING - 150] = 0; // признак конца строки

            CloseHandle(hFile); // закрываем дескриптор
        }
    } 
    break;
 
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...

            COLORREF colorText = RGB(255, 255, 255), // цвет текста
                colorBack = RGB(66, 135, 245),   // цвет заднего фона
                colorLine = RGB(66, 135, 245);  // цвет линий таблицы

          

            HFONT newFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Helvetica"));
            SetTextColor(hdc, RGB(0, 0, 0));
            SelectObject(hdc, newFont);

            RECT wndRect;                       // размеры окна
            GetClientRect(hWnd, &wndRect);      // получаем размер и записываем его в переменную

            INT offset = 10;                     // offset from text to all 4 sides
            INT colWidth = wndRect.right / numOfColumns;
              
            // Calculate the height of text
            RECT rect = {offset, offset, colWidth - offset, 500};
            int height = DrawText(hdc, strCellText, -1, &rect, DT_WORDBREAK | DT_EDITCONTROL | DT_BOTTOM);
            rect.bottom = height + offset;
         
            for (int i = 0; i < numOfRows; i++)
            {
                for (int j = 0; j < numOfColumns; j++)
                {

                    int height = DrawText(hdc, strCellText, -1, &rect, DT_WORDBREAK | DT_EDITCONTROL | DT_BOTTOM);
                    OffsetRect(&rect, colWidth, 0);
                    DrawLine(hdc, colorLine, 0, rect.bottom + offset, wndRect.right, rect.bottom + offset); // рисуем горизонтальную линию

                }

                OffsetRect(&rect, -numOfColumns * colWidth, height + offset * 2);
            }

            DrawVerticalTableLines(hdc, colorLine, colWidth, (height + offset * 2) * numOfRows ); // рисуем вертикальную линию

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}




// Рисуем горизонтальную линию
VOID DrawLine(HDC hdc, COLORREF color, int x1, int y1, int x2, int y2)
{
    // содзаём перо, параметры: стиль пера (сплошной), толщина пера, цвет пера
    HPEN pen = CreatePen(PS_INSIDEFRAME, 3, color);
    POINT pt;
    SelectObject(hdc, pen); // выбираем в качестве объекта контекст изображения 
    MoveToEx(hdc, x1, y1, &pt);  // обновляем позицию текущей точки
    LineTo(hdc, x2, y2); // соединяем текущую точку с новой
    DeleteObject(pen); // удаляем перо
}

// рисуем вертикальную линию
VOID DrawVerticalTableLines(HDC hdc, COLORREF color, INT cellSizeX, INT tableSizeY)
{
    for (int i = 1; i < numOfColumns; i++)
    {
        DrawLine(hdc, color, i * cellSizeX, 0, i * cellSizeX, tableSizeY);
    }
}
