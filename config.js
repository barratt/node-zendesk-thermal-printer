const config = {

    port: process.env.PORT || 3302,

    pollRate: process.env.POLL_RATE,
    timeout: process.env.REQUEST_TIMEOUT || 6000,

    zendesk: {
        username:  process.env.ZENDESK_USERNAME,
        token:     process.env.ZENDESK_TOKEN,
        remoteUri: `https://${process.env.ZENDESK_SLUG}.zendesk.com/api/v2`,
    }

};4

module.exports = config;