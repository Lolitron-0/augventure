export default function (instance) {
	return {
		filterEvents(payload) {
			return instance.get("events?filter=" + JSON.stringify(payload));
		},
		createEvent(payload) {
			return instance.post("events", payload);
		},
	};
}
