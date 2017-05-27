using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_App
{
    public class GlassesObject
    {
        public string Id { get; set; }
        public string Name { get; set; }
        public string Color { get; set; }
        public string Producer { get; set; }
        public float Price { get; set; }
        public string Status { get; set; }
        public int Temple { get; set; }
        public int Eye { get; set; }
        public int Bridge { get; set; }
    }
    
    public class UserObject
    {
        public string Id { get; set; }
        public string Name { get; set; }
        public string Email { get; set; }
        public string Address { get; set; }
        public bool Gender { get; set; }
        public string Discription { get; set; }
    }

}
