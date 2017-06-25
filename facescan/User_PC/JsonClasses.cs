using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace User_PC
{

    public class User
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Email { get; set; }
        public string Address { get; set; }
        public string Gender { get; set; }
        public string Discription { get; set; }
        public string Password { get; set; }
        public string Avatar { get; set; }
    }

    
    public class Glasses
    {
        public string Id { get; set; }
        public string Name { get; set; }
        public string Color { get; set; }
        public string Producer { get; set; }
        public float Price { get; set; }
        public string Thumnail { get; set; }
        public string Status { get; set; }
        public int Temple { get; set; }
        public int Eye { get; set; }
        public int Bridge { get; set; }
    }

    public class HeadData
    {
        public int Id { get; set; }
        public int UserId { get; set; }
        public string Obj { get; set; }
        public string Mtl { get; set; }
        public string Png1 { get; set; }
        public string Png2 { get; set; }
        public bool Used { get; set; }
        public string FileName { get; set; }
    }
}
