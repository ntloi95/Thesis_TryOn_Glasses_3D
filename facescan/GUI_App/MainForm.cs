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
using System.Collections;
using Newtonsoft.Json.Linq;
using System.Net;
using Newtonsoft.Json;
using System.IO;
using System.Media;

namespace GUI_App
{
    public partial class MainForm : MaterialForm
    {
        private IntPtr ExeHandle;
        private Process ExeProcess;

        public MainForm()
        {
            InitializeComponent();

            MaterialSkinManager skinManager = MaterialSkinManager.Instance;
            skinManager.AddFormToManage(this);
            skinManager.Theme = MaterialSkinManager.Themes.DARK;
            skinManager.RemoveFormToManage(this);
            mDisplayGlassesList = new ArrayList();
            mDisplayUserList = new ArrayList();
            mDisplayTransaction = new ArrayList();
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
            if (ExeHandle != IntPtr.Zero)
            {
                ExeProcess.Kill();
                ExeHandle = IntPtr.Zero;
            }
            base.OnHandleDestroyed(e);
        }

        private void Form2_ClientSizeChanged(object sender, EventArgs e)
        {
            if (ExeHandle != IntPtr.Zero)
                MoveWindow(ExeHandle, TabControl.Left, TabControl.Top + introductionScanner.Bottom, TabControl.Width, TabControl.Height - introductionScanner.Bottom, true);
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
            if(ExeHandle == IntPtr.Zero)
            {
                const int GWL_STYLE = -16;
                const int WS_VISIBLE = 0x10000000;
                ExeProcess = Process.Start("facescanDX_NoRS.exe");
                ExeProcess.WaitForInputIdle();
                ExeHandle = ExeProcess.MainWindowHandle;
                SetParent(ExeHandle, this.Handle);
                SetWindowLong(ExeHandle, GWL_STYLE, WS_VISIBLE);
                MoveWindow(ExeHandle, TabControl.Left, TabControl.Top + introductionScanner.Bottom, TabControl.Width, TabControl.Height - introductionScanner.Bottom, true);
            }
            else
            {
                const int SW_SHOW = 5;
                ShowWindow(ExeHandle, SW_SHOW);
            }
        }

        private void materialSingleLineTextField3_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && (e.KeyChar != '.'))
                e.Handled = true;

