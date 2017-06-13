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

namespace User_PC
{
    public partial class MainForm : MaterialForm
    {
        public MainForm()
        {
            InitializeComponent();
        }


        private void button2_Click(object sender, EventArgs e)
        {
            NewUser form = new NewUser();
            this.Hide();
            form.Show(this);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OldUser form = new OldUser();
            this.Hide();
            form.Show(this);
        }
    }
}
