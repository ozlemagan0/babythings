using Babything.WebApi.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Babything.WebApi.Service
{
    public interface IClientService
    {

        Task SendData(MyEventData data);
    }
}
