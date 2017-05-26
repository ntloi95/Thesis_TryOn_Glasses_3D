using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MaterialSkin.Animations;
using MaterialSkin.Controls;
using MaterialSkin;
using MetroFramework;
using System.Runtime.InteropServices;
using System.Threading;
using System.Diagnostics;

namespace GUI_App
{
    public partial class Form2 : MaterialForm
    {
        private IntPtr AppWinHandle;
        private Process p;

        public Form2()
        {
            InitializeComponent();

            MaterialSkinManager skinManager = MaterialSkinManager.Instance;
            skinManager.AddFormToManage(this);
            skinManager.Theme = MaterialSkinManager.Themes.DARK;
        }

        [DllImport("user32.dll")]
        static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);
        [DllImport("user32.dll")]
        static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);
        [DllImport("user32.dll")]
        static extern bool MoveWindow(IntPtr handle, int x, int y, int width, int height, bool redraw);
        [DllImport("user32.dll")]
        static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

        protected override void OnHandleDestroyed(EventArgs e)
        {
            if (AppWinHandle != IntPtr.Zero)
            {
                p.Kill();
                AppWinHandle = IntPtr.Zero;
            }
            base.OnHandleDestroyed(e);
        }

        private void Form2_ClientSizeChanged(object sender, EventArgs e)
        {
            if (AppWinHandle != IntPtr.Zero)
                MoveWindow(AppWinHandle, TabControl.Left, TabControl.Top + introductionScanner.Bottom, TabControl.Width, TabControl.Height - introductionScanner.Bottom, true);
        }

        private void tabPageScanner_Leave(object sender, EventArgs e)
        {
            if (AppWinHandle != IntPtr.Zero)
            {
                ShowWindow(AppWinHandle, 0);
            }
        }

        private void tabPageScanner_Enter(object sender, EventArgs e)
        {
            if(AppWinHandle == IntPtr.Zero)
            {
                const int GWL_STYLE = -16;
                const int WS_VISIBLE = 0x10000000;
                p = Process.Start("notepad");
                p.WaitForInputIdle();
                AppWinHandle = p.MainWindowHandle;
                SetParent(AppWinHandle, this.Handle);
                SetWindowLong(AppWinHandle, GWL_STYLE, WS_VISIBLE);
                MoveWindow(AppWinHandle, TabControl.Left, TabControl.Top + introductionScanner.Bottom, TabControl.Width, TabControl.Height - introductionScanner.Bottom, true);
            }
            else
            {
                const int SW_SHOW = 5;
                ShowWindow(AppWinHandle, SW_SHOW);
            }
        }

        private void materialSingleLineTextField3_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && (e.KeyChar != '.'))
                e.Handled = true;

            if ((e.KeyChar == '.') && ((sender as TextBox).Text.IndexOf('.') > -1))
                e.Handled = true;
            materialSingleLineTextField3.Text = materialSingleLineTextField3.Text; 
        }
    }
}
