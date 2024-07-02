#include "pch.h"
#include "MainWindow.xaml.h"
#include "App.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::VideoWallpaper::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    double MainWindow::NavigationViewControlCompactModeThresholdWidth()
    {
        return NavigationViewControl().CompactModeThresholdWidth();
    }

    void MainWindow::ContentFrame_NavigationFailed(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Navigation::NavigationFailedEventArgs const& args)
    {
        throw winrt::hresult_error(
            E_FAIL, winrt::hstring(L"Failed to load Page ") + args.SourcePageType().Name);
    }

    void MainWindow::NavigationViewControl_Loaded(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        // Add handler for ContentFrame navigation.
        ContentFrame().Navigated({ this, &MainWindow::On_Navigated });

        // NavigationViewControl doesn't load any page by default, so load home page.
        NavigationViewControl().SelectedItem(NavigationViewControl().MenuItems().GetAt(0));
        // If navigation occurs on SelectionChanged, then this isn't needed.
        // Because we use ItemInvoked to navigate, we need to call Navigate
        // here to load the home page.
        NavigationViewControl_Navigate(winrt::xaml_typename<VideoWallpaper::HomePage>(),
            Microsoft::UI::Xaml::Media::Animation::EntranceNavigationTransitionInfo());
    }

    void MainWindow::NavigationViewControl_ItemInvoked(Windows::Foundation::IInspectable const&, muxc::NavigationViewItemInvokedEventArgs const& args)
    {
        if (args.IsSettingsInvoked())
        {
            NavigationViewControl_Navigate(winrt::xaml_typename<VideoWallpaper::Settings>(),
                args.RecommendedNavigationTransitionInfo());
        }
        else if (args.InvokedItemContainer())
        {
            Windows::UI::Xaml::Interop::TypeName pageTypeName;
            pageTypeName.Name = unbox_value<hstring>(args.InvokedItemContainer().Tag());
            pageTypeName.Kind = Windows::UI::Xaml::Interop::TypeKind::Primitive;
            NavigationViewControl_Navigate(pageTypeName, args.RecommendedNavigationTransitionInfo());
        }
    }

    void MainWindow::NavigationViewControl_SelectionChanged(muxc::NavigationView const&, muxc::NavigationViewSelectionChangedEventArgs const& args)
    {
        if (args.IsSettingsSelected())
        {
            NavigationViewControl_Navigate(winrt::xaml_typename<VideoWallpaper::Settings>(),
                args.RecommendedNavigationTransitionInfo());
        }
        else if (args.SelectedItemContainer())
        {
            Windows::UI::Xaml::Interop::TypeName pageTypeName;
            pageTypeName.Name = unbox_value<hstring>(args.SelectedItemContainer().Tag());
            pageTypeName.Kind = Windows::UI::Xaml::Interop::TypeKind::Primitive;
            NavigationViewControl_Navigate(pageTypeName, args.RecommendedNavigationTransitionInfo());
        }
    }

    void MainWindow::NavigationViewControl_Navigate(Windows::UI::Xaml::Interop::TypeName navPageType, Microsoft::UI::Xaml::Media::Animation::NavigationTransitionInfo const& transitionInfo)
    {
        Windows::UI::Xaml::Interop::TypeName preNavPageType =
            ContentFrame().CurrentSourcePageType();

        // Navigate only if the selected page isn't currently loaded.
        if (navPageType.Name != L"" && preNavPageType.Name != navPageType.Name)
        {
            ContentFrame().Navigate(navPageType, nullptr, transitionInfo);
        }
    }

    void MainWindow::NavigationViewControl_BackRequested(muxc::NavigationView const&, muxc::NavigationViewBackRequestedEventArgs const&)
    {
        TryGoBack();
    }

    void MainWindow::On_Navigated(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& args)
    {
        NavigationViewControl().IsBackEnabled(ContentFrame().CanGoBack());

        if (ContentFrame().SourcePageType().Name ==
            winrt::xaml_typename<VideoWallpaper::Settings>().Name)
        {
            // SettingsItem is not part of NavigationViewControl.MenuItems, and doesn't have a Tag.
            NavigationViewControl().SelectedItem(NavigationViewControl().SettingsItem().as<muxc::NavigationViewItem>());
            NavigationViewControl().Header(winrt::box_value(L"Settings"));
        }
        else if (ContentFrame().SourcePageType().Name != L"")
        {
            for (auto&& eachMenuItem : NavigationViewControl().MenuItems())
            {
                auto navigationViewItem =
                    eachMenuItem.try_as<muxc::NavigationViewItem>();
                {
                    if (navigationViewItem)
                    {
                        winrt::hstring hstringValue =
                            winrt::unbox_value_or<winrt::hstring>(
                                navigationViewItem.Tag(), L"");
                        if (hstringValue == ContentFrame().SourcePageType().Name)
                        {
                            NavigationViewControl().SelectedItem(navigationViewItem);
                            NavigationViewControl().Header(navigationViewItem.Content());
                        }
                    }
                }
            }
        }

    }

    bool MainWindow::TryGoBack()
    {
        if (!ContentFrame().CanGoBack())
            return false;
        // Don't go back if the nav pane is overlayed.
        if (NavigationViewControl().IsPaneOpen() &&
            (NavigationViewControl().DisplayMode() == muxc::NavigationViewDisplayMode::Compact ||
                NavigationViewControl().DisplayMode() == muxc::NavigationViewDisplayMode::Minimal))
            return false;
        ContentFrame().GoBack();
        return true;
    }

}
