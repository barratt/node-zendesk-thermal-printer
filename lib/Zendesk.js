
const zendesk = require('node-zendesk');

const Zendesk = function(config) {
    this.client = zendesk.createClient(config);
}

Zendesk.prototype.openTickets = function() {
    const client = this.client;

    return new Promise((res, rej) => {
        client.search.query("type:ticket status:open", function (err, req, result) {
            if (err)
                return rej(err);
            
            return res(result);
        });
    });
}

module.exports = Zendesk;