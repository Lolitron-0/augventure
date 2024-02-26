export default function (instance) {
	return {
		filterEvents(payload) {
<<<<<<< HEAD
			return instance.get("events?filter=" + JSON.stringify(payload));
=======
			return instance.get("events?sort=-id&filter=" + JSON.stringify(payload));
>>>>>>> 7a63c61e38ecf583e0460ad4a74a68c0cbfdc729
		},
		createEvent(payload) {
			return instance.post("events", payload);
		},
<<<<<<< HEAD
		listEvent() {
			return instance.get("events");
		},
=======
>>>>>>> 7a63c61e38ecf583e0460ad4a74a68c0cbfdc729
	};
}
