using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Babything.WebApi.Model;
using Microsoft.Azure.EventHubs;
using Newtonsoft.Json;
using System.Text;
using Microsoft.Extensions.Options;
using WebApi.Config;

namespace Babything.WebApi.Service
{
    public class ClientService : IClientService
    {
        private EventHubClient eventHubClient;
        private IOptions<HubConfig> _config;
        
        public ClientService(IOptions<HubConfig> config)
        {
            _config = config;

            var connectionStringBuilder = new EventHubsConnectionStringBuilder(_config.Value.EhConnectionString)
            {
                EntityPath = _config.Value.EhEntityPath
            };

            eventHubClient = EventHubClient.CreateFromConnectionString(connectionStringBuilder.ToString());
            
        }
        public Task SendData(MyEventData data)
        {
            var json = JsonConvert.SerializeObject(data);
            var eventData = new EventData(Encoding.UTF8.GetBytes(json));
            return eventHubClient.SendAsync(eventData);
        }
    }
}
