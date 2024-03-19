export default function (instance) {
    return {
        filterSuggestion(payload) {
            return instance.get("suggestions?sort=-votes&filter=" + JSON.stringify(payload));
        },
        createSuggestion(payload) {
            return instance.post("suggestions", payload);
        },
        voteSuggestion(SUGGESTION_ID, payload) {
            return instance.put(`suggestions/${SUGGESTION_ID}/vote`, payload);
        }
    };
}