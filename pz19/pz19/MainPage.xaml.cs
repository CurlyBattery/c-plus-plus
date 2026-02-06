using Windows.UI.ViewManagement;
using Windows.UI.Xaml.Controls;
using Windows.Foundation;
using Windows.UI.Xaml;
using System.Linq;
using System;

namespace pz19
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

        private void onClickOne(object sender, RoutedEventArgs e)
        {
            boxInput.Text += "1";
        }

        private void onClickTwo(object sender, RoutedEventArgs e)
        {
            boxInput.Text += "2";
        }

        private void onClickThree(object sender, RoutedEventArgs e)
        {
            boxInput.Text += "3";
        }

        private void onClickFour(object sender, RoutedEventArgs e)
        {
            boxInput.Text += "4";
        }

        private void onClickFive(object sender, RoutedEventArgs e)
        {
            boxInput.Text += "5";
        }

        private void onClickSix(object sender, RoutedEventArgs e)
        {
            boxInput.Text += "6";
        }

        private void onClickSeven(object sender, RoutedEventArgs e)
        {
            boxInput.Text += "7";
        }

        private void onClickEight(object sender, RoutedEventArgs e)
        {
            boxInput.Text += "8";
        }

        private void onClickNine(object sender, RoutedEventArgs e)
        {
            boxInput.Text += "9";
        }

        private void onClickZero(object sender, RoutedEventArgs e)
        {
            boxInput.Text += "0";
        }

        private void onClickPlus(object sender, RoutedEventArgs e)
        {
            boxInput.Text += "+";
        }

        private void onClickMultiply(object sender, RoutedEventArgs e)
        {
            boxInput.Text += "*";
        }

        private void onClickMinus(object sender, RoutedEventArgs e)
        {
            boxInput.Text += "-";
        }

        private void onClickDivide(object sender, RoutedEventArgs e)
        {
            boxInput.Text += "/";
        }

        private void onClickResult(object sender, RoutedEventArgs e)
        {
            char operation = ' ';

            for (int i = 0; i < boxInput.Text.Length; i++)
            {
                if (boxInput.Text[i] == '+' || boxInput.Text[i] == '*' || boxInput.Text[i] == '-' || boxInput.Text[i] == '/')
                {
                    operation = boxInput.Text[i];
                }
            }

            string[] numsArr = boxInput.Text.Split(operation);
            double num1 = double.Parse(numsArr[0]);
            double num2 = double.Parse(numsArr[1]);

            switch (operation)
            {
                case '+':
                    boxInput.Text = $"{num1+num2}";
                    break;
                case '8':
                    boxInput.Text = $"{num1*num2}";
                    break;
                case '-':
                    boxInput.Text = $"{num1-num2}";
                    break;
                case '/':
                    boxInput.Text = $"{num1/num2}";
                    break;
                default:
                    boxInput.Text = $"{0}";
                    break;
            }
        }

        private void onClickPow(object sender, RoutedEventArgs e)
        {
            double num = double.Parse(boxInput.Text);

            boxInput.Text = Math.Pow(num, 2).ToString();
        }

        private void onClickSqrt(object sender, RoutedEventArgs e)
        {
            double num = double.Parse(boxInput.Text);

            boxInput.Text = Math.Sqrt(num).ToString();
        }
    }
}
