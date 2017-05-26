using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using Newtonsoft.Json;
using System.Net;
using Newtonsoft.Json.Linq;
using System.Runtime.InteropServices;
using System.Threading;

namespace GUI_App
{
    public partial class Form1 : Form
    {
        private IntPtr AppWinHandle;
        private Process p;
        public Form1()
        {
            InitializeComponent();
        }

        [DllImport("user32.dll")]
        static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);
        [DllImport("user32.dll")]
        static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);
        [DllImport("user32.dll")]
        static extern bool MoveWindow(IntPtr handle, int x, int y, int width, int height, bool redraw);
        private void button1_Click(object sender, EventArgs e)
        {
            const int GWL_STYLE = -16;
            const int WS_VISIBLE = 0x10000000;
            p = Process.Start("facescanDX_NoRS.exe");
            p.WaitForInputIdle();
            AppWinHandle = p.MainWindowHandle;
            SetParent(AppWinHandle, this.Handle);
            SetWindowLong(AppWinHandle, GWL_STYLE, WS_VISIBLE);
            MoveWindow(AppWinHandle, 300, 0, this.Width-300, this.Height, true);
        }
        protected override void OnResize(EventArgs e)
        {
            if (AppWinHandle != IntPtr.Zero)
            {
                MoveWindow(AppWinHandle, 300, 0, this.Width - 300, this.Height, true);
            }
            base.OnResize(e);
        }

        protected override void OnHandleDestroyed(EventArgs e)
        {
            // Stop the application
            if (AppWinHandle != IntPtr.Zero)
            {

                // Post a colse message
                p.Close();

                // Delay for it to get the message
                System.Threading.Thread.Sleep(1000);

                // Clear internal handle
                AppWinHandle = IntPtr.Zero;
            }

            base.OnHandleDestroyed(e);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            String url = "http://localhost:1310/api/glasses";
            var json = new WebClient().DownloadString(url);

            //MessageBox.Show(json.ToString());
            var g = JsonConvert.DeserializeObject<Rootobject>(json);
            //MessageBox.Show(g.List.Length.ToString());
        }


    }
}
