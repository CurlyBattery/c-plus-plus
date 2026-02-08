using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace pz26
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            InitializeComponent();
        }

        private void GoToPage2(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(BlankPage1), "Переход с главной страницы");
        }

        private void GoToPage3(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(BlankPage2));
        }
    }
}
