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
using User_PC;
using System.Net;
using Newtonsoft.Json;
using System.IO;
using System.Threading;

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

        private IntPtr ScanHandle;
        private Process ScanProcess;

        Image avatar;
        User CurrentUser;
        WebCam webcam;

        public NewUser()
        {
            InitializeComponent();
            MaximizedBounds = Screen.FromHandle(this.Handle).WorkingArea;
            CurrentUser = new User();
            webcam = new WebCam();
        }

        private void NewUser_Load(object sender, EventArgs e)
        {
            
        }

        void FinishedSignIn()
        {
            TabControlNewUser.Visible = false;
            DialogResult isOK = MessageBox.Show("Excellent! You finished completely register. You can use tablet to continue",
                "Congratulations", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
            if (isOK == DialogResult.OK)
            {
                Owner.Show();
                Close();
            }
            btnBack.Visible = true;
        }
        private void btnNext_Click(object sender, EventArgs e)
        {
            switch(TabControlNewUser.SelectedIndex)
            {
                case 0:
                    {
                        if (!checkPage0Infor())
                        {
                            labelNotification.ForeColor = Color.FromArgb(255, 0, 0);
                            labelNotification.Text = "Email and Full name is required";
                            return;
                        }

                        try
                        {
                            WebRequest request = WebRequest.Create(Utilities.ServerHost + "/api/user");
                            request.Method = "POST";

                            User user = new User();
                            user.Address = txtBoxAddress.Text;
                            user.Discription = "";
                            user.Email = txtBoxEmail.Text;
                            user.Gender = (btnFemale.Checked ? "F" : "M");
                            user.Name = txtBoxName.Text;

                            string postData = JsonConvert.SerializeObject(user);
                            byte[] byteArray = Encoding.UTF8.GetBytes(postData);
                            request.ContentType = "application/json";
                            Stream dataStream = request.GetRequestStream();
                            dataStream.Write(byteArray, 0, byteArray.Length);
                            dataStream.Close();
                            WebResponse response = request.GetResponse();
                            if (((HttpWebResponse)response).StatusCode == HttpStatusCode.Created)
                            {
                                labelNotification.ForeColor = Color.FromArgb(0, 200, 0);
                                labelNotification.Text = "Information register is valid!";

                                //Parse Message get CurrentUser
                                using (var sr = new StreamReader(response.GetResponseStream()))
                                {
                                    string json = sr.ReadToEnd();
                                    CurrentUser = JsonConvert.DeserializeObject<User>(json);
                                }
                            }
                        }

                        catch (Exception ex)
                        {
                            MessageBox.Show(ex.ToString(), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            labelNotification.ForeColor = Color.FromArgb(255, 0, 0);
                            labelNotification.Text = "Information register is invalid!";
                        }

                        break;
                    }
                case 1:
                    {
                        if (!checkPage1Infor())
                        {
                            labelNotification.ForeColor = Color.FromArgb(255, 0, 0);
                            labelNotification.Text = "Information is not valid";
                            if (avatar == null || labelNotification.Text.Length == 0)
                                MessageBox.Show("You have to set password and avatar", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                            return;
                        }

                        try
                        {
                            WebRequest request = WebRequest.Create(Utilities.ServerHost + "/api/updatepassword?email=" + txtBoxEmail.Text);
                            request.Method = "PUT";

                            User user = new User();
                            user.Password = txtBoxPassword1.Text;
                            if (avatar == null)
                                MessageBox.Show("You have not set avatar for log in by face", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            else
                                using (var ms = new MemoryStream())
                                {
                                    avatar.Save(ms, System.Drawing.Imaging.ImageFormat.Jpeg);
                                    user.Avatar = Convert.ToBase64String(ms.ToArray());
                                }

                            string postData = JsonConvert.SerializeObject(user);
                            byte[] byteArray = Encoding.UTF8.GetBytes(postData);
                            request.ContentType = "application/json";
                            Stream dataStream = request.GetRequestStream();
                            dataStream.Write(byteArray, 0, byteArray.Length);
                            dataStream.Close();
                            WebResponse response = request.GetResponse();
                            if (((HttpWebResponse)response).StatusCode == HttpStatusCode.OK)
                            {
                                labelNotification.ForeColor = Color.FromArgb(0, 200, 0);
                                labelNotification.Text = "Information register is valid!";
                            }
                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show(ex.ToString(), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            labelNotification.ForeColor = Color.FromArgb(255, 0, 0);
                            labelNotification.Text = "Information register is invalid!";
                        }

                        break;
                    }
                case 2:
                    {
                        this.WindowState = FormWindowState.Maximized;
                        btnBack.Visible = false;
                        btnNext.Visible = false;
                        break;
                    }

                case 3:
                    {
                        FinishedSignIn();
                        return;
                    }
            }

            TabControlNewUser.SelectedIndex += 1;     
        }

        private void btnBack_Click(object sender, EventArgs e)
        {
            if(TabControlNewUser.SelectedIndex > 0)
                TabControlNewUser.SelectedIndex--;
        }

        private void btnTakePhoto_Click(object sender, EventArgs e)
        {
            webcam.Stop();
            avatar = pictureBoxFace.Image;

            btnTakePhoto.Visible = false;
            btnTryAgain.Visible = true;
            
        }

        protected override void OnHandleDestroyed(EventArgs e)
        {
            if (ScanHandle != IntPtr.Zero)
            {
                ScanProcess.Kill();
                ScanHandle = IntPtr.Zero;
            }
            base.OnHandleDestroyed(e);
        }

        private void NewUserForm_ClientSizeChanged(object sender, EventArgs e)
        {
            if (ScanHandle != IntPtr.Zero)
                MoveWindow(ScanHandle, TabControlNewUser.Left, TabControlNewUser.Top, TabControlNewUser.Width, TabControlNewUser.Height, true);
        }

        private void tabPageScanner_Leave(object sender, EventArgs e)
        {
            if (ScanHandle != IntPtr.Zero)
            {
                ShowWindow(ScanHandle, 0);
            }
        }

        private void tabPageScanner_Enter(object sender, EventArgs e)
        {
            const int GWL_STYLE = -16;
            const int WS_VISIBLE = 0x10000000;

            FormWindowState oldState = WindowState;
            this.WindowState = FormWindowState.Maximized;

            //Write data for read right profile of currentUser.
            System.IO.StreamWriter file = new System.IO.StreamWriter(Utilities.CurrentUserID);
            file.Write(CurrentUser.Id);
            file.Close();

            Thread thread = new Thread(() =>
            {
                progressLoadScan.Visible = true;

                ProcessStartInfo inforStart = new ProcessStartInfo(Utilities.PathScan);
                inforStart.WindowStyle = ProcessWindowStyle.Minimized;
                ScanProcess = Process.Start(inforStart);
                ScanProcess.WaitForInputIdle();
                ScanHandle = ScanProcess.MainWindowHandle;
                SetParent(ScanHandle, this.Handle);
                SetWindowLong(ScanHandle, GWL_STYLE, WS_VISIBLE);
                MoveWindow(ScanHandle, TabControlNewUser.Left, TabControlNewUser.Top, TabControlNewUser.Width, TabControlNewUser.Height, true);

                labelNotification.Text = "Please finish your scan step by step";
                labelNotification.ForeColor = Color.Red;
                btnNext.Visible = false;

                ScanProcess.WaitForExit();
                ScanHandle = IntPtr.Zero;
                Utilities.PushHeadData(CurrentUser);

                progressLoadScan.Visible = false;
                FinishedSignIn();
            });

            thread.Start();

            IProgress<int> progress = new Progress<int>(value => { progressLoadScan.Value = value; });
            Task.Run(() =>
            {
                for (int i = 0; i <= progressLoadScan.Maximum - 5; i++)
                {
                    if (!thread.IsAlive)
                    {
                        break;
                    }
                    System.Threading.Thread.Sleep(1);
                    progress.Report(i);
                }
            });
        }

        private void NewUser_FormClosed(object sender, FormClosedEventArgs e)
        {
            Owner.Show();
            if(ScanHandle != IntPtr.Zero)
            {
                ScanProcess.Kill();
                ScanHandle = IntPtr.Zero;
            }
        }

        private void btnTurnCamera_Click(object sender, EventArgs e)
        {
            webcam.InitializeWebCam(ref pictureBoxFace);
            btnTakePhoto.Visible = true;
            btnTurnCamera.Visible = false;
            webcam.Start();
            avatar = null;
        }
        private bool checkPage0Infor()
        {
            return txtBoxName.TextLength != 0 && txtBoxEmail.TextLength != 0;
        }
        private void tabPage1_Leave(object sender, EventArgs e)
        {
            
        }

        private bool checkPage1Infor()
        {
            return txtBoxPassword1.TextLength != 0 && txtBoxPassword2.TextLength != 0 && txtBoxPassword2.Text == txtBoxPassword1.Text && avatar != null;
        }

        private void tabPage2_Leave(object sender, EventArgs e)
        {

        }

        private void TabControlNewUser_SelectedIndexChanged(object sender, EventArgs e)
        {
            labelNotification.Text = "";
            int index = TabControlNewUser.SelectedIndex;
            switch (index)
            {
                case 0:
                    {
                        labelInstruction.Text = "Fill all information and click Next";
                        break;
                    }
                case 1:
                    {
                        labelInstruction.Text = "Set password, avatar and click Next!";
                        break;
                    }
                case 2:
                    {
                        labelInstruction.Text = "";
                        break;
                    }
                case 3:
                    {
                        labelInstruction.Text = "Scan your face and Modify it same to your!";
                        break;
                    }

            }
        }

        private void txtBoxEmail_Leave(object sender, EventArgs e)
        {
            
        }

        private void btnTryAgain_Click(object sender, EventArgs e)
        {
            webcam.InitializeWebCam(ref pictureBoxFace);
            btnTakePhoto.Visible = true;
            btnTurnCamera.Visible = false;
            btnTryAgain.Visible = false;
            webcam.Start();
            avatar = null;
        }
    }
}
