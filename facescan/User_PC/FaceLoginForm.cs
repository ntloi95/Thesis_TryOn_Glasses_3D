using System;
using System.Linq;
using System.Text;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.ComponentModel;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Collections.Specialized;
using System.Threading.Tasks;
using MaterialSkin.Controls;


namespace User_PC
{
    //Design by Pongsakorn Poosankam
    public partial class FaceLoginForm : MaterialForm
    {
        WebCam webcam;
        public FaceLoginForm()
        {
            InitializeComponent();
            btnFaceLogin.Visible = false;
            webcam = new WebCam();
            webcam.InitializeWebCam(ref imgVideo);
            webcam.Start();
            btnFaceLogin.Visible = true;
        }
        
        private void FaceLogin_Load(object sender, EventArgs e)
        {
            
        }

        public static async Task<string> SendRequestLogin(string url, string file, string paramName, string contentType)
        {
            string boundary = "---------------------------" + DateTime.Now.Ticks.ToString("x");
            byte[] boundarybytes = System.Text.Encoding.ASCII.GetBytes("\r\n--" + boundary + "\r\n");

            HttpWebRequest wr = (HttpWebRequest)WebRequest.Create(url);
            wr.ContentType = "multipart/form-data; boundary=" + boundary;
            wr.Method = "POST";
            wr.KeepAlive = true;
            wr.Credentials = System.Net.CredentialCache.DefaultCredentials;

            Stream rs = wr.GetRequestStream();

            rs.Write(boundarybytes, 0, boundarybytes.Length);

            string headerTemplate = "Content-Disposition: form-data; name=\"{0}\"; filename=\"{1}\"\r\nContent-Type: {2}\r\n\r\n";
            string header = string.Format(headerTemplate, paramName, file, contentType);
            byte[] headerbytes = System.Text.Encoding.UTF8.GetBytes(header);
            rs.Write(headerbytes, 0, headerbytes.Length);

            FileStream fileStream = new FileStream(file, FileMode.Open, FileAccess.Read);
            byte[] buffer = new byte[4096];
            int bytesRead = 0;
            while ((bytesRead = fileStream.Read(buffer, 0, buffer.Length)) != 0)
            {
                rs.Write(buffer, 0, bytesRead);
            }
            fileStream.Close();

            byte[] trailer = System.Text.Encoding.ASCII.GetBytes("\r\n--" + boundary + "--\r\n");
            rs.Write(trailer, 0, trailer.Length);
            rs.Close();

            WebResponse wresp = null;
            try
            {
                wresp = await wr.GetResponseAsync();
                Stream stream2 = wresp.GetResponseStream();
                StreamReader reader2 = new StreamReader(stream2);
                if (((HttpWebResponse)wresp).StatusCode == HttpStatusCode.OK)
                {
                    return reader2.ReadToEnd();
                }
                return null;
            }
            catch
            {
                
            }
            return null;
        }

        private async void bntCapture_Click(object sender, EventArgs e)
        {
            string pathFile = @".\userdata\temp.ava";
            FileStream fstream = new FileStream(pathFile, FileMode.OpenOrCreate);
            imgVideo.Image.Save(fstream, System.Drawing.Imaging.ImageFormat.Jpeg);
            fstream.Close();
            webcam.Stop();
            string UserID = await SendRequestLogin(Utilities.ServerHost+"/api/facelogin", pathFile, "file", "image/jpg"); 
            if (UserID != null)
            {
                OldUser parent = (OldUser) Owner;
                parent.loginSuccess(UserID);
                this.Close();
            }
            else
            {
                MessageBox.Show("Can not find out you");
                this.Close();
            }

        }

        private void FaceLoginForm_Enter(object sender, EventArgs e)
        {
            
        }

        private void FaceLoginForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            webcam.Stop();
        } 
    }
}
