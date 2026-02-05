using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace App1
{
    public class Person
    {
        public string Name { get; set; }
        public string Group { get; set; }

        public override string ToString()
        {
            return $"Student {this.Name} from Group {this.Group}";
        }
    }
}
