export default function(instance) {
    return {
        filterEvents(payload) {
            return instance.get('events?sort=-id', payload)
        },
        createEvent(payload) {
            return instance.post('events', payload)
        }
    }
}