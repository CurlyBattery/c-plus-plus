using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;

namespace pz24
{
    public sealed partial class MainPage : Page
    {
        private List<Bookmark> bookmarks = new List<Bookmark>();

        public MainPage()
        {
            InitializeComponent();
            LoadDefaultBookMarks();

            NavigateToUrl("https://www.microsoft.com");
        }

        private class Bookmark
        {
            public string Title { get; set; }
            public string Url { get; set; }
        }

        private void LoadDefaultBookMarks()
        {
            bookmarks.Add(new Bookmark { Title = "Microsoft", Url = "https://www.microsoft.com" });
            bookmarks.Add(new Bookmark { Title = "GitHub", Url = "https://github.com" });
            bookmarks.Add(new Bookmark { Title = "Stack Overflow", Url = "https://stackoverflow.com" });

            UpdateBookmarksMenu();
        }

        private void UpdateBookmarksMenu()
        {
            while (bookmarksFloyout.Items.Count > 2)
            {
                bookmarksFloyout.Items.RemoveAt(2);
            }

            foreach (var bookmark in bookmarks)
            {
                MenuFlyoutItem item = new MenuFlyoutItem
                {
                    Text = bookmark.Title,
                    Tag = bookmark.Url
                };
                item.Click += BookmarkItemClick;
                bookmarksFloyout.Items.Add(item);
            }
        }

        private void BookmarkItemClick(object sender, RoutedEventArgs e)
        {
            MenuFlyoutItem item = sender as MenuFlyoutItem;
            if (item != null && item.Tag != null)
            {
                string url = item.Tag.ToString();
                txtUrl.Text = url;
                NavigateToUrl(url);
            }
        }

        private async void AddBookmark_Click(object sender, RoutedEventArgs e)
        {
            string currentUrl = txtUrl.Text;

            if (string.IsNullOrWhiteSpace(currentUrl))
            {
                await ShowMessage("Ошибка", "Сначала откройте страницу");
                return;
            }

            if (bookmarks.Exists(b => b.Url == currentUrl))
            {
                await ShowMessage("Информация", "Эта страница уже в закладках");
                return;
            }

            TextBox nameInput = new TextBox
            {
                PlaceholderText = "Название закладки",
                Text = webView.DocumentTitle ?? currentUrl
            };

            ContentDialog dialog = new ContentDialog
            {
                Title = "Добавить в закладки",
                Content = nameInput,
                PrimaryButtonText = "Добавить",
                CloseButtonText = "Отмена"
            };

            var result = await dialog.ShowAsync();

            if (result == ContentDialogResult.Primary)
            {
                string title = string.IsNullOrWhiteSpace(nameInput.Text)
                    ? currentUrl
                    : nameInput.Text;

                bookmarks.Add(new Bookmark { Title = title, Url = currentUrl });
                UpdateBookmarksMenu();

                await ShowMessage("Успех", "Закладка добавлена!");
            }
        }

        private void btnGo_Click(object sender, RoutedEventArgs e)
        {
            NavigateToUrl(txtUrl.Text);
        }

        private void txtUrl_KeyDown(object sender, KeyRoutedEventArgs e)
        {
            if (e.Key == Windows.System.VirtualKey.Enter)
            {
                NavigateToUrl(txtUrl.Text);
            }
        }

        private void NavigateToUrl(string url)
        {
            if (string.IsNullOrWhiteSpace(url))
                return;

            if (!url.StartsWith("http://") && !url.StartsWith("https://"))
            {
                url = "https://" + url;
            }

            try
            {
                Uri uri = new Uri(url);
                webView.Navigate(uri);
            }
            catch (Exception ex)
            {
                ShowMessage("Ошибка", "Неверный URL: " + ex.Message);
            }
        }

        private void btnBack_Click(object sender, RoutedEventArgs e)
        {
            if (webView.CanGoBack)
            {
                webView.GoBack();
            }
        }

        private void btnForward_Click(object sender, RoutedEventArgs e)
        {
            if (webView.CanGoForward)
            {
                webView.GoForward();
            }
        }

        private void webView_NavigationStarting(WebView sender, WebViewNavigationStartingEventArgs args)
        {
            if (progressBar != null)
            {
                progressBar.Visibility = Visibility.Visible;
            }

            if (txtUrl != null)
            {
                txtUrl.Text = args.Uri?.ToString() ?? txtUrl.Text;
            }
        }

        private void webView_ContentLoading(WebView sender, WebViewContentLoadingEventArgs args)
        {
        }

        private void webView_NavigationCompleted(WebView sender, WebViewNavigationCompletedEventArgs args)
        {
            if (progressBar != null)
            {
                progressBar.Visibility = Visibility.Collapsed;
            }

            if (args.IsSuccess)
            {
                if (txtUrl != null)
                {
                    txtUrl.Text = args.Uri?.ToString() ?? txtUrl.Text;
                }

                if (btnBack != null)
                {
                    btnBack.IsEnabled = webView.CanGoBack;
                }

                if (btnForward != null)
                {
                    btnForward.IsEnabled = webView.CanGoForward;
                }
            }
            else
            {
                ShowMessage("Ошибка загрузки", "Не удалось загрузить страницу");
            }
        }

        private async Task ShowMessage(string title, string message)
        {
            MessageDialog dialog = new MessageDialog(message, title);
            await dialog.ShowAsync();
        }
    }
}
