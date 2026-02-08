using System;
using System.Threading.Tasks;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Storage;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

namespace pz25
{
    /// <summary>
    /// Provides application-specific behavior to supplement the default <see cref="Application"/> class.
    /// </summary>
    public sealed partial class App : Application
    {
        /// <summary>
        /// Initializes the singleton application object. This is the first line of authored code
        /// executed, and as such is the logical equivalent of main() or WinMain().
        /// </summary>
        public App()
        {
            InitializeComponent();

            Suspending += OnSuspending;
            Resuming += OnResuming;
        }

        /// <inheritdoc/>
        protected override async void OnLaunched(LaunchActivatedEventArgs e)
        {

            string message = $"Запуск приложения\nПредыдущее состояние: {e.PreviousExecutionState}";
            await ShowMessageAsync("OnLaunched", message);

            if (Window.Current.Content is not Frame rootFrame)
            {
                rootFrame = new Frame();
                rootFrame.NavigationFailed += OnNavigationFailed;


                if (e.PreviousExecutionState == ApplicationExecutionState.Terminated)
                {
                    await ShowMessageAsync("Восстановление", "Приложение было завершено системой.\nЗагружаем сохраненные данные...");
                    await LoadStateAsync();
                }
                else if (e.PreviousExecutionState == ApplicationExecutionState.ClosedByUser)
                {
                    await ShowMessageAsync("Повторный запуск", "Приложение было закрыто пользователем");
                }
                else if (e.PreviousExecutionState == ApplicationExecutionState.NotRunning)
                {
                    await ShowMessageAsync("Первый запуск", "Приложение запускается впервые");
                }

                Window.Current.Content = rootFrame;
            }

            if (e.PrelaunchActivated == false)
            {
                if (rootFrame.Content == null)
                {
                    rootFrame.Navigate(typeof(MainPage), e.Arguments);
                }

                Window.Current.Activate();
            }
        }

        protected override async void OnActivated(IActivatedEventArgs args)
        {
            await ShowMessageAsync("OnActivated", $"Приложение активировано\nПредыдущее состояние: {args.PreviousExecutionState}");
            base.OnActivated(args);
        }


        private void OnNavigationFailed(object sender, NavigationFailedEventArgs e)
        {
            throw new Exception($"Failed to load page '{e.SourcePageType.FullName}'.");
        }

        private async void OnSuspending(object sender, SuspendingEventArgs e)
        {
            SuspendingDeferral deferral = e.SuspendingOperation.GetDeferral();
            await ShowMessageAsync("OnSuspending", "Приложение восстанавливается\n");

            await SaveStateAsync();
          
            deferral.Complete();
        }

        private async void OnResuming(object sender, object e) {
            await ShowMessageAsync("OnResuming", "Приложение возобновляет работу\n");
        }

        private async Task SaveStateAsync()
        {
            ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
            localSettings.Values["LastSuspendTime"] = DateTime.Now.ToString();
            localSettings.Values["AppData"] = "Важные данные приложения";


        }

        private async System.Threading.Tasks.Task LoadStateAsync()
        {
            ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
            if (localSettings.Values.ContainsKey("LastSuspendTime"))
            {
                string lastTime = localSettings.Values["LastSuspendTime"].ToString();
                string data = localSettings.Values["AppData"]?.ToString() ?? "нет данных";

                await ShowMessageAsync("Данные восстановлены",
                    $"Последняя приостановка: {lastTime}\nДанные: {data}");
            }
        }

        private async Task ShowMessageAsync(string title, string message)
        {
            MessageDialog dialog = new MessageDialog(message, title);
            await dialog.ShowAsync();

        }
    }
}
