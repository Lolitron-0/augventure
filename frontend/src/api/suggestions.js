export default function (instance) {
    return {
        filterSuggestion(payload) {
            return instance.get("suggestions?sort=-votes" + JSON.stringify(payload));
        },
        createSuggestion(payload) {
            return instance.post("suggestions", payload);
        },
    };
}