export default function(instance) {
    return {
        filterEvents(payload) {
            return instance.get('events?sort=-id', payload)
        }
    }
}