            if ((e.KeyChar == '.') && ((sender as TextBox).Text.IndexOf('.') > -1))
                e.Handled = true;
            PriceTextField.Text = PriceTextField.Text; 
        }

        private void LinkAbout_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            AboutForm AboutDialog = new AboutForm();
            AboutDialog.ShowDialog(this);
        }

        private void LinkContact_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            ContactForm ContactDialog = new ContactForm();
            ContactDialog.ShowDialog(this);
        }

        private ArrayList mDisplayUserList;
        private void AddUserToTableView(UserObject u)
        {
            int row = tableDataUser.Rows.Add();
            tableDataUser.Rows[row].Cells[1].Value = row + 1;
            tableDataUser.Rows[row].Cells[2].Value = u.Id;
            tableDataUser.Rows[row].Cells[3].Value = u.Name;
            tableDataUser.Rows[row].Cells[4].Value = u.Email;
            tableDataUser.Rows[row].Cells[5].Value = u.Address;
            tableDataUser.Rows[row].Cells[6].Value = u.Gender ? "Female" : "Male";
            tableDataUser.Rows[row].Cells[7].Value = u.Discription;
            
        }

        private void btn_SearchUser_Click(object sender, EventArgs e)
        {
            String CommandUrl = "http://localhost:1310/api/user";
            try
            {
                string json = new WebClient().DownloadString(CommandUrl);
                JArray jarray = JArray.Parse(json);

                mDisplayUserList.Clear();
                tableDataUser.Rows.Clear();

                foreach (var item in jarray)
                {
                    UserObject user = JsonConvert.DeserializeObject<UserObject>(item.ToString());
                    mDisplayGlassesList.Add(user);
                    AddUserToTableView(user);
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.ToString(), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private ArrayList mDisplayGlassesList;
        private void AddGlassesToTableView(GlassesObject g)
        {
            int row = tableDataGlasses.Rows.Add();
            tableDataGlasses.Rows[row].Cells[1].Value = row+1;
            tableDataGlasses.Rows[row].Cells[2].Value = g.Id;
            tableDataGlasses.Rows[row].Cells[3].Value = g.Name;
            tableDataGlasses.Rows[row].Cells[4].Value = g.Color;
            tableDataGlasses.Rows[row].Cells[5].Value = g.Producer;
            tableDataGlasses.Rows[row].Cells[6].Value = g.Price;
            tableDataGlasses.Rows[row].Cells[7].Value = g.Status;
            tableDataGlasses.Rows[row].Cells[8].Value = g.Temple;
            tableDataGlasses.Rows[row].Cells[9].Value = g.Eye;
            tableDataGlasses.Rows[row].Cells[10].Value = g.Bridge;
        }

        private void btn_SearchGlasses_Click(object sender, EventArgs e)
        {
            String CommandUrl = "http://localhost:1310/api/glasses";
            try
            {
                string json = new WebClient().DownloadString(CommandUrl);
                JArray jarray = JArray.Parse(json);

                mDisplayGlassesList.Clear();
                tableDataGlasses.Rows.Clear();

                foreach (var item in jarray)
                {
                    GlassesObject glasses = JsonConvert.DeserializeObject<GlassesObject>(item.ToString());
                    mDisplayGlassesList.Add(glasses);
                    AddGlassesToTableView(glasses);
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.ToString(), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            
        }

        private void metroButton10_Click(object sender, EventArgs e)
        {
            try
            {
                WebRequest request = WebRequest.Create("http://localhost:1310/api/user");
                request.Method = "POST";

                UserObject user = new UserObject();
                user.Address = AddressTextfield.Text;
                user.Discription = DiscriptionTextField.Text;
                user.Email = EmailTextField.Text;
                user.Gender = radioFemale.Checked;
                user.Id = IdTextField.Text;
                user.Name = FullNameTextField.Text;

                string postData = JsonConvert.SerializeObject(user);
                byte[] byteArray = Encoding.UTF8.GetBytes(postData);
                request.ContentType = "application/json";
                Stream dataStream = request.GetRequestStream();
                dataStream.Write(byteArray, 0, byteArray.Length);
                dataStream.Close();
                WebResponse response = request.GetResponse();
                if (((HttpWebResponse)response).StatusCode == HttpStatusCode.Created)
                {
                    AddUserToTableView(user);
                    labelStatusUser.ForeColor = Color.FromArgb(50, 255, 50);
                    labelStatusUser.Text = "Insert success!!";
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                labelStatusUser.ForeColor = Color.FromArgb(255, 50, 50);
                labelStatusUser.Text = "Insert failed!!";
            }
        }

        private void btnHelp_Click(object sender, EventArgs e)
        {
            try
            {
                Process.Start("help.pdf");
            }
            catch
            {
                MessageBox.Show("Helping file is damaged", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            
        }

        private void tabPageUser_Enter(object sender, EventArgs e)
        {
            labelStatusUser.Text = "";
        }

        private void btnInsertGlasses_Click(object sender, EventArgs e)
        {
            try
            {
                WebRequest request = WebRequest.Create("http://localhost:1310/api/glasses");
                request.Method = "POST";

                GlassesObject glasses = new GlassesObject();
                glasses.Bridge = (int)BridgeSize.Value;
                glasses.Color = ColorComboBox.Text;
                glasses.Eye = (int)EyeSize.Value;
                glasses.Id = GlassesIDTextField.Text;
                glasses.Name = GlassesNameTextField.Name;
                if (PriceTextField.Text.Length == 0)
                    glasses.Price = 0;
                else
                    glasses.Price = float.Parse(PriceTextField.Text);
                glasses.Producer = ProducerComboBox.Text;
                glasses.Status = StatusComboBox.Text;
                glasses.Temple = (int)TempleSize.Value;
                
                string postData = JsonConvert.SerializeObject(glasses);
                byte[] byteArray = Encoding.UTF8.GetBytes(postData);
                request.ContentType = "application/json";
                Stream dataStream = request.GetRequestStream();
                dataStream.Write(byteArray, 0, byteArray.Length);
                dataStream.Close();
                WebResponse response = request.GetResponse();
                if (((HttpWebResponse)response).StatusCode == HttpStatusCode.Created)
                {
                    AddGlassesToTableView(glasses);
                    lableStatusGlasses.ForeColor = Color.FromArgb(50, 255, 50);
                    lableStatusGlasses.Text = "Insert success!!";
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                lableStatusGlasses.ForeColor = Color.FromArgb(255, 50, 50);
                lableStatusGlasses.Text = "Insert failed!!";
            }
        }

        private void tabPageGlasses_Enter(object sender, EventArgs e)
        {
            lableStatusGlasses.Text = "";
        }

        private void btnDeleteUser_Click(object sender, EventArgs e)
        {
            foreach(DataGridViewRow row in tableDataUser.Rows)
            {
                if((bool) row.Cells[0].Value)
                {
                    tableDataUser.Rows.Remove(row);
                    foreach (DataGridViewRow rowj in tableDataUser.Rows)
                        rowj.Cells[1].Value = rowj.Index + 1;
                    break;
                }
            }
        }

        private void tableDataUser_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            foreach (DataGridViewRow row in tableDataUser.Rows)
                row.Cells[0].Value = false;
        }

        private void btnDeleteGlasses_Click(object sender, EventArgs e)
        {
            foreach (DataGridViewRow row in tableDataGlasses.Rows)
            {
                if ((bool)row.Cells[0].Value)
                {
                    tableDataGlasses.Rows.Remove(row);
                    foreach (DataGridViewRow rowj in tableDataGlasses.Rows)
                        rowj.Cells[1].Value = rowj.Index + 1;
                    break;
                }
            }
        }

        private void tableDataGlasses_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            foreach (DataGridViewRow row in tableDataGlasses.Rows)
                row.Cells[0].Value = false;
        }

        private ArrayList mDisplayTransaction;
        void AddTransactionToTableView(TransactionObject transaction)
        {
            int row = tableAllTransaction.Rows.Add();
            tableAllTransaction.Rows[row].Cells[1].Value = row + 1;
            tableAllTransaction.Rows[row].Cells[2].Value = transaction.Id;
            tableAllTransaction.Rows[row].Cells[3].Value = transaction.User_Id;
        }
        private void btnSearchTransaction_Click(object sender, EventArgs e)
        {
            String CommandUrl = "http://localhost:1310/api/transaction";
            try
            {
                string json = new WebClient().DownloadString(CommandUrl);
                JArray jarray = JArray.Parse(json);

                mDisplayTransaction.Clear();
                tableAllTransaction.Rows.Clear();

                foreach (var item in jarray)
                {
                    TransactionObject transaction = JsonConvert.DeserializeObject<TransactionObject>(item.ToString());
                    mDisplayGlassesList.Add(transaction);
                    AddTransactionToTableView(transaction);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void AddUserInforToTransactionView(UserObject user)
        {
            CustomerFullNameTextField.Text = user.Name;
            CustomerEmailTextField.Text = user.Email;
            CustomerAddressTextField.Text = user.Address;
        }

        private void tableAllTransaction_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            /*foreach (DataGridViewRow row in tableAllTransaction.Rows)
                row.Cells[0].Value = false;
            String CommandUrl = "http://localhost:1310/api/user?id=" + tableAllTransaction.Rows[e.RowIndex].Cells[3];
            try
            {
                string json = new WebClient().DownloadString(CommandUrl);
                UserObject user = JsonConvert.DeserializeObject<UserObject>(json);
                AddUserInforToTransactionView(user);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }*/
        }
    }
}
