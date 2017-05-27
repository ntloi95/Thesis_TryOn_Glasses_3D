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
using System.IO;

namespace GUI_App
{
    public partial class Form1 : Form
    {
        //private IntPtr AppWinHandle;
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
        private void button2_Click(object sender, EventArgs e)
        { 
            HttpWebRequest request = (HttpWebRequest)HttpWebRequest.Create("http://localhost:1310/api/user");
            request.Method = "POST";

            string postData = "{'Id':'U003','Name':'Nguyen Van A','Email':'ntloi95@gmail.com','Address':'227, Nguyen Van Cu Str, District 5','Gender':false,'Discription':'He is very handsome'}";
            byte[] byteArray = Encoding.UTF8.GetBytes(postData);
            request.ContentType = "application/json";
            Stream dataStream = request.GetRequestStream();
            dataStream.Write(byteArray, 0, byteArray.Length);
            dataStream.Close();
            try
            {
                HttpWebResponse response = (HttpWebResponse)request.GetResponse();
                MessageBox.Show(((HttpWebResponse)response).StatusDescription);
                //Get the stream containing content returned by the server.  
                dataStream = response.GetResponseStream();
                StreamReader reader = new StreamReader(dataStream);
                string responseFromServer = reader.ReadToEnd();
                MessageBox.Show(responseFromServer);
                reader.Close();
                dataStream.Close();
                response.Close();  
            }
            catch(Exception ex)
            {
                MessageBox.Show("Cant not insert because " + ex.ToString(), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Process.Start("help.pdf");
        }


    }
}
