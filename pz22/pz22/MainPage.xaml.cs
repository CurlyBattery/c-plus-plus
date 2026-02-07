using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace pz22
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a <see cref="Frame">.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            InitializeComponent();
        }

        private void UpdateTotal(object sender, RoutedEventArgs e) {
            int total = 0;

            if (chkEspresso.IsChecked == true) total += 150;
            if (chkCappuccino.IsChecked == true) total += 200;
            if (chkLatte.IsChecked == true) total += 220;

            if (chkCroisant.IsChecked == true) total += 120;
            if (chkBrownie.IsChecked == true) total += 180;

            if ((rbMedium != null) && rbMedium.IsChecked == true) total += 50;
            if ((rbLarge != null) && rbLarge.IsChecked == true) total += 100;

            if(txtTotal != null) txtTotal.Text = $"{total} р";


        }
    }
}
