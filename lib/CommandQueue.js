
const validCommands = [
    // Cool stuff
    'inverse',
    'println',
    'reset',
    'feed',

    // Weight
    'bold',

    // Justification
    'centre',

    // Sizes
    'large',
    'medium',
    'small',
];

const CommandQueue = function() {
    this.queue = [];
}

// This is cool because it registers all the valid commands 
// as functions AND lets you pass data into them
for (let command of validCommands) {
    CommandQueue.prototype[command] = function() {
        this.queue.push(command);

        for (let arg of arguments)
            this.queue.push(arg);
    }
}

// If you use this, please ensure you're using valid commands!
CommandQueue.prototype.push = function(commands) {
    this.queue = this.queue.concat(commands);
}

// Get all the commands out as one big list.
CommandQueue.prototype.commands = function() {
    return this.queue;
};

module.exports = CommandQueue;
