using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApi.Model;

namespace Babything.WebApi.Model
{
    public class MyEventData
    {
        public double Pulse { get; set; }
        public double Acc { get; set; }
        public Gps Gps { get; set; }

    }
}
