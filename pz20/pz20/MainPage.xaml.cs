using System;
using System.Threading;
using System.Threading.Tasks;
using Windows.UI.Core;
using Windows.UI.Xaml.Controls;

namespace pz20
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a <see cref="Frame">.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private static SemaphoreSlim semaphore = new SemaphoreSlim(4, 4);

        public MainPage()
        {
            InitializeComponent();
            StartSimulation();
        }

        private async void StartSimulation()
        {
            for (int i = 0; i <= 10; i++)
            {
                int carId = i;
                _ = Task.Run(() => CarRefuel(carId));
                await Task.Delay(500);
            }
        }

        private async Task CarRefuel(int carId)
        {
            await LogMessage($"Машина {carId} подъехала к заправке\n");

            await semaphore.WaitAsync();

            await LogMessage($"Машина {carId} начала заправку\n");
            await Task.Delay(2000);
            await LogMessage($"Машина {carId} закончила заправку\n");

            semaphore.Release();
        }

        private async Task LogMessage(string message)
        {
            await Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
            {
                outputTextBlock.Text += message + "\n";
            });
        }
    } 
}
