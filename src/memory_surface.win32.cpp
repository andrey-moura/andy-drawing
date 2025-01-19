#include <uva/drawing.hpp>

#include <uva/drawing/win32.hpp>

#define m_bitmap os_specific_data_as<memory_surface_data>().bitmap

uva::drawing::memory_surface::memory_surface(const uva::size& s)
    : surface(s)
{
    HBITMAP bitmap = CreateCompatibleBitmap(GetDC(nullptr), s.w, s.h);

    if (bitmap == nullptr)
    {
        throw std::runtime_error("Failed to create bitmap");
    }

    m_bitmap = bitmap;
}

uva::drawing::memory_surface::~memory_surface()
{
    DeleteObject(os_specific_data_as<memory_surface_data>().bitmap);
}

bool uva::drawing::memory_surface::write_to_file(std::filesystem::path &path, std::string_view stem)
{
    path /= stem;
    path.replace_extension(".bmp");

    HDC hDC;
    int iBits;
    WORD wBitCount;
    DWORD dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
    BITMAP Bitmap0;
    BITMAPFILEHEADER bmfHdr;
    BITMAPINFOHEADER bi;
    LPBITMAPINFOHEADER lpbi;
    HANDLE fh, hDib, hPal, hOldPal2 = NULL;
    hDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
    iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
    DeleteDC(hDC);
    if (iBits <= 1)
        wBitCount = 1;
    else if (iBits <= 4)
        wBitCount = 4;
    else if (iBits <= 8)
        wBitCount = 8;
    else
        wBitCount = 24;
    GetObject(m_bitmap, sizeof(Bitmap0), (LPSTR)&Bitmap0);
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = Bitmap0.bmWidth;
    bi.biHeight = -Bitmap0.bmHeight;
    bi.biPlanes = 1;
    bi.biBitCount = wBitCount;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrImportant = 0;
    bi.biClrUsed = 256;
    dwBmBitsSize = ((Bitmap0.bmWidth * wBitCount + 31) & ~31) / 8
        * Bitmap0.bmHeight;
    hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
    *lpbi = bi;

    hPal = GetStockObject(DEFAULT_PALETTE);
    if (hPal)
    {
        hDC = GetDC(NULL);
        hOldPal2 = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
        RealizePalette(hDC);
    }

    GetDIBits(hDC, m_bitmap, 0, (UINT)Bitmap0.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)
        + dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);

    if (hOldPal2)
    {
        SelectPalette(hDC, (HPALETTE)hOldPal2, TRUE);
        RealizePalette(hDC);
        ReleaseDC(NULL, hDC);
    }

    fh = CreateFile(path.string().c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

    if (fh == INVALID_HANDLE_VALUE)
        return FALSE;

    bmfHdr.bfType = 0x4D42; // "BM"
    dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
    bmfHdr.bfSize = dwDIBSize;
    bmfHdr.bfReserved1 = 0;
    bmfHdr.bfReserved2 = 0;
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

    WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

    WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
    GlobalUnlock(hDib);
    GlobalFree(hDib);
    CloseHandle(fh);
    return TRUE;
}

uva::drawing::image uva::drawing::memory_surface::to_image()
{
    // Get pixels of the HBITMAP in m_bitmap

    BITMAPINFO info;
    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biWidth = width();
    info.bmiHeader.biHeight = height();
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    info.bmiHeader.biSizeImage = 0;
    info.bmiHeader.biXPelsPerMeter = 0;
    info.bmiHeader.biYPelsPerMeter = 0;
    info.bmiHeader.biClrUsed = 0;
    info.bmiHeader.biClrImportant = 0;

    uva::drawing::image img(size());

    uva::color* pixels = img.pixels();

    GetDIBits(GetDC(nullptr), m_bitmap, 0, height(), pixels, &info, DIB_RGB_COLORS);

    for(size_t i = 0; i < size().w * size().h; i++)
    {
        char r = pixels[i].r;
        char b = pixels[i].b;

        pixels[i].r = b;
        pixels[i].b = r;

        // Workaround for the fact that the alpha channel is not set by GetDIBits
        // TODO: We have to fix this
        pixels[i].a = 255;
    }

    return img;
}