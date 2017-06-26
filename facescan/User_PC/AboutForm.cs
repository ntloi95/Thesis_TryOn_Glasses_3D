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

namespace User_PC
{
    public partial class AboutForm : MaterialForm
    {
        public AboutForm()
        {
            InitializeComponent();
            MaterialSkinManager skinManager = MaterialSkinManager.Instance;
            skinManager.AddFormToManage(this);
            skinManager.Theme = MaterialSkinManager.Themes.LIGHT;
            skinManager.RemoveFormToManage(this);
        }

        private void AboutForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            MaterialSkinManager skinManager = MaterialSkinManager.Instance;
            skinManager.Theme = MaterialSkinManager.Themes.DARK;
        }
    }
}
