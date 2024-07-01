#pragma once

#include "About.g.h"

namespace winrt::VideoWallpaper::implementation
{
    struct About : AboutT<About>
    {
        About()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::VideoWallpaper::factory_implementation
{
    struct About : AboutT<About, implementation::About>
    {
    };
}