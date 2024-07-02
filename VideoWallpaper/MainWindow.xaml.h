#pragma once

#include "MainWindow.g.h"

namespace muxc
{
    using namespace winrt::Microsoft::UI::Xaml::Controls;
};

namespace winrt::VideoWallpaper::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            //using namespace winrt;
            //using namespace Microsoft::UI::Xaml;
            //auto window = this->try_as<Window>();
            //window.SetTitleBar(AppTitleBar());
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
        double NavigationViewControlCompactModeThresholdWidth();
        void ContentFrame_NavigationFailed(
            Windows::Foundation::IInspectable const& /* sender */,
            Microsoft::UI::Xaml::Navigation::NavigationFailedEventArgs const& args);
        void NavigationViewControl_Loaded(
            Windows::Foundation::IInspectable const& /* sender */,
            Microsoft::UI::Xaml::RoutedEventArgs const& /* args */);
        void NavigationViewControl_ItemInvoked(
            Windows::Foundation::IInspectable const& /* sender */,
            muxc::NavigationViewItemInvokedEventArgs const& args);

        // NavigationViewControl_SelectionChanged is not used in this example, but is shown for completeness.
        // You'll typically handle either ItemInvoked or SelectionChanged to perform navigation,
        // but not both.
        void NavigationViewControl_SelectionChanged(
            muxc::NavigationView const& /* sender */,
            muxc::NavigationViewSelectionChangedEventArgs const& args);
        void NavigationViewControl_Navigate(
            Windows::UI::Xaml::Interop::TypeName navPageType,
            Microsoft::UI::Xaml::Media::Animation::NavigationTransitionInfo const& transitionInfo);
        void NavigationViewControl_BackRequested(
            muxc::NavigationView const& /* sender */,
            muxc::NavigationViewBackRequestedEventArgs const& /* args */);
        void On_Navigated(
            Windows::Foundation::IInspectable const& /* sender */,
            Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& args);
        bool TryGoBack();
    };
}

namespace winrt::VideoWallpaper::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
