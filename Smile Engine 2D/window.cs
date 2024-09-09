using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Smile_Engine_2D
{
    public partial class window : Form
    {
        

        public window()
        {
            InitializeComponent();
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            DateTime thisDay = DateTime.Today;

            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "Smile Engnie File Project (*.sefp)|*.sefp";

            if (sfd.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    

                    DateTime now = DateTime.Now;
                    Console.WriteLine(now.ToString("yyyy-MM-dd hh:mm:ss"));

                    string pathFile = sfd.FileName;
                    BinaryWriter DataPrjFile = new BinaryWriter(File.Create(pathFile));
                    DataPrjFile.Write(now.ToString("yyyy-MM-dd hh:mm:ss"));
                    DataPrjFile.Close();

                    CreateProject CreateProject = new CreateProject();
                    CreateProject.Show();
                }
                catch
                {
                    MessageBoxButtons buttons = MessageBoxButtons.OK;
                    MessageBox.Show("An error occurred with the creation of the file. Please contact support", "Error", buttons, MessageBoxIcon.Error);
                }
            }
        }

        private void panel2_Paint(object sender, PaintEventArgs e)
        {

        }

        private void window_Load(object sender, EventArgs e)
        {

        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void open_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Smile Engnie File Project (*.sefp)|*.sefp";

            if (ofd.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    openFile OpenProject = new openFile();
                    OpenProject.Show();
                }
                catch
                {

                }
            }
        }
    }
}
