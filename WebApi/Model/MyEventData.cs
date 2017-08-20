using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApi.Model;

namespace Babything.WebApi.Model
{
    public class MyEventData
    {
        public DateTime Time { get; set; } = DateTime.UtcNow;
        public double tmp { get; set; }
        public double spo2 { get; set; }
        public double bpm { get; set; }
        public double pres { get; set; }
        public double hum { get; set; }
        public double alt { get; set; }

    }
}
