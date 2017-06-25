namespace User_PC
{
    //Design by Pongsakorn Poosankam
    partial class FaceLoginForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.imgVideo = new System.Windows.Forms.PictureBox();
            this.btnFaceLogin = new MaterialSkin.Controls.MaterialRaisedButton();
            ((System.ComponentModel.ISupportInitialize)(this.imgVideo)).BeginInit();
            this.SuspendLayout();
            // 
            // imgVideo
            // 
            this.imgVideo.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.imgVideo.Location = new System.Drawing.Point(16, 80);
            this.imgVideo.Name = "imgVideo";
            this.imgVideo.Size = new System.Drawing.Size(496, 339);
            this.imgVideo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.imgVideo.TabIndex = 0;
            this.imgVideo.TabStop = false;
            // 
            // btnFaceLogin
            // 
            this.btnFaceLogin.Depth = 0;
            this.btnFaceLogin.Location = new System.Drawing.Point(224, 432);
            this.btnFaceLogin.MouseState = MaterialSkin.MouseState.HOVER;
            this.btnFaceLogin.Name = "btnFaceLogin";
            this.btnFaceLogin.Primary = true;
            this.btnFaceLogin.Size = new System.Drawing.Size(75, 23);
            this.btnFaceLogin.TabIndex = 1;
            this.btnFaceLogin.Text = "Log in";
            this.btnFaceLogin.UseVisualStyleBackColor = true;
            this.btnFaceLogin.Click += new System.EventHandler(this.bntCapture_Click);
            // 
            // FaceLoginForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(530, 468);
            this.Controls.Add(this.btnFaceLogin);
            this.Controls.Add(this.imgVideo);
            this.Name = "FaceLoginForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "WinForm C# WebCam";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FaceLoginForm_FormClosed);
            this.Load += new System.EventHandler(this.FaceLogin_Load);
            this.Enter += new System.EventHandler(this.FaceLoginForm_Enter);
            ((System.ComponentModel.ISupportInitialize)(this.imgVideo)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox imgVideo;
        private MaterialSkin.Controls.MaterialRaisedButton btnFaceLogin;
    }
}

