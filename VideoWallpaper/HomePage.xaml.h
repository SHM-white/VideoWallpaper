#pragma once

#include "HomePage.g.h"

namespace winrt::VideoWallpaper::implementation
{
    struct HomePage : HomePageT<HomePage>
    {
        HomePage()
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
    struct HomePage : HomePageT<HomePage, implementation::HomePage>
    {
    };
}