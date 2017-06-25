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
using System.Net;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;
using System.IO;
using System.Drawing.Drawing2D;
using System.Configuration;

namespace User_PC
{
    public partial class OldUser : MaterialForm
    {
        private User CurrentUser;
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
            labelNotification.Text = "";
        }

        public void loginSuccess(string json)
        {
            CurrentUser = JsonConvert.DeserializeObject<User>(json);
            MessageBox.Show("Welcome \n" + CurrentUser.Name, "Welcome");
            TabControlOldUser.SelectedIndex++;

            byte[] bytes = Convert.FromBase64String(CurrentUser.Avatar);
            Image image;
            using (MemoryStream ms = new MemoryStream(bytes))
            {
                image = Image.FromStream(ms);
                pictureBox1.Image = image;

                var wfactor = (double)image.Width / pictureBox1.ClientSize.Width;
                var hfactor = (double)image.Height / pictureBox1.ClientSize.Height;

                var resizeFactor = Math.Max(wfactor, hfactor);
                var imageSize = new Size((int)(image.Width / resizeFactor), (int)(image.Height / resizeFactor));

                System.Drawing.Drawing2D.GraphicsPath path = new System.Drawing.Drawing2D.GraphicsPath();
                int x = (imageSize.Width - imageSize.Height) / 2;
                path.AddEllipse(x, x, imageSize.Height, imageSize.Height);
                pictureBox1.Region = new Region(path);

                TextBoxEmail.Text = "";
                TextBoxPassword.Text = "";
            }


        }
        private void TextBoxPassword_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                String CommandUrl = Utilities.ServerHost + "/api/emaillogin?email=" + TextBoxEmail.Text + "&password=" + TextBoxPassword.Text;
                try
                {
                    String json = new WebClient().DownloadString(CommandUrl);
                    loginSuccess(json);
                }
                catch
                {
                    MessageBox.Show("Please try again", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void btnScanAgain_Click(object sender, EventArgs e)
        {
            btnBack.Visible = false;
            TabControlOldUser.SelectedIndex = 2;
        }

        private void btnEditFace_Click(object sender, EventArgs e)
        {
            btnBack.Visible = false;
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
            WindowState = FormWindowState.Normal;
        }

        private void tabPageEdit_Leave(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Normal;
        }

        private void tabPageScan_Enter(object sender, EventArgs e)
        {
            const int GWL_STYLE = -16;
            const int WS_VISIBLE = 0x10000000;

            FormWindowState oldState = WindowState;
            this.WindowState = FormWindowState.Maximized;

            //Write data for read right profile of currentUser.
            System.IO.StreamWriter file = new System.IO.StreamWriter(Utilities.CurrentUserID);
            file.WriteLine(CurrentUser.Id);
            file.Close();

            Thread thread = new Thread(() =>
            {
                ProcessStartInfo inforStart = new ProcessStartInfo(Utilities.PathScan);
                inforStart.WindowStyle = ProcessWindowStyle.Minimized;
                ScanProcess = Process.Start(inforStart);
                ScanProcess.WaitForInputIdle();
                ScanHandle = ScanProcess.MainWindowHandle;
                SetParent(ScanHandle, this.Handle);
                SetWindowLong(ScanHandle, GWL_STYLE, WS_VISIBLE);
                MoveWindow(ScanHandle, TabControlOldUser.Left, TabControlOldUser.Top, TabControlOldUser.Width, TabControlOldUser.Height, true);

                ScanProcess.WaitForExit();

                //Push Edit Head data
                Utilities.PushEditHeadData(CurrentUser);
                TabControlOldUser.SelectedIndex = 1;
                WindowState = oldState;
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
        private void tabPageEdit_Enter(object sender, EventArgs e)
        {
            const int GWL_STYLE = -16;
            const int WS_VISIBLE = 0x10000000;
            const int SW_SHOW = 5;

            FormWindowState oldState = this.WindowState;
            this.WindowState = FormWindowState.Maximized;

            //Write data for read right profile of currentUser.
            System.IO.StreamWriter file = new System.IO.StreamWriter(Utilities.CurrentUserID);
            file.WriteLine(CurrentUser.Id);
            file.Close();

            Thread thread = new Thread(() =>
            {
                ProcessStartInfo inforStart = new ProcessStartInfo(Utilities.PathEdit);
                inforStart.WindowStyle = ProcessWindowStyle.Minimized;
                EditProcess = Process.Start(inforStart);
                EditProcess.WaitForInputIdle();
                EditHandle = EditProcess.MainWindowHandle;

                ShowWindow(EditHandle, SW_SHOW);
                SetParent(EditHandle, this.Handle);
                SetWindowLong(EditHandle, GWL_STYLE, WS_VISIBLE);
                MoveWindow(EditHandle, TabControlOldUser.Left, TabControlOldUser.Top, TabControlOldUser.Width, TabControlOldUser.Height, true);

                EditProcess.WaitForExit();

                //Push Edit Head Data
                Utilities.PushEditHeadData(CurrentUser);
                TabControlOldUser.SelectedIndex = 1;
                WindowState = oldState;
            });

            thread.Start();

            IProgress<int> progress = new Progress<int>(value => { progressLoadEdit.Value = value; });
            Task.Run(() =>
            {
                for (int i = 0; i <= progressLoadEdit.Maximum - 5; i++)
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

        private void TabPageInfor_Enter(object sender, EventArgs e)
        {

            // Load old data:
            txtBoxOldAddress.Text = CurrentUser.Address;
           
            txtBoxOldEmail.Text = CurrentUser.Email;
            txtBoxOldName.Text = CurrentUser.Name;
            radioButtonOldMale.Checked = CurrentUser.Gender == "M";
            radioButtonOldFemale.Checked = CurrentUser.Gender == "F";

            btnBack.Visible = true;
        }

        private void btnBack_Click(object sender, EventArgs e)
        {
            TabControlOldUser.SelectedIndex = 1;
        }

        private void TabPageFunction_Enter(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Normal;
            labelWelcome.Text = "Welcome, " + CurrentUser.Name;
            btnBack.Visible = false;
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
            if (ScanHandle != IntPtr.Zero)
            {
                ScanProcess.Kill();
                ScanHandle = IntPtr.Zero;
            }
            if (EditHandle != IntPtr.Zero)
            {
                EditProcess.Kill();
                EditHandle = IntPtr.Zero;
            }
            Owner.Show();
        }

        private void TextBoxPassword_Click(object sender, EventArgs e)
        {

        }

        private void TabControlOldUser_Enter(object sender, EventArgs e)
        {

        }

        private void btnUpdateInfor_Click(object sender, EventArgs e)
        {
            try
            {
                WebRequest request = WebRequest.Create(Utilities.ServerHost+"/api/updateinfor?email=" + CurrentUser.Email);
                request.Method = "PUT";

                User user = new User();
                user.Name = txtBoxOldName.Text;
                user.Address = txtBoxOldAddress.Text;
                user.Email = txtBoxOldEmail.Text;
                user.Discription = "";

                if (radioButtonOldMale.Checked)
                    user.Gender = "M";
                else
                    user.Gender = "F";

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
                    labelNotification.Text = "Update Success!";

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
        }
        private WebCam webcam;
        private Image avatar;
        
        private void materialRaisedButton5_Click(object sender, EventArgs e)
        {
            try {
                WebRequest request = WebRequest.Create(Utilities.ServerHost+"/api/updatepassword?email="+CurrentUser.Email);
                request.Method = "PUT";

                User user = new User();
                if(avatar == null)
                    MessageBox.Show("You have not set avatar for log in by face", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                else                    
                using (var ms = new MemoryStream())
                {
                    avatar.Save(ms, System.Drawing.Imaging.ImageFormat.Jpeg);
                    user.Avatar = Convert.ToBase64String(ms.ToArray());
                }
                user.Password = CurrentUser.Password;
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
                    labelNotification.Text = "Update avatar success";
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                labelNotification.ForeColor = Color.FromArgb(255, 0, 0);
                labelNotification.Text = "Update avatar failed";
            }
        }

        private void btnTurnOnCamera_Click(object sender, EventArgs e)
        {
            btnTakePhoto.Visible = true;
            btnTurnOnCamera.Visible = false;
            webcam.Start();
        }

        private void btnTakePhoto_Click(object sender, EventArgs e)
        {
            btnTurnOnCamera.Visible = false;
            btnTryAgain.Visible = true;
            btnUpload.Visible = true;
            webcam.Stop();
            avatar = pictureBoxFace.Image;
            btnTakePhoto.Visible = false;
        }

        private void OldUser_Load(object sender, EventArgs e)
        {
            webcam = new WebCam();
            webcam.InitializeWebCam(ref pictureBoxFace);
            avatar = null;
        }

        private void btnTryAgain_Click(object sender, EventArgs e)
        {
            btnTakePhoto.Visible = true;
            btnTryAgain.Visible = false;
            btnUpload.Visible = false;
            webcam.Start();
        }

        private void tabPageChangePass_Leave(object sender, EventArgs e)
        {
            webcam.Stop();
        }

        private void pictureBox1_Resize(object sender, EventArgs e)
        {
            
        }

        private void btn_LogOut_Click(object sender, EventArgs e)
        {
            TabControlOldUser.SelectedIndex = 0;
            CurrentUser = null;
        }

        private void btnFaceLogin_Click(object sender, EventArgs e)
        {
            Form faceLogin = new FaceLoginForm();
            faceLogin.Show(this);
        }

        private void TabPageLogin_Enter(object sender, EventArgs e)
        {
            btnBack.Visible = false;
        }

        private void TextBoxEmail_Leave(object sender, EventArgs e)
        {
            
        }

        private void tabPageChangePass_Enter(object sender, EventArgs e)
        {
            btnBack.Visible = true;
        }

        private void TabControlOldUser_SelectedIndexChanged(object sender, EventArgs e)
        {
            labelNotification.Text = "";
        }

        private void btnUpdateTextPassword_Click(object sender, EventArgs e)
        {
            if(txtBoxNewPass1.Text != txtBoxNewPass2.Text || txtBoxNewPass1.Text.Length == 0 || txtBoxOldPass.Text != CurrentUser.Password)
            try
            {
                WebRequest request = WebRequest.Create(Utilities.ServerHost + "/api/update_text_password?email=" + CurrentUser.Email);
                request.Method = "PUT";

                User user = new User();
                
                user.Password = CurrentUser.Password;
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
                    labelNotification.Text = "Update password success";
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Update Password failed" + ex.ToString(), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                labelNotification.ForeColor = Color.FromArgb(255, 0, 0);
                labelNotification.Text = "Update password failed";
            }
        }
    }
}