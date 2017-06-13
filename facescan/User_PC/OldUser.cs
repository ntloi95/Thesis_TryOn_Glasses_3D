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
using System.Threading;

namespace User_PC
{
    public partial class OldUser : MaterialForm
    {
        [DllImport("user32.dll")]
        static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);
        [DllImport("user32.dll")]
        static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);
        [DllImport("user32.dll")]
        static extern bool MoveWindow(IntPtr handle, int x, int y, int width, int height, bool redraw);
        [DllImport("user32.dll")]
        static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

        private IntPtr ScanHandle;
        private Process ScanProcess;
        private IntPtr EditHandle;
        private Process EditProcess;

        public OldUser()
        {
            InitializeComponent();
            MaximizedBounds = Screen.FromHandle(this.Handle).WorkingArea;
            ScanHandle = IntPtr.Zero;
            EditHandle = IntPtr.Zero;
        }

        private void TextBoxPassword_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Enter)
            {
                TabControlOldUser.SelectedIndex++;
                btnBack.Visible = true;
            }
        }

        private void btnScanAgain_Click(object sender, EventArgs e)
        {
            TabControlOldUser.SelectedIndex = 2;
        }

        private void btnEditFace_Click(object sender, EventArgs e)
        {
            TabControlOldUser.SelectedIndex = 3;
        }

        private void btnEditInfor_Click(object sender, EventArgs e)
        {
            TabControlOldUser.SelectedIndex = 4;
        }

        private void OldUserForm_ClientSizeChanged(object sender, EventArgs e)
        {
            if (ScanHandle != IntPtr.Zero)
                MoveWindow(ScanHandle, TabControlOldUser.Left, TabControlOldUser.Top, TabControlOldUser.Width, TabControlOldUser.Height, true);
            if (EditHandle != IntPtr.Zero)
                MoveWindow(EditHandle, TabControlOldUser.Left, TabControlOldUser.Top, TabControlOldUser.Width, TabControlOldUser.Height, true);      
        }

        private void tabPageScan_Leave(object sender, EventArgs e)
        {
            if (ScanHandle != IntPtr.Zero)
            {
                ShowWindow(ScanHandle, 0);
            }
        }

        private void tabPageEdit_Leave(object sender, EventArgs e)
        {
            if(EditHandle != IntPtr.Zero)
            {
                ShowWindow(EditHandle, 0);
            }
        }

        private void tabPageScan_Enter(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Maximized;
            if (ScanHandle == IntPtr.Zero)
            {
                const int GWL_STYLE = -16;
                const int WS_VISIBLE = 0x10000000;
                ScanProcess = Process.Start(@"C:\Users\ThanhLoi\Desktop\Thesis\Github\Thesis_TryOn_Glasses_3D\facescan\bin\v120\x32\scan.exe");
                ScanProcess.WaitForInputIdle();
                ScanHandle = ScanProcess.MainWindowHandle;
                SetParent(ScanHandle, this.Handle);
                SetWindowLong(ScanHandle, GWL_STYLE, WS_VISIBLE);
                MoveWindow(ScanHandle, TabControlOldUser.Left, TabControlOldUser.Top, TabControlOldUser.Width, TabControlOldUser.Height, true);
            }
            else
            {
                const int SW_SHOW = 5;
                ShowWindow(ScanHandle, SW_SHOW);
            }
        }
        private void tabPageEdit_Enter(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Maximized;
            if (EditHandle == IntPtr.Zero)
            {
                /*EditProcess = new Process();
                ProcessStartInfo processInfor = new ProcessStartInfo();
                processInfor.FileName = @"C:\Users\ThanhLoi\Desktop\Thesis\Github\Thesis_TryOn_Glasses_3D\facescan\bin\v120\x32\edit.exe";
                EditProcess.StartInfo = processInfor;
                
                ThreadStart editStart = new ThreadStart(
                    () => EditProcess.Start()
                );
                Thread editThread = new Thread(editStart);
                editThread.IsBackground = true;
                editThread.Start();

                //Thread updateProgress = new Thread(UpdateProgressTask);
                //updateProgress.Start();

                while (!editThread.Join(0)) ;*/

                //progressLoad.Value = progressLoad.Maximum;

                const int GWL_STYLE = -16;
                const int WS_VISIBLE = 0x10000000;
                EditProcess = Process.Start(@"C:\Users\ThanhLoi\Desktop\Thesis\Github\Thesis_TryOn_Glasses_3D\facescan\bin\v120\x32\edit.exe");
                EditProcess.WaitForInputIdle();
                EditHandle = EditProcess.MainWindowHandle;
                SetParent(EditHandle, this.Handle);
                SetWindowLong(EditHandle, GWL_STYLE, WS_VISIBLE);
                MoveWindow(EditHandle, TabControlOldUser.Left, TabControlOldUser.Top, TabControlOldUser.Width, TabControlOldUser.Height, true);
            }
            else
            {
                const int SW_SHOW = 5;
                ShowWindow(EditHandle, SW_SHOW);
            }
        }

        private void UpdateProgressTask()
        {
            //int maxValue = progressLoad.Maximum;

            for (int i = 0; i < 98; i++)
            {
                //UpdateProgress(maxValue/100*i);
                Thread.Sleep(1);
            }
        }

        public void UpdateProgress(int i)
        {
            if (InvokeRequired)
            {
                this.BeginInvoke(new Action<int>(UpdateProgress), new object[] { i });
                return;
            }
            //progressLoad.Value = i;
        }

        private void TabPageInfor_Enter(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Normal;
        }

        private void btnBack_Click(object sender, EventArgs e)
        {
            TabControlOldUser.SelectedIndex = 1;
        }

        private void TabPageFunction_Enter(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Normal;
        }

        private void btnChangePassword_Click(object sender, EventArgs e)
        {
            TabControlOldUser.SelectedIndex = 5;
        }

        private void btnUpload_Click(object sender, EventArgs e)
        {

        }

        private void OldUser_FormClosed(object sender, FormClosedEventArgs e)
        {
            /*
            if (ScanHandle != IntPtr.Zero)
            {
                ScanProcess.Kill();
                ScanHandle = IntPtr.Zero;
            }
            if (EditHandle != IntPtr.Zero)
            {
                EditProcess.Kill();
                EditHandle = IntPtr.Zero;
            }*/
            Owner.Show();
        }
    }
}
