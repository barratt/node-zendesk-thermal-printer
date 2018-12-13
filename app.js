const express   = require('express');
const sleep     = require('await-sleep');

const config    = require('./config');
const Zendesk   = require('./lib/Zendesk');

const utils     = require('./lib/utils');

const zendesk   = new Zendesk(config.zendesk);

const seenTickets = []; // A list of ticket ID's we've seen
const ticketQueue = []; // A list of tickets we need to print

const app = express();

app.get('/', async (req, res) => {
    let requestTime = Date.now();

    // Trick to hang the request if no tickets
    // This way we can respond as soon as we get a ticket and the client
    // can instantly request again if it times out.
    // Be sure not to set this too high as we will hang here even if the client is gone.
    // Zendesk is so slow idek why i bothered with this guess i just wanted to be cool.
    while (ticketQueue.length <= 0 && (Date.now() - requestTime) < config.timeout)
        await sleep(500);

    // We've hung, lets see if we have one.
    if (ticketQueue.length == 0) 
        return res.send([]); // Oh well, we tried.
    
    res.send(ticketQueue.splice(0, 1)[0]);
});


// Lets setup our main stuff.
async function lookForTickets() {
    console.log(`Getting open tickets`);
    let tickets = await zendesk.openTickets();
    console.log(`Got ${tickets.length} tickets`);

    // Lets see if we have any tickets that we've not seen before.
    for (let ticket of tickets) {
        if (seenTickets.indexOf(ticket.id) > -1)
            continue; // Seen it, boring.
        
        // Turn it into a command list.
        let printerTicket = utils.formatFromTicket(ticket);

        // Lets push it on the queue.
        ticketQueue.push(printerTicket);
        seenTickets.push(ticket.id);
        console.log(`Added ticket ${ticket.id} to queue`);
    }
}

// Setup looker.
lookForTickets();
setInterval(lookForTickets, config.pollRate);

app.listen(config.port, () => {
    console.log(`App listening on port ${config.port}`);
});