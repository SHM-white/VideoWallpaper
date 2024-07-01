#include "pch.h"
#include "EditWallpapers.xaml.h"
#if __has_include("EditWallpapers.g.cpp")
#include "EditWallpapers.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::VideoWallpaper::implementation
{
    int32_t EditWallpapers::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void EditWallpapers::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void EditWallpapers::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
