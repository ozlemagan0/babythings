using Babything.WebApi.Model;
using Babything.WebApi.Service;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Babything.WebApi.Controllers
{
    
    [Route("api/data")]
    public class DataController
    {

        private IClientService _service;

        public DataController(IClientService service)
        {
            _service = service;
        }

        [HttpPost]
        public async Task PostAsync([FromBody]MyEventData data)
        {
            await _service.SendData(data);            
        }

    }
}
