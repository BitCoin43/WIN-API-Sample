#include <atlimage.h>//обертки для HDC
#include <gdiplus.h>//GDI+ заголовочный файл
#pragma comment(lib,"gdiplus.lib")//GDI+ библиотека

using namespace Gdiplus;//использование пространства имен GDI+

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);//функция обработки сообщений окна
BOOL InitApplication(HINSTANCE hInstance);// функция для подготовки данных класса окна и его регистрации в ОС Windows
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);//первая вызываемая функция объекта theApp для создания окна 
void SetAlphaImage(HWND hWnd);//настройка и вывод изображения


HWND hWnd1;
HWND hWnd;

RECT rc;

HBITMAP mLoadImg(WCHAR* szFilename)
{
    HBITMAP result = NULL;

    Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(szFilename, false);
    bitmap->GetHBITMAP(NULL, &result);
    delete bitmap;
    return result;
}

void displayImage(HBITMAP mBmp, HWND mHwnd)
{
    RECT myRect; //расположение, высота, ширина прямоугольника
    BITMAP bm;//объект рисунка   
    HDC screenDC, memDC; //идентификатор контекста устройства   
    HBITMAP oldBmp; //битмап   
    BLENDFUNCTION bf; //Структура для управления плавным переходом цвета и тона, устанавливая функции сопряжения для источниковых и принимающих точечных рисунков    
    GetObject(mBmp, sizeof(bm), &bm);//получение информации о рисунке в буфер (bm)

    //исходная операция плавного перехода цвета и тона (исходный точечный рисунок помещается поверх принимающего точечного рисунка, бузирующегося на a - значениях источниковых пикселей)
    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;

    //устанавливает а-значение прозрачности, которое будет использоваться на всем источниковом точечном рисунке
    bf.SourceConstantAlpha = 0xff;

    //управляет способом, которым интерпретируются исходные и принимающие точечные рисунки .
    bf.AlphaFormat = AC_SRC_ALPHA;

    //извлекаем дескриптор созданного окна
    screenDC = GetDC(mHwnd);

    //получаем описывающий окно прямоугольник
    GetClientRect(mHwnd, &myRect);

    //Если рисунок пуст, закрашиваем все белой кистью
    if (mBmp == NULL)
        FillRect(screenDC, &myRect, WHITE_BRUSH);
    //иначе	
    else
    {
        //создадим контекст устройства в памяти (DC), совместимый с заданным устройством
        memDC = CreateCompatibleDC(screenDC);

        //выбор нашего рисунка
        oldBmp = (HBITMAP)SelectObject(memDC, mBmp);

        //показываем на экране точечные рисунки, с прозрачным или полупрозрачным фоном
        AlphaBlend(screenDC, 0, 0, myRect.right, myRect.bottom, memDC, 0, 0, bm.bmWidth, bm.bmHeight, bf);

        //возвращаем настройки и освобаждаем память
        SelectObject(memDC, oldBmp);
        DeleteDC(memDC);
        ReleaseDC(mHwnd, screenDC);
    }
}

int WINAPI WinMain(						//функция с которой начинается выполнение программы (точка входа)                
    HINSTANCE           hInstance,		//дискриптор данного приложения
    HINSTANCE           hPrevInstance,  //дискриптор предыдущей запущенной копии приложения
    LPSTR               lpCmdLine,      //указатель на командную строку (в IDE можно задать по команде Properties)                        
    int                 nCmdShow)      //режим начального отображения главного окна                          
{
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    if (!InitApplication(hInstance)) //Инициализируем приложение - подготавливаем данные класса окна и регистрируем его
        return FALSE;

    if (!InitInstance(hInstance, nCmdShow)) //Завершаем создание приложения, создаем и отображаем главное окно приложения
        return FALSE;

    MSG msg;									//Для дочернего сообщения

    while (GetMessage(&msg, NULL, 0, 0)/*прием сообщения из очереди сообщений приложения*/)	//стандартный цикл обработки сообщений
    {
        TranslateMessage(&msg);//сообщение передается данной функции. Она вызывает драйвер клавиатуры ОС Windows для преобразования виртуальных
        //кодов клавиш в ASCII-значения, которые ставятся в очередь программных событий в виде сообщения WM_CHAR
        DispatchMessage(&msg);//берет данные о сообщении и передает в соответствующую оконную процедуру для обработки
    }
    //этот цикл работает на всем протяжении работы программы 

    GdiplusShutdown(gdiplusToken);

    return static_cast<int>(msg.wParam);
}

//функция для подготовки данных класса окна и его регистрации в ОС Windows
BOOL InitApplication(HINSTANCE hInstance)
{
    //Сведения о регистрируемом классе
    WNDCLASS            wc;


    wc.style = CS_HREDRAW | CS_VREDRAW;//свойства окна
    wc.lpfnWndProc = static_cast<WNDPROC>(WndProc);//адрес функции окна, которая обрабатывает сообщения для окон данного класса
    wc.cbClsExtra = 0;//количество байт для хранения доп информации
    wc.cbWndExtra = 0;//количество байт для хранения доп информации
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_ASTERISK); //загрузка иконки приложния
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);//загрузка курсора
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);//загрузка фона рабочего стола
    wc.lpszMenuName = NULL;//загрузка меню (NULL - отсутствует)
    wc.lpszClassName = L"WndBtnAPI";//Указатель на строку имени класса (должно быть уникальным)

    return RegisterClass(&wc);//регистрируем класс
}

