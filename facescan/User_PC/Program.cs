using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace User_PC
{
    public static class Utilities
    {
        public static String ServerHost = ConfigurationManager.AppSettings["server"];
        public static String PathScan = ConfigurationManager.AppSettings["scan.exe"];
        public static String PathEdit = ConfigurationManager.AppSettings["edit.exe"];
        public static String CurrentUserID = ConfigurationManager.AppSettings["currentid"];

        private static byte[] ResizeImage(String fileName)
        {
            Image image = Bitmap.FromFile(fileName);
            Size newSize = new Size(512, 512);
            Image newImage = new Bitmap(newSize.Width, newSize.Height);
            using (Graphics GFX = Graphics.FromImage((Image)newImage))
            {
                GFX.DrawImage(image, new Rectangle(Point.Empty, newSize));
            }

            using (var ms = new MemoryStream())
            {
                newImage.Save(ms, System.Drawing.Imaging.ImageFormat.Gif);
                return ms.ToArray();
            }
        }

        public static void PushHeadData(User CurrentUser)
        {
            try
            {
                WebRequest request = WebRequest.Create(ServerHost + "/api/addhead");
                request.Method = "POST";
                request.ContentType = "application/json";

                HeadData head = new HeadData();
                head.FileName = CurrentUser.Email;
                head.Used = true;
                head.UserId = CurrentUser.Id;

                string path = @"./userdata/export/" + CurrentUser.Id;
                byte[] buffer = System.IO.File.ReadAllBytes(path + ".mtl");
                head.Mtl = Convert.ToBase64String(buffer);

                buffer = System.IO.File.ReadAllBytes(path + ".obj");
                head.Obj = Convert.ToBase64String(buffer);

                buffer = ResizeImage(path + "_face.png");
                head.Png1 = Convert.ToBase64String(buffer);

                buffer = ResizeImage(path + "_hair.png");
                head.Png2 = Convert.ToBase64String(buffer);

                string postData = JsonConvert.SerializeObject(head);
                byte[] byteArray = Encoding.UTF8.GetBytes(postData);
                Stream dataStream = request.GetRequestStream();
                dataStream.Write(byteArray, 0, byteArray.Length);
                dataStream.Close();
                WebResponse response = request.GetResponse();
            }

            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public static void PushEditHeadData(User CurrentUser)
        {
            try
            {
                WebRequest request = WebRequest.Create(ServerHost + "/api/deletehead?userid="+CurrentUser.Id);
                request.Method = "PUT";
                request.ContentLength = 0;
                WebResponse response = request.GetResponse();
                PushHeadData(CurrentUser);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);

            }
        }
    }
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());
        }
    }
}
