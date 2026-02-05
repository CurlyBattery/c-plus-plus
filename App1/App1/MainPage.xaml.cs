using System.Linq;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace App1
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            InitializeComponent();
            Button button3 = new Button();
            button3.Content = "Кнопка 3";
            button3.Width = 120;
            button3.Height = 40;
            button3.Margin = new Thickness(200, 0, 0, 0);
            button3.Background = new SolidColorBrush(Windows.UI.Colors.White);
            button3.Foreground = new SolidColorBrush(Windows.UI.Colors.Black);
            button3.FontFamily = new FontFamily("Verdana");
            layout.Children.Add(button3);
        }

        private void buttonClick(object sender, RoutedEventArgs e)
        {
            button1.Content = "успешно";
        }
    }
}