//создаем окно
BOOL InitInstance(
    HINSTANCE           hInstance,
    int                 nCmdShow)
{

    hWnd = CreateWindowEx(
        WS_EX_LAYERED,//слоистое окно поддерживающее альфа прозрачность отдельных пикселей
        //WS_EX_OVERLAPPEDWINDOW,
        L"WndBtnAPI", //имя класса
        L"Title", //заголовок окна
        WS_OVERLAPPEDWINDOW,//перекрывающееся окно
        CW_USEDEFAULT, //X -координата
        //0,
        0,			   //Y - координата
        CW_USEDEFAULT, //ширина окна
        0,//высота окна
        NULL,		   //дескриптор родительского окна
        NULL,		   //дескриптор меню окна
        hInstance,     //дескриптор экземпляра приложения
        NULL);         //указатель на дополнительные данные окна (их нет)

    //Функции для вывода окон
    if (ShowWindow(hWnd, nCmdShow))
        return FALSE;

    if (!UpdateWindow(hWnd))
        return FALSE;

    SetAlphaImage(hWnd);

    return TRUE;
}

//Функция для обработки сообщений
LRESULT CALLBACK WndProc(           // Возвращает результат
    //   обработки сообщения,
    //   зависящий от посланного
    //   сообщения: 0 - успех
    HWND                hwnd,       // Дескриптор созданного окна
    UINT                message,    // Номер сообщения
    WPARAM              wParam,     // Дополнительная информация о 
    LPARAM              lParam)    //   сообщении, зависящая от
    //   типа сообщения (wParam,
    //   lParam)
{
    PAINTSTRUCT pt;
    HDC hDC;
    static HBITMAP myImage;
    switch (message)
    {
    case WM_CREATE://создание окна

        break;
    case WM_NCHITTEST://Нажимается или отпускается кнопка мыши
        return HTCAPTION;
        break;

    case WM_DESTROY://уничтожение окна
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);//обработка по умолчанию

    }

    return 0;
}


void SetAlphaImage(HWND hWnd)
{
    // Load our PNG image
    CImage img;//объект для поддержки растровых изображений
    HRESULT hr = img.Load(L"templates/test.png");//загружаем рисунок из папки с иходными текстами программы
    if (FAILED(hr))//Если есть ошибки то возвращаем управление
        return;
    //Get dimensions
    int iWidth = img.GetWidth();//фиксируем ширину картинки
    int iHeight = img.GetHeight();//фиксируем высоту картинки
    // Make mem DC + mem  bitmap
    HDC hdcScreen = GetDC(NULL);//получим дескриптор устройства для всего экрана
    HDC hDC = CreateCompatibleDC(hdcScreen);//создадим контекст устройства в памяти (DC), совместимый с заданным устройством

    HBITMAP hBmp = CreateCompatibleBitmap(hdcScreen, iWidth, iHeight);//создадим точечный рисунок, совместимый с утсройством, которое связано с заданным контекстом устройства
    HBITMAP hBmpOld = (HBITMAP)SelectObject(hDC, hBmp);//выбираем объект в заданный контекст устройства (DC)

    // Рисуем изображение в контексте утсройства
    // Обрабатываем каждый пиксель (настраиваем альфу)
    for (int i = 0; i < img.GetWidth(); i++)
    {
        for (int j = 0; j < img.GetHeight(); j++)
        {
            BYTE* ptr = (BYTE*)img.GetPixelAddress(i, j);
            ptr[0] = ((ptr[0] * ptr[3]) + 127) / 255;
            ptr[1] = ((ptr[1] * ptr[3]) + 127) / 255;
            ptr[2] = ((ptr[2] * ptr[3]) + 127) / 255;
        }
    }

    //показываем на экране точечные рисунки, которые имеют прозрачные или полупрозрачные пиксели
    img.AlphaBlend(hDC, 0, 0, iWidth, iHeight, 0, 0, iWidth, iHeight);
    BLENDFUNCTION blend = { 0 };
    blend.BlendOp = AC_SRC_OVER;
    blend.SourceConstantAlpha = 255;
    blend.AlphaFormat = AC_SRC_ALPHA;

    POINT ptPos = { 0, 0 };

    SIZE sizeWnd = { iWidth, iHeight };

    POINT ptSrc = { 0, 0 };

    HWND hDT = GetDesktopWindow();

    if (hDT)
    {
        RECT rcDT;

        GetWindowRect(hDT, &rcDT);
        //находим середину по горизонтали и вертикали
        ptPos.x = (rcDT.right - iWidth) / 2;
        ptPos.y = (rcDT.bottom - iHeight) / 2;
    }

    //модифицируем свойства многослойного окна
    UpdateLayeredWindow(hWnd, hdcScreen, &ptPos, &sizeWnd, hDC, &ptSrc, 0, &blend, ULW_ALPHA);

    //возврат к прдыдущим настройкам и освобождение памяти
    SelectObject(hDC, hBmpOld);
    DeleteObject(hBmp);
    DeleteDC(hDC);
    ReleaseDC(NULL, hdcScreen);
}