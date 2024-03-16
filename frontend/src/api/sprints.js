export default function (instance) {
    return {
        listSprints() {
            return instance.get("sprints");
        },
        createSprint(payload) {
            return instance.post("sprints", payload);
        },
    };
}