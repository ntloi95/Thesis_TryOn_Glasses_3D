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
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace User_PC
{
     
    public partial class NewUser : MaterialForm
    {
        [DllImport("user32.dll")]
        static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);
        [DllImport("user32.dll")]
        static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);
        [DllImport("user32.dll")]
        static extern bool MoveWindow(IntPtr handle, int x, int y, int width, int height, bool redraw);
        [DllImport("user32.dll")]
        static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

        private IntPtr ExeHandle;
        private Process ExeProcess;

        public NewUser()
        {
            InitializeComponent();
            MaximizedBounds = Screen.FromHandle(this.Handle).WorkingArea;
        }

        private void NewUser_Load(object sender, EventArgs e)
        {

        }

        private void btnNext_Click(object sender, EventArgs e)
        {
            if (TabControlNewUser.SelectedIndex < TabControlNewUser.TabCount - 1)
            {
                TabControlNewUser.SelectedIndex++;
                progressBarRegister.Value = TabControlNewUser.SelectedIndex * progressBarRegister.Maximum / 3;
            }
            else
            {
                progressBarRegister.Value = progressBarRegister.Maximum;
                TabControlNewUser.Visible = false;
                DialogResult isOK = MessageBox.Show("Excellent! You finished completely register. \nFrom now, you can use our mobile devices to try on Glasses or use this app to edit or scan again your face",
                    "Congratulations", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                if(isOK == DialogResult.OK)
                {
                    Owner.Show();
                    Close();
                }
            }
               
        }

        private void btnBack_Click(object sender, EventArgs e)
        {
            if(TabControlNewUser.SelectedIndex > 0)
                TabControlNewUser.SelectedIndex--;
            progressBarRegister.Value = TabControlNewUser.SelectedIndex*progressBarRegister.Maximum / 3;
        }

        private void btnTakePhoto_Click(object sender, EventArgs e)
        {

        }

        protected override void OnHandleDestroyed(EventArgs e)
        {
            if (ExeHandle != IntPtr.Zero)
            {
                ExeProcess.Kill();
                ExeHandle = IntPtr.Zero;
            }
            base.OnHandleDestroyed(e);
        }

        private void NewUserForm_ClientSizeChanged(object sender, EventArgs e)
        {
            if (ExeHandle != IntPtr.Zero)
                MoveWindow(ExeHandle, TabControlNewUser.Left, TabControlNewUser.Top, TabControlNewUser.Width, TabControlNewUser.Height, true);
        }

        private void tabPageScanner_Leave(object sender, EventArgs e)
        {
            if (ExeHandle != IntPtr.Zero)
            {
                ShowWindow(ExeHandle, 0);
            }
        }

        private void tabPageScanner_Enter(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Maximized;
            if (ExeHandle == IntPtr.Zero)
            {
                const int GWL_STYLE = -16;
                const int WS_VISIBLE = 0x10000000;
                ExeProcess = Process.Start(@"C:\Users\ThanhLoi\Desktop\Thesis\Github\Thesis_TryOn_Glasses_3D\facescan\bin\v120\x32\scan.exe");
                ExeProcess.WaitForInputIdle();
                ExeHandle = ExeProcess.MainWindowHandle;
                SetParent(ExeHandle, this.Handle);
                SetWindowLong(ExeHandle, GWL_STYLE, WS_VISIBLE);
                MoveWindow(ExeHandle, TabControlNewUser.Left, TabControlNewUser.Top, TabControlNewUser.Width, TabControlNewUser.Height, true);
            }
            else
            {
                const int SW_SHOW = 5;
                ShowWindow(ExeHandle, SW_SHOW);
            }
        }

        private void NewUser_FormClosed(object sender, FormClosedEventArgs e)
        {
            Owner.Show();
        }
    }
}
