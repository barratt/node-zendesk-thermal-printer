const CommandQueue = require('./CommandQueue');

const formatFromTicket = function(ticket) {
    let commandQueue = new CommandQueue();

    commandQueue.push(bigHeader("NEW TICKET"));
    commandQueue.push(ticketId(ticket.id));
    commandQueue.push(subject(ticket.subject));
    commandQueue.feed(2);

    // TODO: Add more details.
    // commandQueue.println(`From: `);

    return commandQueue.commands();
}

// Other helpers used in here.
const bigHeader = function(text) {
    return [
        'reset',
        'inverse',
        'bold',
        'medium',
        'centre',
        'println',
        text,
    ];
}

const ticketId = function(id) {
    return [
        'reset',
        'large',
        'println',
        '# ' + id,
    ];
}

const subject = function(subject) {
    return [
        'reset',
        'bold',
        'println',
        'subject:',
        'bold',
        'println',
        subject
    ];
}


module.exports = {
    formatFromTicket,
};