using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_App
{

    public class Rootobject
    {
        public List<Class1> Property1 { get; set; }
    }

    public class Class1
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

}
